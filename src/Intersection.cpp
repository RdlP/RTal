#include "Intersection.hpp"

#include <iostream>

Intersection::Intersection()
{

}

Intersection::Intersection(bool intersection, vec3 point, vec3 normal):
	m_intersection(intersection), m_point(point), m_normal(normal), m_inside(false)
{

}

Intersection::Intersection(bool intersection, vec3 point, vec3 normal, bool inside):
	m_intersection(intersection), m_point(point), m_normal(normal), m_inside(inside)
{

}

Intersection::Intersection(bool intersection):
	m_intersection(intersection)
{

}

Intersection::~Intersection()
{
	m_intersection = false;
}

bool Intersection::isIntersection()
{
	return m_intersection;
}

void Intersection::setIntersection(bool intersection)
{
	m_intersection = intersection;
}

vec3 Intersection::getPoint()
{
	return m_point;
}

void Intersection::setPoint(vec3 point)
{
	m_point = point;
}

vec3 Intersection::getNormal()
{
	return m_normal;
}

void Intersection::setNormal(vec3 normal)
{
	m_normal = normal;
}

bool Intersection::isInside()
{
	return m_inside;
}

void Intersection::setInside(bool inside)
{
	m_inside = inside;
}
