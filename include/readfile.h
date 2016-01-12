// Readfile definitions 

#include "Scene.hpp"
#include "Screen.hpp"
#include "Camera.hpp"
#include "Geometry.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

void matransform (stack<mat4> &transfstack, float * values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename, Camera *&camera, Screen* &screen, Scene *&scene);
