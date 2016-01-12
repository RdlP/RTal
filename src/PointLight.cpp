#include "PointLight.hpp"

PointLight::PointLight(vec3 position, vec3 color)
: m_position(position), Light(color), 
	m_constantAttenuation(1.0f), m_linearAttenuation(0.1f), m_quadraticAttenuation(0.01f)
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

float PointLight::getConstantAttenuation()
{
	return m_constantAttenuation;
}

void PointLight::setConstantAttenuation(float constantAttenuation)
{
	m_constantAttenuation = constantAttenuation;
}

float PointLight::getLinearAttenuation()
{
	return m_linearAttenuation;
}

void PointLight::setLinearAttenuation(float linearAttenuation)
{
	m_linearAttenuation = linearAttenuation;
}

float PointLight::getQuadraticAttenuation()
{
	return m_quadraticAttenuation;
}

void PointLight::setQuadraticAttenuation(float quadraticAttenuation)
{
	m_quadraticAttenuation = quadraticAttenuation;
}

void PointLight::setAttenuation(float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
{
	m_constantAttenuation = constantAttenuation;
	m_linearAttenuation = linearAttenuation;
	m_quadraticAttenuation = quadraticAttenuation;
}

void PointLight::setAttenuation(vec3 attenuation)
{
	m_constantAttenuation = attenuation.x;
	m_linearAttenuation = attenuation.y;
	m_quadraticAttenuation = attenuation.z;
}