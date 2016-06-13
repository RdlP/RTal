// Readfile definitions 

#include "Scene.hpp"
#include "Screen.hpp"
#include "PerspectiveCamera.hpp"
#include "OrthographicCamera.hpp"
#include "Camera.hpp"

#include "Geometry.hpp"
#include "Sphere.hpp"
#include "Cone.hpp"
#include "Triangle.hpp"
#include "Torus.hpp"
#include "Box.hpp"
#include "Cylinder.hpp"
#include "Material.hpp"
#include "Light.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"

void matransform (stack<mat4> &transfstack, float * values) ;
void rightmultiply (const mat4 & M, stack<mat4> &transfstack) ;
bool readvals (stringstream &s, const int numvals, float * values) ;
void readfile (const char * filename, Camera *&camera, Screen* &screen, Scene *&scene);
