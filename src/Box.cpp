#include "Box.hpp"

Box::Box(float half[3], vec3 center, mat4 transform):
	m_center(center), Geometry(transform)
{
	m_half[0] = half[0];
	m_half[1] = half[1];
	m_half[2] = half[2];
}

Box::~Box()
{
	
}

Intersection Box::hit(Ray ray)
{

	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));


	vec3 p = m_center - ray.getOrigin();
	float tmin = -99999999.0f;
	float tmax = 99999999.0f;
	float t1,t2;
	vec3 axisX(1,0,0), axisY(0,1,0), axisZ(0,0,1);
	vec3 axis[3] = {axisX,axisY,axisZ};
	int nearNormal, farNormal;
	for (int i = 0; i < 3; i++)
	{
		float e = glm::dot(axis[i],p);
		float f = glm::dot(axis[i],ray.getDirection());
		//std::cout << f << std::endl;
		if (f != 0)
		{
			t1 = (e+m_half[i])/f;
			t2 = (e-m_half[i])/f;
			if (t1 > t2)
			{
				std::swap(t1,t2);
			}
			if (t1 > tmin)
			{
				tmin = t1;
				nearNormal = i;
			}
			if (t2 < tmax)
			{
				tmax = t2;
				farNormal = i;
			}
			//std::cout << "tmin " << tmin << " tmax " << tmax << std::endl;
			if (tmin > tmax)
			{
				return Intersection(false);
			}
			
			if (tmax < 0)
			{
				//std::cout << tmax << std::endl;
				return Intersection(false);
			}

		}
		else if(-e -m_half[i] > 0 || -e +m_half[i] < 0)
		{
			return 0;
		}
	}
	
	
	
	if (tmin > 0)
	{
		vec3 normal = axis[nearNormal];
		//normal = axis[iNormal];
		//std::cout << "ABC: " << axis[iNormal].x << " " << axis[iNormal].y << " " << axis[iNormal].z << std::endl;
		//std::cout << iNormal << std::endl;
		//if ()
		if (glm::dot(ray.getDirection(),normal) > 0) 
		{
			
			normal = - normal;
		}

		return Intersection(true, ray.getOrigin() + ray.getDirection()*tmin, normal);
	}

	return Intersection(false);
}