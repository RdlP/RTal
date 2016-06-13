#ifndef TRIANGLE_HEADER
#define TRIANGLE_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <iostream>

class Triangle : public Geometry
{
	public:
		Triangle(vec3 a, vec3 b, vec3 c, mat4 transform);
		virtual ~Triangle();
		Intersection hit(Ray ray);
	private:
		vec3 m_a, m_b, m_c;
};

#endif