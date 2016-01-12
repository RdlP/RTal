#ifndef POINT_LIGHT_HEADER
#define POINT_LIGHT_HEADER

#include "Light.hpp"
#include "variables.h"

class PointLight : public Light {
	public:
		PointLight(vec3 position, vec3 color);
		virtual ~PointLight();
		vec3 getPosition();
		void setPosition(vec3 position);
		float getConstantAttenuation();
		void setConstantAttenuation(float constant);
		float getLinearAttenuation();
		void setLinearAttenuation(float linear);
		float getQuadraticAttenuation();
		void setQuadraticAttenuation(float quadratic);
		void setAttenuation(vec3 attenuation);
		void setAttenuation(float constant, float linear, float quadratic);

	private:
		vec3 m_position;
		float m_constantAttenuation, m_linearAttenuation, m_quadraticAttenuation;
};
#endif