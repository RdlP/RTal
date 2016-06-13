#ifndef MATERIAL_HEADER
#define MATERIAL_HEADER
#include "variables.h"


class Material
{
	public:
		Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 emission, float shininess);
		virtual ~Material();
		vec3 getAmbient();
		void setAmbient(vec3 ambient);
		vec3 getDiffuse();
		void setDiffuse(vec3 diffuse);
		vec3 getSpecular();
		void setSpecular(vec3 specular);
		vec3 getEmission();
		void setEmission(vec3 emission);
		float getShininess();
		void setShininess(float shininess);
		float getRefractionIndex();
		void setRefractionIndex(float iRefrac);
	private:
		vec3 m_ambient;
		vec3 m_diffuse;
		vec3 m_specular;
		vec3 m_emission;
		float m_shininess;
		float m_iRefrac;
};
#endif