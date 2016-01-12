#ifndef POINT_LIGHT_HEADER
#define POINT_LIGHT_HEADER

#include "Light.hpp"
#include "variables.h"

class PointLight : public Light {
	public:
		PointLight(vec3 position, vec3 color, vec3 attenuation);
		virtual ~PointLight();
		vec3 getPosition();
		void setPosition(vec3 position);
		vec3 getAttenuation();
		void setAttenuation(vec3 attenuation);

	private:
		vec3 m_position;
		vec3 m_attenuation;
};
#endif