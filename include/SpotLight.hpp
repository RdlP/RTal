#ifndef SPOT_LIGHT_HEADER
#define SPOT_LIGHT_HEADER

#include "PointLight.hpp"
#include "variables.h"

class SpotLight : public PointLight {
	public:
		SpotLight(vec3 position, vec3 color, vec3 direction);
		virtual ~SpotLight();
		vec3 getDirection();
		void setDirection(vec3 position);
		float getExponent();
		void setExponent(float exponent);
		float getCosCutOff();
		void setCosCutOff(float cosCutOff);

	private:
		vec3 m_dir;
		float m_cosCutOff, m_exponent;
};
#endif