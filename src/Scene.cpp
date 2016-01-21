#include "Scene.hpp"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::addGeometry(Geometry *geometry)
{
	m_geometries.push_back(geometry);
}

void Scene::addLight(Light *light)
{
	m_lights.push_back(light);
}

vec3 Scene::trace(Ray ray, int depth)
{
	if (depth > getMaxDepth())
	{
		return vec3(1);
	}
	float dist = 9999999.0f;
	vec3 intersectionPoint;
	vec3 d;
	vec3 N;
	vec3 outColor(0,0,0);
	Geometry* geo = NULL;
	vec3 origin, direction;
	origin = ray.getOrigin();
	direction = ray.getDirection();
	for (int i = 0; i < m_geometries.size(); i++)
	{
		Geometry * geometry = m_geometries.at(i);

		if(geometry->hit(ray, d))
		{
			vec3 intersected = vec3( geometry->getTransform() * vec4(d,1));
			float distance = sqrt((intersected.x-ray.getOrigin().x)*(intersected.x-ray.getOrigin().x)+
			(intersected.y-ray.getOrigin().y)*(intersected.y-ray.getOrigin().y)+
			(intersected.z-ray.getOrigin().z)*(intersected.z-ray.getOrigin().z));
			if (distance < dist)
			{
				dist = distance;
				geo = geometry;
				intersectionPoint = intersected;
			}
		}
		
	}
	if (!geo)
	{
		return vec3(0);
	}
	int visible=1;
	for (int i = 0; i < m_lights.size() && visible == 1; i++)
	{
		Light *light = m_lights.at(i);
		vec3 L;
		float dist;
		vec3 intersected;
		visible=1;
		float attenuation = 1.0f;
		if (DirectionalLight* dl = dynamic_cast<DirectionalLight*>(light))
		{
			L = dl->getDirection();
			dist = 9999999999999.0f;
		}
		else if (PointLight* pl = dynamic_cast<PointLight*>(light))
		{
			L =  (pl->getPosition()-intersectionPoint);
			dist = glm::length(L);
			attenuation = 1.0f / (pl->getConstantAttenuation() + pl->getLinearAttenuation()*dist + pl->getQuadraticAttenuation()*dist*dist);
		}
		Ray secondaryRay(intersectionPoint+glm::normalize(L)*0.0001f, glm::normalize(L));
		vec3 o = secondaryRay.getOrigin();
		vec3 dir = secondaryRay.getDirection();
		for (int j = 0; j < m_geometries.size(); j++)
		{
			Geometry* g = m_geometries.at(j);
			if (g->hit(secondaryRay, intersected))
			{
				intersected = vec3( (g->getTransform()) * vec4(intersected,1));
				float distance = glm::length(o-intersected);
				if (distance < dist)
				{
					visible = 0;
				}
			}
		}
		N = glm::normalize(vec3(glm::inverse(glm::transpose(geo->getTransform())) * vec4(geo->getNormal(intersectionPoint),0)));
		L = glm::normalize(L);

		// Diffuse
		float dot = glm::dot(L, N)*visible;
		
		vec3 diffuse(0,0,0), specular(0,0,0);
		if (dot > 0)
		{
			diffuse = light->getColor() * geo->getMaterial()->getDiffuse() * dot;
		}

		// Specular
		vec3 H = glm::normalize(L - ray.getDirection());
		//vec3 V = ray.getDirection();
		//vec3 R = L - 2.0f * glm::dot(L, N) * N;
		dot = glm::dot(H,N)*visible;
		if (dot > 0)
		{
			float spec = powf(dot,geo->getMaterial()->getShininess());
			specular = light->getColor() * geo->getMaterial()->getSpecular() * spec;
		}
		outColor += (diffuse + specular)*attenuation;
		//REFLECTION
		if (depth < m_maxDepth)
		{
			float spec = powf(dot,geo->getMaterial()->getShininess());
			vec3 R = ray.getDirection() - 2.0f * glm::dot(ray.getDirection(), N) * N;
			outColor += attenuation * light->getColor()* geo->getMaterial()->getSpecular() * trace(Ray(intersectionPoint +  R * 0.01f, R), depth+1);
		}
	}
	return geo->getMaterial()->getAmbient() + geo->getMaterial()->getEmission() + outColor;
	
}

void Scene::render(Camera* camera, Screen* screen)
{
	float angle = tan(M_PI * 0.5 * camera->getFov() / 180.); 
	for (int i = 0; i < screen->getHeight(); i++)
	{
		std::cout << "Pixel: y: " << i << std::endl;
	    for (int j = 0; j < screen->getWidth(); j++)
	    {
		  Ray primaryRay = camera->computeRay(j,i,screen);
		  vec3 color = trace(primaryRay, 0);
		  screen->putPixel(j,i,color);
	    }
	}
}

int Scene::getNumbersGeometries()
{
	return m_geometries.size();
}

int Scene::getNumbersLights()
{
	return m_lights.size();
}

void Scene::setMaxDepth(int depth)
{
	m_maxDepth = depth;
}

int Scene::getMaxDepth()
{
	return m_maxDepth;
}