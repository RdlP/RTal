#include "Sphere.hpp"

#include <iostream>

Sphere::Sphere(vec3 center, float radius, mat4 transform):
	Geometry(transform), m_radius(radius), m_center(center)
{

}

Sphere::~Sphere()
{

}

Intersection Sphere::hit(Ray ray)
{
	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));

	// R(t) = o + td
	// (p-c)·(p-c) - r² = 0 =>
	// (o + td - c) · (o + td - c) - r² = 0 =>
	// t²(D·D) + 2t(d · (o - c)) + (o - c) · (o - c) - r² = 0
	vec3 m = ray.getOrigin() - m_center;

	float a = glm::dot(ray.getDirection(), ray.getDirection());
	float b = 2 * glm::dot(ray.getDirection(), m);
	float c = glm::dot(m,m)-m_radius*m_radius;
	float discr = b*b - 4*a*c;
	if (discr < 0)
	{
		return Intersection(false);
	}

	float x1 = (-b+sqrt(discr))/(2*a);
	float x2 = (-b-sqrt(discr))/(2*a);

	float t; 
	if (x1 > x2)
	{
		t=x2;
	}

	if (t < 0)
	{
		t=x1;
	}


	if (t<0)
	{
		return Intersection(false);
	}
	vec3 point = ray.getOrigin() + ray.getDirection()*t;

	if (x2 >= 0 && x1 < 0)
	{
		return Intersection(true,point,glm::normalize(point-m_center), true);
	}else if (x1 >= 0 && x2 < 0)
	{
		return Intersection(true,point,glm::normalize(point-m_center), true);
	}

	return Intersection(true,point,glm::normalize(point-m_center));
}