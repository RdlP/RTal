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

vec3 Scene::trace(Ray ray, int depth, float oiRefract)
{
	if (depth > getMaxDepth())
	{
		return vec3(1);
	}
	float dist = 999999999999.0f;
	vec3 intersectionPoint;
	vec3 d;
	vec3 N;
	vec3 outColor(0,0,0);
	Geometry* geo = NULL;
	vec3 origin, direction;
	origin = ray.getOrigin();
	direction = ray.getDirection();
	Intersection intersectionData;
	for (int i = 0; i < m_geometries.size(); i++)
	{
		Geometry * geometry = m_geometries.at(i);
		Intersection res;
		res = geometry->hit(ray);
		if(res.isIntersection())
		{
			vec3 intersected = vec3( geometry->getTransform() * vec4(res.getPoint(),1));
			float distance = sqrt((intersected.x-ray.getOrigin().x)*(intersected.x-ray.getOrigin().x)+
			(intersected.y-ray.getOrigin().y)*(intersected.y-ray.getOrigin().y)+
			(intersected.z-ray.getOrigin().z)*(intersected.z-ray.getOrigin().z));
			if (distance < dist)
			{
				dist = distance;
				geo = geometry;
				intersectionPoint = intersected;
				intersectionData = res;
			}
		}
		
	}
	if (!geo)
	{
		return vec3(0);
	}
	//return vec3(1.0f, 0.0f, 0.0f);
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
		else if (SpotLight* sl = dynamic_cast<SpotLight*>(light))
		{
			L =  (sl->getPosition()-intersectionPoint);
			float dot = glm::dot(glm::normalize(L),sl->getDirection());
			if (dot < sl->getCosCutOff()){
				attenuation = 0.0f;
			}else{
				attenuation = 1.0f / (sl->getConstantAttenuation() + sl->getLinearAttenuation()*dist + sl->getQuadraticAttenuation()*dist*dist);
				attenuation *= powf(dot,sl->getExponent());
			}
			dist = glm::length(L);
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
			Intersection inter = g->hit(secondaryRay);
			if (inter.isIntersection())
			{
				intersected = vec3( (g->getTransform()) * vec4(inter.getPoint(),1));
				float distance = glm::length(o-intersected);
				if (distance < dist)
				{
					visible = 0;
				}
			}
		}
		N = glm::normalize(vec3(glm::inverse(glm::transpose(geo->getTransform())) * vec4(intersectionData.getNormal(),0)));
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
			outColor += attenuation * light->getColor()* geo->getMaterial()->getSpecular() * trace(Ray(intersectionPoint +  R * 0.01f, R), depth+1, oiRefract);
		}
		//REFRACTION
		float iRefract = geo->getMaterial()->getRefractionIndex();
		if (depth < m_maxDepth && iRefract > 0.0f)
		{
			float n = oiRefract / iRefract;
			N = N * (intersectionData.isInside()?-1.0f:1.0f);
			float cosI = -glm::dot(N, ray.getDirection());
			float cosT2 = 1.0f - n*n*(1.0f -cosI*cosI);
			if (cosT2 > 0.0f)
			{
				vec3 T = glm::normalize((n* ray.getDirection()) + (n*cosI-sqrtf(cosT2))*N);
				outColor += trace(Ray(intersectionPoint +  T * 0.01f, T), depth+1, iRefract)*0.5f;
			}
		}
	}
	return geo->getMaterial()->getAmbient() + geo->getMaterial()->getEmission() + outColor;
	
}

void Scene::render(Camera* camera, Screen* screen)
{
	//float angle = tan(M_PI * 0.5 * camera->getFov() / 180.); 
	for (int i = 0; i < screen->getHeight(); i++)
	{
		std::cout << "Pixel: y: " << i << std::endl;
	    for (int j = 0; j < screen->getWidth(); j++)
	    {
		  Ray primaryRay = camera->computeRay(j,i,screen);
		  vec3 color = trace(primaryRay, 0, 1.0f);
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