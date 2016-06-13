#ifndef CONE_HEADER
#define CONE_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>

class Cone : public Geometry
{
	public:
		Cone(float height, float radius, mat4 transform);
		virtual ~Cone();
		Intersection hit(Ray ray);
	private:
		float m_height, m_radius;
};

#endif