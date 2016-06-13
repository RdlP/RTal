#ifndef ORTHOGRAPHIC_HEADER
#define ORTHOGRAPHIC_HEADER
#include "variables.h"
#include "Ray.hpp"
#include "Screen.hpp"
#include "Camera.hpp"
#include <math.h>

class OrthographicCamera : public Camera
{
	public:
		OrthographicCamera(vec3 eye, vec3 lookAt, vec3 up);
		virtual ~OrthographicCamera();
		Ray computeRay(int x, int y, Screen* screen);

	private:
		void precomputeCameraFrame();
};

#endif