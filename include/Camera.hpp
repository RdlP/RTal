#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include "variables.h"
#include "Ray.hpp"
#include "Screen.hpp"
#include <math.h>

class Camera
{
	public:
		Camera(vec3 eye, vec3 lookAt, vec3 up);
		virtual ~Camera();
		virtual Ray computeRay(int x, int y, Screen* screen) = 0;
		vec3 getEye();
		vec3 getEyeV();
		vec3 getLookAt();
		vec3 getUp();

	protected:
		vec3 m_u, m_v, m_w;
		vec3 m_eye, m_eyeV, m_lookAt, m_up;
};

#endif