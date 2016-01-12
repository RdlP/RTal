#include "Ray.hpp"

Ray::Ray(vec3 origin, vec3 dir)
	: m_origin(origin), m_dir(dir)
{

}

Ray::~Ray()
{

}

void Ray::setOrigin(vec3 origin)
{
	m_origin = origin;
}

vec3 Ray::getOrigin()
{
	return m_origin;
}

void Ray::setDirection(vec3 direction)
{
	m_dir = direction;
}

vec3 Ray::getDirection()
{
	return m_dir;
}