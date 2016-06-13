#include "Torus.hpp"

#include <iostream>

Torus::Torus(float radius1, float radius2, mat4 transform):
	Geometry(transform), m_radius1(radius1), m_radius2(radius2)
{

}

Torus::~Torus()
{

}

int Torus::solveCubic(float a, float b, float c, float& root1, float& root2, float& root3)
{
	float p = ((-1.0f/3.0f) * powf(a,2) + b)/3.0f;
	p = (-1.0f/9.0f)*a*a + (1.0f/3.0f)*b;
	float q = ((2.0f/27.0f) * powf(a,3) - (1.0f/3.0f)*a*b + c)/2.0f;
	q = (1.0f/27.0f)*a*a*a - (1.0f/6.0f)*a*b + (1.0f/2.0f) *c;
	float D = -(powf(p,3) + powf(q,2));

	if (D < 0.0f)
	{
		float r = powf((-q + sqrt(-D)),1.0f/3.0f);
		float s = powf((-q - sqrt(-D)),1.0f/3.0f);
		root1 = (r+s) - a/3.0f;
		return 1;
	}
	else if (D == 0.0f)
	{
		float r = powf((-q + sqrt(-D)),1.0f/3.0f);
		float s = powf((-q - sqrt(-D)),1.0f/3.0f);
		root1 = (r+s) - a/3.0f;
		root2 = root3 = (-r) - a/3.0f;
		return 2;
	}
	else if (D > 0.0f)
	{
		// CHECK p < 0
		if (p > 0.0f)
		{
			return 0;
		}
		float theta = (1.0f/3.0f) * acos(-q/sqrt(powf(-p,3)));
		root1 = (2*sqrt(-p)*cos(theta)) - a/3.0f;
		root2 = (2*sqrt(-p)*cos(theta + (2.0f*3.1415f)/3.0f)) - a/3.0f;
		root3 = (2*sqrt(-p)*cos(theta - (2.0f*3.1415f)/3.0f)) - a/3.0f;
		return 3;
	}
}

int Torus::solveQuartic(float a, float b, float c, float d, float& root1, float& root2, float& root3, float& root4)
{
	float p = (-3.0f/8.0f)*powf(a,2) + b;
	float q = (1.0f/8.0f)*powf(a,3) - (1.0f/2.0f)*a*b + c;
	float r = (-3.0f/256.0f)*powf(a,4) + (1.0f/16.0f)*powf(a,2)*b - (1.0f/4.0f)*a*c + d;
	//int nroots = solveCubic(-p/2.0f, -r, (4*r*p-powf(q,2))/8.0f, root1, root2, root3);
	int nroots = solveCubic(p/2.0f, (p*p-4*r)/16.0f, (-q*q)/64.0f, root1, root2, root3);
	
	//std::cout << root1 << std::endl;
	if (nroots == 0)
	{
		return 0;
	}
	float y = root1;
	if (y != y){
		y = root2;
	}
	if (y != y){
		y=root3;
	}
	int nroots1, nroots2;
	std::cout << "y " << y << " a " << a << " b " << b << " p " << p << " r " << r << std::endl;
	root1 = root2 = root3 = root4 = -1;
	if (q >= 0)
	{
		std::cout << " a " << 1 << " b " << sqrt(2*y - p) << " c " << y - sqrt(powf(y,2)-r) << std::endl;
		nroots1 = solveQuadratic(1.0f, sqrt(2*y - p), y - sqrt(powf(y,2)-r), root1, root2);
		std::cout << " a " << 1 << " b " << -sqrt(2*y - p) << " c " << y + sqrt(powf(y,2)-r) << std::endl;
		nroots2 = solveQuadratic(1.0f, -sqrt(2*y - p), y + sqrt(powf(y,2)-r), root3, root4);
		//std::cout << " root1 " << root1 << " root2 " << root2 << " root3 " << root3 << " root4 " << root4 << std::endl;
		if (nroots1 != 0)
		{
			root1 -= a/4.0f;
			root2 -= a/4.0f;
			std::cout << "solucion" << std::endl;
		}
		if (nroots2 != 0)
		{
			root3 -= a/4.0f;
			root4 -= a/4.0f;
			std::cout << "solucion" << std::endl;
		}

		return nroots1+nroots2;
	}
	else
	{
		//std::cout << "y " << y << " p " << p << " r " << r << std::endl;
		std::cout << " a " << 1 << " b " << sqrt(2*y - p) << " c " << y + sqrt(powf(y,2)-r) << std::endl;
		nroots1 = solveQuadratic(1.0f, sqrt(2*y - p), y + sqrt(powf(y,2)-r), root1, root2);
		std::cout << " a " << 1 << " b " << -sqrt(2*y - p) << " c " << y - sqrt(powf(y,2)-r) << std::endl;
		nroots2 = solveQuadratic(1.0f, -sqrt(2*y - p), y - sqrt(powf(y,2)-r), root3, root4);
		//std::cout << " root1 " << root1 << " root2 " << root2 << " root3 " << root3 << " root4 " << root4 << std::endl;

		if (nroots1 != 0)
		{
			root1 -= a/4.0f;
			root2 -= a/4.0f;
			std::cout << "solucion" << std::endl;
		}
		if (nroots2 != 0)
		{
			root3 -= a/4.0f;
			root4 -= a/4.0f;
			std::cout << "solucion" << std::endl;
		}

		return nroots1+nroots2;
	}

	std::cout << "root1" << root1 << std::endl;
	std::cout << "root2" << root2 << std::endl;
	std::cout << "root3" << root3 << std::endl;
	std::cout << "root4" << root4 << std::endl;
	
	
}

