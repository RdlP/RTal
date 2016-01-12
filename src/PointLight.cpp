#include "PointLight.hpp"

PointLight::PointLight(vec3 position, vec3 color, vec3 attenuation)
: m_position(position), Light(color), m_attenuation(attenuation)
{

}

PointLight::~PointLight()
{

}

vec3 PointLight::getPosition()
{
	return m_position;
}

void PointLight::setPosition(vec3 position)
{
	m_position = position;
}

vec3 PointLight::getAttenuation()
{
	return m_attenuation;
}

void PointLight::setAttenuation(vec3 attenuation)
{
	m_attenuation = attenuation;
}