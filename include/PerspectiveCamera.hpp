#ifndef PERSPECTIVE_HEADER
#define PERSPECTIVE_HEADER
#include "variables.h"
#include "Ray.hpp"
#include "Screen.hpp"
#include "Camera.hpp"
#include <math.h>

class PerspectiveCamera : public Camera
{
	public:
		PerspectiveCamera(vec3 eye, vec3 lookAt, vec3 up, float fov);
		virtual ~PerspectiveCamera();
		Ray computeRay(int x, int y, Screen* screen);
		float getFov();

	private:
		void precomputeCameraFrame();
		float m_fov, m_angle;
};

#endif