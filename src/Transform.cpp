

#include "Transform.h"
#include <stdio.h>

mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  float x = axis[0], y = axis[1], z = axis[2];
  float r = glm::radians(degrees);
  mat3 I (1.0);
  float c = cos(r);
  float s = sin(r);
  mat3 A(0.0,z,-y,-z,0.0,x,y,-x,0.0);
  mat3 aa(x*x,x*y,x*z,x*y,y*y,y*z,x*z,y*z,z*z);

  mat3 result = (c*I)+((1.0-c)*aa)+(s*A);
  
  return result;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  vec3 eyeV = eye-center;
  vec3 w = glm::normalize(eyeV);
  vec3 u = glm::normalize(glm::cross(up,w));
  vec3 v = glm::cross(w,u);
  mat4 result (u.x,v.x,w.x,0,u.y,v.y,w.y,0,u.z,v.z,w.z,0,glm::dot(-eye,u),glm::dot(-eye,v),glm::dot(-eye,w),1.0);

  return result;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret(1.0/(aspect*tan(glm::radians(fovy)/2.0)),0,0,0,0,1.0/tan(glm::radians(fovy)/2.0),0,0,0,0,-((zFar+zNear)/(zFar-zNear)),-1.0,0.0,0.0,-((2.0*zFar*zNear)/(zFar-zNear)),0.0);

  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 ret (sx,0.0,0.0,0.0,0.0,sy,0.0,0.0,0.0,0.0,sz,0.0,0.0,0.0,0.0,1.0);

  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 ret(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0,tx,ty,tz,1.0);

  return ret;
}

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
