#ifndef SPHERE_HEADER
#define SPHERE_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>

class Sphere : public Geometry
{
	public:
		Sphere(vec3 center, float radius, mat4 transform);
		virtual ~Sphere();
		Intersection hit(Ray ray);
	private:
		vec3 m_center;
		float m_radius;
};

#endif