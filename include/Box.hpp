#ifndef BOX_HEADER
#define BOX_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>
#include <iostream>

class Box : public Geometry
{
	public:
		Box(float half[3], vec3 center, mat4 transform);
		virtual ~Box();
		Intersection hit(Ray ray);
	private:
		vec3 m_center;
		float m_half[3];
};

#endif