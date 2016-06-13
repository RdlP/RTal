#include "OrthographicCamera.hpp"

OrthographicCamera::OrthographicCamera(vec3 eye, vec3 lookAt, vec3 up):
	Camera(eye, lookAt, up)
{
	precomputeCameraFrame();
}

OrthographicCamera::~OrthographicCamera(){

}

void OrthographicCamera::precomputeCameraFrame()
{
	m_w = glm::normalize(m_eye - m_lookAt);
	m_u = glm::normalize(glm::cross(m_up, m_w));
	m_v = glm::cross(m_w, m_u);
}

Ray OrthographicCamera::computeRay(int x, int y, Screen* screen)
{
	float nx = ((x+0.5) -((float)screen->getWidth()/2)) / ((float)screen->getWidth()/2);
	float ny = (((float)screen->getHeight()/2) - (y+0.5)) / ((float)screen->getHeight()/2);
	vec3 ray_direction = -m_w;
	vec3 origin = m_eye + ny*m_v + nx*m_u;
	Ray primaryRay(origin, glm::normalize(ray_direction));
	return primaryRay;
}