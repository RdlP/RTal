#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Geometry.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <iostream>

class Triangle : public Geometry
{
	public:
		Triangle(vec3 a, vec3 b, vec3 c, mat4 transform);
		virtual ~Triangle();
		int hit(Ray& ray, float &dist);
		vec3 getNormal(vec3 point);
	private:
		vec3 m_a, m_b, m_c;
};

#endif