#include "Sphere.hpp"

#include <iostream>

Sphere::Sphere(vec3 center, float radius, mat4 transform):
	Geometry(transform), m_radius(radius), m_center(center)
{

}

Sphere::~Sphere()
{

}

vec3 Sphere::getNormal(vec3 point)
{
	return glm::normalize(point-m_center);
}

int Sphere::hit(Ray& ray, float& dist)
{
	vec3 m = ray.getOrigin() - m_center;
	
	float b = glm::dot(m, ray.getDirection());
	
	float c = glm::dot(m,m) - m_radius*m_radius;
	
	if (c > 0.0f && b > 0.0f)
	{
		return 0;
	}
	float discr = b*b-c;
	if (discr < 0.0f)
	{
		return 0;
	}
	float t = -b - sqrt(discr);
	vec3 intersected = ray.getOrigin() + ray.getDirection()*t;
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