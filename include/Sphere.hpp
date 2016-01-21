#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Geometry.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>

class Sphere : public Geometry
{
	public:
		Sphere(vec3 center, float radius, mat4 transform);
		virtual ~Sphere();
		int hit(Ray ray, vec3 &point);
		vec3 getNormal(vec3 point);
	private:
		vec3 m_center;
		float m_radius;
};

#endif