#ifndef DIRECTIONAL_LIGHT_HEADER
#define DIRECTIONAL_LIGHT_HEADER

#include "Light.hpp"
#include "variables.h"

class DirectionalLight : public Light {
	public:
		DirectionalLight(vec3 direction, vec3 color);
		virtual ~DirectionalLight();
		vec3 getDirection();
		void setDirection(vec3 direction);

	private:
		vec3 m_direction;
};
#endif