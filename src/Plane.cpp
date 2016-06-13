#include "Plane.hpp"

Plane::Plane(vec3 point, vec3 normal, mat4 transform):
	m_point(point), m_normal(normal), Geometry(transform)
{
	
}

Plane::~Plane()
{
	
}

Intersection Plane::hit(Ray ray)
{

	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));

	// R(t) = o + td;
	// ax + by + cz = d => n·X=d
	// n·R(t) = d
	// n · [o + td] = d
	// n·o + nt·d = d
	// t = (d-n·o)/(n·d)
	float nd = glm::dot(m_normal,ray.getDirection());
	if (nd == 0) // PARAREL
	{
		return Intersection(false);
	}
	float d = glm::dot(m_normal, m_point);
	float t = (d-glm::dot(m_normal,ray.getOrigin())) / nd;
	if (t < 0)
	{
		return Intersection(false);
	}
	vec3 point = ray.getOrigin() + t * ray.getDirection();

	return Intersection(true, point, m_normal);
}