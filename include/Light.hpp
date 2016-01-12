#ifndef LIGHT_HEADER
#define LIGHT_HEADER

#include "variables.h"

class Light {
	public:
		Light(vec3 color);
		virtual ~Light();
		vec3 getColor();
		void setColor(vec3 color);

	private:
		vec3 m_color;
};
#endif