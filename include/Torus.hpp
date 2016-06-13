#ifndef TORUS_HEADER
#define TORUS_HEADER

#include "Geometry.hpp"
#include "Intersection.hpp"
#include "Ray.hpp"
#include "variables.h"
#include <math.h>

class Torus : public Geometry
{
	public:
		Torus(float radius1, float radius2, mat4 transform);
		virtual ~Torus();
		Intersection hit(Ray ray);
		int solveQuartic(float a, float b, float c, float d, float& root1, float& root2, float& root3, float& root4);
		int solveCubic(float a, float b, float c, float& root1, float& root2, float& root3);
		int solveQuadratic(float a, float b, float c, float& root1, float& root2);
	private:
		float m_radius1, m_radius2;
};

#endif