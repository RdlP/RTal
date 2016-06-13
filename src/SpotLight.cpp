#include "SpotLight.hpp"

SpotLight::SpotLight(vec3 position, vec3 color, vec3 direction)
: PointLight(position,color), m_dir(direction), 
	m_exponent(1.0f), m_cosCutOff(0.1f)
{

}

SpotLight::~SpotLight()
{

}

vec3 SpotLight::getDirection()
{
	return m_dir;
}

void SpotLight::setDirection(vec3 direction)
{
	m_dir = direction;
}

float SpotLight::getExponent()
{
	return m_exponent;
}

void SpotLight::setExponent(float exponent)
{
	m_exponent = exponent;
}

float SpotLight::getCosCutOff()
{
	return m_cosCutOff;
}

void SpotLight::setCosCutOff(float cosCutOff)
{
	m_cosCutOff = cosCutOff;
}