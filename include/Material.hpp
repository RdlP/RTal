#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER
#include "variables.h"


class Material
{
	public:
		Material(vec3 ambient, vec3 diffuse, vec3 specular, float shininess);
		virtual ~Material();
		vec3 getAmbient();
		vec3 getDiffuse();
		vec3 getSpecular();
		float getShininess();
	private:
		vec3 m_ambient;
		vec3 m_diffuse;
		vec3 m_specular;
		float m_shininess;
};
#endif