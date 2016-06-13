#include "PerspectiveCamera.hpp"

PerspectiveCamera::PerspectiveCamera(vec3 eye, vec3 lookAt, vec3 up, float fov):
	Camera(eye, lookAt, up), m_fov(fov)
{
	precomputeCameraFrame();
}

PerspectiveCamera::~PerspectiveCamera(){

}

float PerspectiveCamera::getFov(){
	return m_fov;
}

void PerspectiveCamera::precomputeCameraFrame()
{
	m_w = glm::normalize(m_eye - m_lookAt);
	m_u = glm::normalize(glm::cross(m_up, m_w));
	m_v = glm::cross(m_w, m_u);
	m_angle = tan(M_PI * 0.5 * m_fov / 180.); 
}

Ray PerspectiveCamera::computeRay(int x, int y, Screen* screen)
{
	float alpha = m_angle * (((x+0.5) -((float)screen->getWidth()/2)) / ((float)screen->getWidth()/2)) * screen->getAspectRatio();
	float beta = m_angle * ((((float)screen->getHeight()/2) - (y+0.5)) / ((float)screen->getHeight()/2)) ;
	vec3 ray_direction = alpha*m_u + beta*m_v - m_w;
	//vec3 f(0,0,-1);
	//float nx = ((x+0.5) -((float)screen->getWidth()/2)) / ((float)screen->getWidth()/2);
	//float ny = (((float)screen->getHeight()/2) - (y+0.5)) / ((float)screen->getHeight()/2);
	//vec3 ray_direction = -m_w;
	//vec3 origin = m_eye + ny*m_v + nx*m_u;
	Ray primaryRay(m_eye, glm::normalize(ray_direction));
	//Ray primaryRay(origin, glm::normalize(ray_direction));
	return primaryRay;
}