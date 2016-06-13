#include "Material.hpp"

Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission, float shininess):
	m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_emission(emission), m_shininess(shininess)
{

}

Material::~Material()
{

}

vec3 Material::getAmbient()
{
	return m_ambient;
}

void Material::setAmbient(vec3 ambient)
{
	m_ambient = ambient;
}

vec3 Material::getDiffuse()
{
	return m_diffuse;
}

void Material::setDiffuse(vec3 diffuse)
{
	m_diffuse = diffuse;
}

vec3 Material::getSpecular()
{
	return m_specular;
}

void Material::setSpecular(vec3 specular)
{
	m_specular = specular;
}

vec3 Material::getEmission()
{
	return m_emission;
}

void Material::setEmission(vec3 emission)
{
	m_emission = emission;
}

float Material::getShininess()
{
	return m_shininess;
}

void Material::setShininess(float shininess)
{
	m_shininess = shininess;
}

float Material::getRefractionIndex()
{
	return m_iRefrac;
}

void Material::setRefractionIndex(float iRefrac)
{
	m_iRefrac = iRefrac;
}