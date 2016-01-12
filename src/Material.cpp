#include "Material.hpp"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, float shininess):
	m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{

}

Material::~Material()
{

}

vec3 Material::getAmbient()
{
	return m_ambient;
}

vec3 Material::getDiffuse()
{
	return m_diffuse;
}

vec3 Material::getSpecular()
{
	return m_specular;
}

float Material::getShininess()
{
	return m_shininess;
}