int Torus::solveQuadratic(float a, float b, float c, float& root1, float& root2)
{
	float D = b*b - 4*a*c;
	if (D < 0.0f)
	{
		return 0;
	}

	root1 = (-b + sqrt(D)) / 2.0f*a;
	root2 = (-b - sqrt(D)) / 2.0f*a;

	return 2;
}

Intersection Torus::hit(Ray ray)
{
	ray.setOrigin(vec3(getInverseTransform() * vec4(ray.getOrigin(),1)));
	ray.setDirection(glm::normalize(vec3(getInverseTransform() * vec4(ray.getDirection(),0))));

	// (a + b)² = (a² + b² + 2ab) * (a + b) = a³ + ab² + 2a²b + a²b + b³ + 2ab² = a³ + 3a²b + 3ab² + b³ 

	// R(t) = o + td
	// s² + z² = r2²; s = sqrt(x² + y²) - r1
	// (sqrt(x² + y²) - r1)² + z² = r2²
	// x² + y² + z² + r1² - r2² - 2r1sqrt(x² + y²) = 0
	// (x² + y² + z² + r1² - r2²)² = 4r1²(x² + y²)
	// [(ox + tdx)² + (oy + tdy)² + (oz + tdz)² + r1² - r2²]² = 4r1²[(ox + tdx)² + (oy + tdy)²]
	// [(ox² + (tdx)² + 2toxdx) + (oy² + (tdy)² + 2toydy) + (oz² + (tdz)² + 2tozdz) + r1² - r2²]² = 4r1²[(ox² + (tdx)² + 2toxdx) + (oy² + (tdy)² + 2toydy)]
	// [(tdx)² + (tdy)² + (tdz)² + 2toxdx + 2toydy + 2tozdz + ox² + oy² + oz² + r1² - r2²] = 4r1²[ox² + oy² + (tdx)² + (tdy)² 2toxdx + 2toydy]
	// [t²(d·d) + 2t(o·d) + (o·o) + r1² - r2²]² = 4r1²ox² + 4r1²oy² + 4r1²(tdx)² + 4r1²(tdy)² + 8r1²toxdx + 8r1²toydy
	// a = d·d; 
	// b=2(o·d); 
	// c=(o·o) + r1² - r2²
	// [at² + bt + c]² = 4r1²ox² + 4r1²oy² + 4r1²(tdx)² + 4r1²(tdy)² + 8r1²toxdx + 8r1²toydy
	// (at² + bt + c)(at² + bt + c) = a²t⁴ + abt³ + act² + bat³ + b²t² + bct + cat² + cbt + c² = a²t⁴ + b²t² + c² + 2cat² + 2bat³ 2cbt
	// a²t⁴ + b²t² + c² + 2cat² + 2bat³ 2cbt = 4r1²ox² + 4r1²oy² + 4r1²(tdx)² + 4r1²(tdy)² + 8r1²toxdx + 8r1²toydy
	// (d·d)²t⁴ + (2(o·d))²t² + ((o·o) + r1² - r2²)² + 2(((o·o) + r1² - r2²))(d·d)t² + 2(2(o·d))(d·d)t³ + 2((o·o) + r1² - r2²)(2(o·d))t = 4r1²ox² + 4r1²oy² + 4r1²(tdx)² + 4r1²(tdy)² + 8r1²toxdx + 8r1²toydy

	// a = (d·d)²;
	// b = 4(o·d)(d·d);
	// c = 4(o·d)² + 2(d·d)(o·o) + 2r1²(d·d) - 2r2²(d·d) - 4r1²dx² - 4r1²dy²;
	// d = 2((o·o) + r1² - r2²)(2(o·d)) - 8r1²oxdx - 8r1²oydy
	// e = ((o·o) + r1² - r2²)² - 4r1²ox² - 4r1²oy²
	// at⁴ + bt³ + ct² + dt + e = 0

	// at⁴ + bt³ + ct² + dt + e = 0 => t⁴ + bt³ + ct² + dt + e = 0 => En esta ecuación concreta esto se consigue normalizando el vector d
	// t⁴ + bt³ + ct² + dt + e = 0 => QUARTIC EQUATION

	// t = x - (a/4);
	// p4 = (-3/8)a² + b;
	// q4 = (1/8)a³ - (1/2)ab + c;
	// r4 = (-3/256)a⁴ + (1/16)a²b - (1/4)ac + d;
	// x⁴ + px² + qx + r = 0 => DEPRESSED QUARTIC EQUATION
	// y³ - (p/2)y² - ry + ((4rp-q²)/8) = 0 => CUBIC EQUATION;
	// y = z - (a/3);
	// p3 = (-1/3)a² + b;
	// q3 = (2/27)a³ - (1/3)ab + c;
	// z³ + p3z + q3 = 0 => DEPRESSED CUBI EQUATION
	//
	// D = -4p³ - 27q²
	// r3 = ((-1/2)q + sqrt((-1/108)D))^(1/3)
	// s3 = ((-1/2)q - sqrt((-1/108)D))^(1/3)
	// z1 = r + s; z2 = pr3 + p²s; z3 = p²r + ps; => p = (-1/2) + i (sqrt(3)/2)
	// p3' = p3/3 = (-1/9)a² + (1/3)b; q3' = q3/2 = (1/27)a³ - (-1/6)ab + (1/2)c
	// D = -108(p3'³ + q3'²); => D' = D/108 = -(p3'³ + q3'²)
	// r3 = ((-1/2)q + sqrt((-1/108)D))^(1/3) = (-q3' + sqrt(-D'))^(1/3)
	// s3 = ((-1/2)q - sqrt((-1/108)D))^(1/3) = (-q3' - sqrt(-D'))^(1/3)
	// SI D' < 0 => 1 SOLUCIÓN dada por z1 = r3 + s3;
	// SI D' = 0 r3=s3 => 2 SOLUCIONES => z1 = r3 + s3 = 2s3; z2,z3 = (p + p²)r = -r;
	// SI D' > 0 => 3 SOLUCIONES:
	//		z³ + p3z + q3 = 0 		4cos³0 - 3cos0 = cos30;		z = 2mcos0;		m = sqrt(-p/3);
	//		8m³cos³0 + 2pmcos0 + q3 = 0; p = -3m²;
	//		2m³(4cos³0 - 3cos0) + q3 = 0 => 2m³cos30 + q3 = 0 => cos30 = (-q3/2m³) = (-q3/2)/sqrt(-p3³/27) = (-q3'/sqrt(-p'³)):
	//		0 = (1/3)cos^-1 (-q3'/sqrt(-p'³));
	//		z1 = 2mcos0 = 2sqrt(-p3')cos0;
	//		cos(30 + 2PIk) = cos(30) => 0k = (1/3)cos^-1 (-q3'/sqrt(-p'³))- (2PI/3)k;
	//		x2 = 2sqrt(-p3')cos(0 + (2PI/3));		x3 = 2sqrt(-p3')cos(0 - (2PI/3))
	vec3 dir = ray.getDirection(), o = ray.getOrigin();
	float a = powf(glm::dot(dir, dir),2);
	float b = 4 * glm::dot(o, dir) * glm::dot(dir, dir);
	b = 4 * glm::dot(o, dir);
	float c = 4 * powf(glm::dot(o,dir),2) + 2 * glm::dot(dir,dir)*glm::dot(o,o) + 2*m_radius1*m_radius1*glm::dot(dir,dir) + 2*m_radius2*m_radius2*glm::dot(dir,dir) - 4*m_radius1*m_radius1*dir.x*dir.x - 4*m_radius1*m_radius1*dir.y*dir.y;
	c = 2*glm::dot(dir,dir)*(glm::dot(o,o)+m_radius1*m_radius1 - m_radius2*m_radius2) - 4*m_radius1*m_radius1*(dir.x*dir.x + dir.y*dir.y) + 4*powf(glm::dot(o,dir),2);
c = 2*(glm::dot(o,o)+m_radius1*m_radius1 - m_radius2*m_radius2) - 4*m_radius1*m_radius1*(1 - dir.z*dir.z) + 4*powf(glm::dot(o,dir),2);
	float d = 2*(glm::dot(o,o) + m_radius1*m_radius1 - m_radius2*m_radius2)*2*glm::dot(o,dir)-8*m_radius1*m_radius1*o.x*dir.x - 8*m_radius1*m_radius1*o.y*dir.y;
	//d = 8*m_radius1*m_radius1*o.z*dir.z + 4*glm::dot(dir,o)*(glm::dot(o,o) - m_radius1*m_radius1 - m_radius2*m_radius2);
	float e = powf((glm::dot(o,o) + m_radius1*m_radius1 - m_radius2*m_radius2),2) - 4*m_radius1*m_radius1*o.x*o.x - 4*m_radius1*m_radius1*o.y*o.y;
	//e = powf(glm::dot(dir,dir),2) + powf((m_radius1*m_radius1 - m_radius2*m_radius2),2) + 2*(dir.x*dir.x*dir.y*dir.y + dir.z*dir.z*(m_radius1*m_radius1 -m_radius2*m_radius2) + (dir.x*dir.x+dir.y*dir.y)*(dir.z*dir.z - m_radius1*m_radius1 - m_radius2*m_radius2));
	e = o.x*o.x*o.x*o.x + o.y*o.y*o.y*o.y + o.z*o.z*o.z*o.z + ((m_radius1*m_radius1 - m_radius2*m_radius2)*(m_radius1*m_radius1 - m_radius2*m_radius2)) + 2*(o.x*o.x*o.y*o.y + o.z*o.z*(m_radius1*m_radius1 - m_radius2*m_radius2) + (o.x*o.x+o.y*o.y)*(o.z*o.z - m_radius1*m_radius1 - m_radius2*m_radius2));
	float root1, root2, root3, root4;
	int nroots = solveQuartic(b,c,d,e, root1, root2, root3, root4);
	//std::cout << nroots << std::endl;
	if (nroots == 0)
	{
		//std::cout << "false" << std::endl;
		return Intersection(false);
	}

	float tmin = 9999999999999.0f;
	float roots[4] = {root1, root2, root3, root4};
	//std::cout << " root1 " << root1 << " root2 " << root2 << " root3 " << root3 << " root4 " << root4 << std::endl;
	for (int i = 0; i < 4; i++)
	{

		if (roots[i] < 0.0f)
		{
			continue;
		}
		if (roots[i] < tmin)
		{
			tmin = roots[i];
		}
	}

	vec3 point = ray.getOrigin() + ray.getDirection()*tmin;
	float x = point.x;
	float y = point.y;
	float z = point.z;
	vec3 normal;
	normal.x = 2*x*(x*x + y*y + z*z + m_radius1*m_radius1 - m_radius2*m_radius2) - 8 * m_radius1*m_radius1*x;
	normal.y = 2*y*(x*x + y*y + z*z + m_radius1*m_radius1 - m_radius2*m_radius2) - 8 * m_radius1*m_radius1*y;
	normal.z = 2*z*(x*x + y*y + z*z + m_radius1*m_radius1 - m_radius2*m_radius2) ;

	normal = glm::normalize(normal);

	std::cout << "true" << std::endl;

	return Intersection(true, point, normal);
}