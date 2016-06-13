#ifndef CYLINDER_HEADER
#define CYLINDER_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>

class Cylinder : public Geometry
{
	public:
		Cylinder(float radius, float height, mat4 transform);
		virtual ~Cylinder();
		Intersection hit(Ray ray);
	private:
		float m_radius, m_height;
};

#endif