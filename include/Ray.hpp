#ifndef RAY_HEADER
#define RAY_HEADER

#include "variables.h"

class Ray {
	public:
		Ray(vec3 origin, vec3 dir);
		virtual ~Ray();
		void setOrigin(vec3 origin);
		vec3 getOrigin();
		void setDirection(vec3 direction);
		vec3 getDirection();

	private:
		vec3 m_origin, m_dir;
};
#endif