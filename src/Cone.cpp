#include "Cone.hpp"

#include <iostream>

Cone::Cone(float height, float radius, mat4 transform):
	Geometry(transform), m_height(height), m_radius(radius)
{

}

Cone::~Cone()
{

}

Intersection Cone::hit(Ray ray)
{
	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));

	// R(t) = o + td
	// (hx/r)² - (y - h)² + (hz/r)² = 0
	// (h(ox+tdx)/r)² - (oy+tdy - h)² + (h(oz+tdz)/r)² = 0
	// h²(ox² + (tdx)² + 2oxtdx)/r² - ((oy+tdy)² + h² - 2h(oy+tdy)) + h²(oz² + (tdz)² + 2oztdz)/r² = 0
	// h²(ox² + (tdx)² + 2oxtdx)/r² - (oy² + (tdy)² + 2oytdy  + h² - 2h(oy+tdy)) + h²(oz² + (tdz)² + 2oztdz)/r² = 0
	// h²t²dx²/r² - t²dy² + h²t²dz²/r² + h²2oxtdx/r² - 2oytdy + 2htdy + h²2oztdz/r² + h²ox²/r² - oy² - h² + 2hoy + h²oz²/r² = 0
	// (h²dx²/r² - dy² + h²dz²/r²)t² + (h²2oxdx/r² - 2oydy + 2hdy + h²2ozdz/r²)t + h²ox²/r² - oy² - h² + 2hoy + h²oz²/r² = 0
	// a = h²dx²/r² - dy² + h²dz²/r²
	// b = h²2oxdx/r² - 2oydy + 2hdy + h²2ozdz/r²
	// c = h²ox²/r² - oy² - h² + 2hoy + h²oz²/r²
	vec3 o = ray.getOrigin();
	vec3 d = ray.getDirection();
	float a = (m_height*m_height*d.x*d.x)/(m_radius*m_radius) - d.y*d.y + (m_height*m_height*d.z*d.z)/(m_radius*m_radius);
	float b = (m_height*m_height*2*o.x*d.x)/(m_radius*m_radius) - 2*o.y*d.y + (m_height*m_height*2*o.z*d.z)/(m_radius*m_radius) + 2*m_height*d.y;
	float c = (m_height*m_height*o.x*o.x)/(m_radius*m_radius) - o.y*o.y - m_height*m_height + 2*m_height*o.y + (m_height*m_height*o.z*o.z)/(m_radius*m_radius);
	
	float discr = b*b - 4*a*c;
	
	if (discr < 0)
	{
		return Intersection(false);
	}

	float x1 = (-b+sqrt(discr))/(2*a);
	float x2 = (-b-sqrt(discr))/(2*a);

	float t;
	//choose the smallest and >=0 t
	if (x1 > x2)
	{
		t=x2;
	}

	if (t < 0)
	{
		t=x1;
	}


	// if both solution are <0 => NO INTERSECTION!
	

	if (t<0)
	{
		return Intersection(false);
	}

	// normal calculation
	// f(x,y) = x² + z² - r² = 0
	// T = (dx/dt, y, dz/dt)
	// 0 = df/dt = (df/dx, y, df/dz) · T
	// N = (2x, 0, 2z)
	vec3 point = ray.getOrigin() + ray.getDirection()*t;
	vec3 normal = vec3(2*m_height*point.x/m_radius, -2*(point.y - m_height), 2*m_height*point.z/m_radius);
	normal = glm::normalize(normal);
	//normal = glm::normalize(normal);


	// If the y-component from point computed is smaller than 0 or bigger than height => NO INTERSECTION!
	
	
	//If ray direction is not pararel to Y Plane
	if (ray.getDirection().y != 0.0f) //Paralel
	{
		//Compute t's for point intersection in the Y Plane
		float t2 = (0-ray.getOrigin().y)/ray.getDirection().y;

		if (t2 >= 0)
		{
			// If there is a t >= 0 compute de point and check if the point is inside the cap
			vec3 point1 = ray.getOrigin() + ray.getDirection()*t2;
			//std::cout << "point " << point1.y << " hipo "  << point1.x*point1.x + point1.z*point1.z << " radio " << m_radius*m_radius << std::endl;
			if (point1.x*point1.x + point1.z*point1.z <= m_radius*m_radius)
			{

				if (point.y < 0 || point.y > m_height)
				{
					//return Intersection(false);
					t=99999999.0;
				}
				// Intersection point is inside cap but, Which t is the smallest? t from cap or t from body cylinder?
				// I choose the smallest t and check if the t is from cap and compute normal and return intersection.
				t = std::min(t,t2);

				if (t == t2)
				{
					normal = vec3(0.0f,-1.0f,0.0f);
					return Intersection(true, point1, normal);
				}
			}
		}
	}

	// Intersection in the body cylinder, compute the point and return the intersection
	point = ray.getOrigin() + ray.getDirection()*t;

	if (point.y < 0 || point.y > m_height)
	{
		return Intersection(false);
	}

	return Intersection(true, point, normal);
}