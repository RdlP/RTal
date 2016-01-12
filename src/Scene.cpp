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
	float d=9999999.0f;
	vec3 N;
	vec3 outColor;
	Geometry* geo = NULL;
	for (int i = 0; i < m_geometries.size(); i++)
	{
		Geometry * geometry = m_geometries.at(i);
		if(geometry->hit(ray, d))
		{
			if (d < dist)
			{
				dist = d;
				geo = geometry;
			}
		}
	}
	if (!geo)
	{
		return vec3(0);
	}
	intersectionPoint = ray.getOrigin() + ray.getDirection()*dist;
	for (int i = 0; i < m_lights.size(); i++)
	{
		Light *light = m_lights.at(i);
		vec3 L;
		float dist;
		int visible=1;
		if (DirectionalLight* dl = dynamic_cast<DirectionalLight*>(light))
		{
			L = dl->getDirection();
			dist = 999999.0f;
		}
		else if (PointLight* pl = dynamic_cast<PointLight*>(light))
		{
			L = pl->getPosition() - intersectionPoint;
		}
		Ray secondaryRay(intersectionPoint+glm::normalize(L)*0.001f, glm::normalize(L));
		for (int j = 0; j < m_geometries.size(); j++)
		{
			Geometry* g = m_geometries.at(j);
			if (g->hit(secondaryRay, dist))
			{
				visible = 0;
				break;
			}
		}
		N = geo->getNormal(intersectionPoint);

		L = glm::normalize(L);
		// Diffuse
		float dot = glm::dot(L, N)*visible;
		vec3 diffuse, specular;
		if (dot > 0)
		{

			diffuse = light->getColor() * geo->getMaterial()->getDiffuse() * dot * 255.0f;
		}

		// Specular
		vec3 V = ray.getDirection();
		vec3 R = L - 2.0f * glm::dot(L, N) * N;
		dot = glm::dot(V,R)*visible;
		if (dot > 0)
		{
			vec3 spec = powf(dot,geo->getMaterial()->getShininess()) * geo->getMaterial()->getSpecular();
			specular = light->getColor() * geo->getMaterial()->getSpecular() * spec * 255.0f;
		}
		outColor += /*geo->getMaterial()->getAmbient()*255.0f*/ diffuse + specular;
		//REFLECTION
		if (depth < m_maxDepth)
		{
			vec3 R1 = ray.getDirection() - 2.0f * glm::dot(ray.getDirection(), N) * N;
			outColor += trace(Ray(intersectionPoint +  glm::normalize(R1) * 0.01f, glm::normalize(R1)), depth+1);
		}

		

	}
	return geo->getMaterial()->getAmbient()*255.0f + outColor;
	
}

void Scene::render(Camera* camera, Screen* screen)
{
	float angle = tan(M_PI * 0.5 * camera->getFov() / 180.); 
	for (int i = 0; i < screen->getHeight(); i++)
	{
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