#include "Light.hpp"

Light::Light(vec3 color)
: m_color(color)
{

}

Light::~Light()
{

}

void Light::setColor(vec3 color)
{
	m_color = color;
}

vec3 Light::getColor()
{
	return m_color;
}