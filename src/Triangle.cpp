#include "Triangle.hpp"

Triangle::Triangle(vec3 a, vec3 b, vec3 c, mat4 transform):
	m_a(a), m_b(b), m_c(c), Geometry(transform)
{
	
}

Triangle::~Triangle()
{
	
}

vec3 Triangle::getNormal(vec3 point)
{
	vec3 e1 = m_b-m_a;
	vec3 e2 = m_c-m_a;
	vec3 n = glm::normalize(glm::cross(e1,e2));
	return n;
}

int Triangle::hit(Ray& ray, float &dist)
{
	vec3 e1 = m_b-m_a;
	vec3 e2 = m_c-m_a;
	vec3 dir = ray.getDirection();
	vec3 q = glm::cross(dir, e2);
	float a = glm::dot(e1,q);
	if (a <= 0.0f)
	{
		return 0;
	}

	float f = 1/a;
	vec3 s = ray.getOrigin() - m_a;
	float u = f*glm::dot(s,q);
	if (u < 0.0f)
	{
		return 0;
	}

	vec3 r = glm::cross(s,e1);
	float v = f*glm::dot(dir,r);
	if (v < 0.0f || u+v > 1.0f)
	{
		return 0;
	}

	float t= f*glm::dot(e2,r);
	float w = 1.0f - v - u;

	vec3 intersected = m_a*w + m_b*u + m_c*v;
	float distance = sqrt((intersected.x-ray.getOrigin().x)*(intersected.x-ray.getOrigin().x)+
		(intersected.y-ray.getOrigin().y)*(intersected.y-ray.getOrigin().y)+
		(intersected.z-ray.getOrigin().z)*(intersected.z-ray.getOrigin().z));
	if (distance > dist)
	{
		return 0;
	}
	dist = distance;

	return 1;
}