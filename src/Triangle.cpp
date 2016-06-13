#include "Triangle.hpp"

Triangle::Triangle(vec3 a, vec3 b, vec3 c, mat4 transform):
	m_a(a), m_b(b), m_c(c), Geometry(transform)
{
	
}

Triangle::~Triangle()
{
	
}

Intersection Triangle::hit(Ray ray)
{

	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));

	// R(t) = o + td;
	// ax + by + cz = d => n·X=d
	// n·R(t) = d
	// n · [o + td] = d
	// n·o + nt·d = d
	// t = (d-n·o)/(n·d)
	vec3 ab = m_b-m_a;
	vec3 ac = m_c-m_a;
	vec3 normal = glm::normalize(glm::cross(ab,ac));
	float nd = glm::dot(normal,ray.getDirection());
	if (nd == 0) // PARAREL
	{
		return Intersection(false);
	}
	float d = glm::dot(normal, m_a);
	float t = (d-glm::dot(normal,ray.getOrigin())) / nd;
	if (t < 0)
	{
		return Intersection(false);
	}
	vec3 pointq = ray.getOrigin() + t * ray.getDirection();
	vec3 ap = pointq - m_a; 
	vec3 bp = pointq - m_b; 
	vec3 cp = pointq - m_c; 
	vec3 bc = m_c - m_b;
	vec3 ca = m_a - m_c;

	float e1 = glm::dot(glm::cross(ab, ap),normal);
	float e2 = glm::dot(glm::cross(bc, bp),normal);
	float e3 = glm::dot(glm::cross(ca, cp),normal);

	if (e1 < 0 || e2 < 0 || e3 < 0)
	{
		return Intersection(false);
	}
	float dom = glm::dot(glm::cross(ab, ac),normal);
	float alpha = e2 /dom;
	float beta = e3/dom;
	float gamma = e1/dom;


	vec3 point = m_a*alpha + m_b*beta + m_c*gamma;

	return Intersection(true, point, normal);
}