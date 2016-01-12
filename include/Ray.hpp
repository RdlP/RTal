#ifndef RAY_HEADER
#define RAY_HEADER

#include "variables.h"

class Ray {
	public:
		Ray(vec3 origin, vec3 dir);
		virtual ~Ray();
		vec3 getOrigin();
		vec3 getDirection();

	private:
		vec3 m_origin, m_dir;
};
#endif