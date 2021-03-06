#include "Camera.hpp"

Camera::Camera(vec3 eye, vec3 lookAt, vec3 up):
	m_eye(eye), m_lookAt(lookAt), m_up(up)
{
	//precomputeCameraFrame();
}

Camera::~Camera(){

}

vec3 Camera::getEye(){
	return m_eye;
}

vec3 Camera::getLookAt(){
	return m_lookAt;
}

vec3 Camera::getUp(){
	return m_up;
}

vec3 Camera::getEyeV(){
	return m_lookAt - m_eye;
}

/*Ray Camera::computeRay(int x, int y, Screen* screen)
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
}*/