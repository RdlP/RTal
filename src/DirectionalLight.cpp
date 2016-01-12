#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(vec3 direction, vec3 color)
: m_direction(direction), Light(color)
{

}

DirectionalLight::~DirectionalLight()
{

}

vec3 DirectionalLight::getDirection()
{
	return m_direction;
}

void DirectionalLight::setDirection(vec3 direction)
{
	m_direction = direction;
}