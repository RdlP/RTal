#include "Camera.hpp"

Camera::Camera(vec3 eye, vec3 lookAt, vec3 up, float fov):
	m_eye(eye), m_lookAt(lookAt), m_up(up), m_fov(fov)
{
	precomputeCameraFrame();
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

float Camera::getFov(){
	return m_fov;
}

void Camera::precomputeCameraFrame()
{
	m_w = glm::normalize(m_eye - m_lookAt);
	m_u = glm::normalize(glm::cross(m_up, m_w));
	m_v = glm::cross(m_w, m_u);
	m_angle = tan(M_PI * 0.5 * m_fov / 180.); 
}

Ray Camera::computeRay(int x, int y, Screen* screen)
{
	float alpha = m_angle * (((x+0.5) -((float)screen->getWidth()/2)) / ((float)screen->getWidth()/2)) * screen->getAspectRatio();
	float beta = m_angle * ((((float)screen->getHeight()/2) - (y+0.5)) / ((float)screen->getHeight()/2)) ;
	vec3 ray_direction = alpha*m_u + beta*m_v - m_w;
	Ray primaryRay(m_eye, glm::normalize(ray_direction));
	return primaryRay;
}