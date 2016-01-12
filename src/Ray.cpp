#include "Ray.hpp"

Ray::Ray(vec3 origin, vec3 dir)
	: m_origin(origin), m_dir(dir)
{

}

Ray::~Ray()
{

}

vec3 Ray::getOrigin()
{
	return m_origin;
}

vec3 Ray::getDirection()
{
	return m_dir;
}