#ifndef PLANE_HEADER
#define PLANE_HEADER

#include "Geometry.hpp"
#include "Ray.hpp"
#include "Intersection.hpp"
#include "variables.h"
#include <math.h>

class Plane : public Geometry
{
	public:
		Plane(vec3 point, vec3 normal, mat4 transform);
		virtual ~Plane();
		Intersection hit(Ray ray);
	private:
		vec3 m_point, m_normal;
};

#endif