#ifndef INTERSECTION_HEADER
#define INTERSECTION_HEADER

#include "variables.h"
#include <math.h>

class Intersection
{
	public:
		Intersection();
		Intersection(bool intersection, vec3 point, vec3 normal);
		Intersection(bool intersection, vec3 point, vec3 normal, bool inside);
		Intersection(bool intersection);
		virtual ~Intersection();
		bool isIntersection();
		void setIntersection(bool intersection);
		vec3 getPoint();
		void setPoint(vec3 point);
		vec3 getNormal();
		void setNormal(vec3 normal);
		bool isInside();
		void setInside(bool inside);
	private:
		vec3 m_normal, m_point;
		bool m_intersection, m_inside;
};

#endif