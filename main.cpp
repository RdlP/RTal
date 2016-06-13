
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <list>
#include <stack>
#include "Transform.h"
#include <FreeImage.h>
#include <stdio.h>
#include "Geometry.hpp"
#include "Camera.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"

using namespace std; 

#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h"

float specular[3], ambient[3]={0.2f,0.2f,0.2f}, diffuse[3], shininess, refractIndex, emission[3];
int maxDepth;
float attenuation[3]={1.0f, 0.0f, 0.0f}; 
std::string outputFile;
int main(int argc, char* argv[]) 
{
  if (argc < 3)
  {
    cerr << "Usage: rtal scenefile output\n"; 
    exit(-1); 
  }
  outputFile = argv[2];
  Camera *camera = NULL;// = new Camera();
  Scene *scene = new Scene();
  Screen *screen = NULL;// = new Screen();

  readfile(argv[1], camera, screen, scene);
  cout << "Screen::width " << screen->getWidth() << " Screen::height " << screen->getHeight() << endl;
  //cout << "Camera::fov " << camera->getFov() << endl;
  cout << "Scene::size " << scene->getNumbersGeometries() << endl;
  
  scene->render(camera, screen);
  screen->snapshot(outputFile);
  cout << outputFile << endl;
  return 0;
}
