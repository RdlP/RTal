#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include <GL/glut.h>
#include "Transform.h" 
#include <stdio.h>

using namespace std;
#include "readfile.h"

void matransform(stack<mat4> &transfstack, float* values) 
{
  mat4 transform = transfstack.top(); 
  vec4 valvec = vec4(values[0],values[1],values[2],1); 
  vec4 newval = transform * valvec; 
  for (int i = 0; i < 3; i++) values[i] = newval[i]; 
}

void rightmultiply(const mat4 & M, stack<mat4> &transfstack) 
{
  mat4 &T = transfstack.top(); 
  T = T * M; 
}

bool readvals(stringstream &s, const int numvals, float* values) 
{
  for (int i = 0; i < numvals; i++) {
    s >> values[i]; 
    if (s.fail()) {
      cout << "Failed reading value " << i << " will skip\n"; 
      return false;
    }
  }
  return true; 
}

void readfile(const char* filename, Camera *&camera, Screen* &screen, Scene *&scene) 
{
  string str, cmd; 
  ifstream in;
  in.open(filename); 
  if (in.is_open()) {

    stack <mat4> transfstack; 
    transfstack.push(mat4(1.0));  // identity

    getline (in, str); 
    vec3 * vertices;
    int currentVertex = 0;
    while (in) {
      if ((str.find_first_not_of(" \t\r\n") != string::npos) && (str[0] != '#')) {
        // Ruled out comment and blank lines 

        stringstream s(str);
        s >> cmd; 
        int i; 
        float values[10]; // Position and color for light, colors for others
        // Up to 10 params for cameras.  
        bool validinput; // Validity of input 


        if (cmd == "size"){
          validinput = readvals(s,2,values); 
          if (validinput) { 
            screen = new Screen((int)values[0], (int)values[1]);
          } 
        }else if (cmd == "maxdepth"){
          validinput = readvals(s,1,values); 
          if (validinput) { 
            scene->setMaxDepth((int)values[0]);
          } 
        }else if (cmd == "output"){
          s >> outputFile;
        }else if (cmd == "camera") {
          validinput = readvals(s,10,values); // 10 values eye cen up fov
          if (validinput) {
            camera = new Camera(vec3(values[0],values[1],values[2]), vec3(values[3],values[4],values[5]), vec3(values[6],values[7],values[8]), values[9]);

          }
        }else if (cmd == "point" || cmd == "directional"){
          validinput = readvals(s,6,values);
          if (validinput) {
            if (cmd == "point"){
              PointLight * point = new PointLight(vec3(values[0],values[1],values[2]),vec3(values[3],values[4],values[5]));
              point->setAttenuation(attenuation[0], attenuation[1], attenuation[2]);
              scene->addLight(point);
            }else if (cmd == "directional"){
              DirectionalLight * directional = new DirectionalLight(vec3(values[0],values[1],values[2]),vec3(values[3],values[4],values[5]));
              scene->addLight(directional);
            }
          }
        }else if (cmd == "ambient") {
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              ambient[i] = values[i]; 
            }
          }
        }else if (cmd == "attenuation"){
          validinput = readvals(s, 3, values); // colors 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              attenuation[i] = values[i]; 
            }
          }
        } else if (cmd == "diffuse") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              diffuse[i] = values[i]; 
            }
          }
        } else if (cmd == "specular") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              specular[i] = values[i]; 
            }
          }
        } else if (cmd == "emission") {
          validinput = readvals(s, 3, values); 
          if (validinput) {
            for (i = 0; i < 3; i++) {
              emission[i] = values[i]; 
            }
          }
        } else if (cmd == "shininess") {
          validinput = readvals(s, 1, values); 
          if (validinput) {
            shininess = values[0]; 
          }
        } else if (cmd == "translate") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            float x = values[0];
            float y = values[1];
            float z = values[2];
            mat4 tr = Transform::translate(x,y, z);
            rightmultiply(tr, transfstack);

          }
        }
        else if (cmd == "scale") {
          validinput = readvals(s,3,values); 
          if (validinput) {
            float x = values[0];
            float y = values[1];
            float z = values[2];
            mat4 sc = Transform::scale(x,y,z);
            rightmultiply(sc, transfstack);

          }
        }
        else if (cmd == "rotate") {
          validinput = readvals(s,4,values); 
          if (validinput) {
            float x = values[0];
            float y = values[1];
            float z = values[2];
            float degrees = values[3];
            vec3 axis(x,y,z);
            axis = glm::normalize(axis);
            mat3 rt = Transform::rotate(degrees,axis);
            mat4 rotate4(rt[0][0], rt[0][1], rt[0][2],0.0,rt[1][0],rt[1][1],rt[1][2],0.0,rt[2][0],rt[2][1],rt[2][2],0.0,0.0,0.0,0.0,1.0);
            rightmultiply(rotate4, transfstack);

          }
        }

        else if (cmd == "pushTransform") {
          transfstack.push(transfstack.top()); 
        } else if (cmd == "popTransform") {
          if (transfstack.size() <= 1) {
            cerr << "Stack has no elements.  Cannot Pop\n"; 
          } else {
            transfstack.pop(); 
          }
        }else if (cmd == "maxverts"){
          validinput = readvals(s,1,values); 
          if (validinput) {
            vertices = new vec3[(int)values[0]];
          }
        }else if (cmd == "sphere"){
          validinput = readvals(s,4,values); 
          if (validinput) {
            Sphere *sphere = new Sphere(vec3(values[0],values[1],values[2]),values[3], transfstack.top());
            Material *material = new Material(vec3(ambient[0], ambient[1], ambient[2]), vec3(diffuse[0], diffuse[1], diffuse[2]), vec3(specular[0], specular[1], specular[2]), shininess);
            sphere->setMaterial(material);
            scene->addGeometry(sphere);
          }
        }else if (cmd == "vertex"){
          validinput = readvals(s,3,values); 
          if (validinput) {
            vertices[currentVertex] = vec3(values[0], values[1], values[2]);
            currentVertex++;
          }
        }else if (cmd == "tri"){
          validinput = readvals(s,3,values); 
          if (validinput) {
            Triangle *triangle = new Triangle(vertices[(int)values[0]],vertices[(int)values[1]],vertices[(int)values[2]], transfstack.top());
            Material *material = new Material(vec3(ambient[0], ambient[1], ambient[2]), vec3(diffuse[0], diffuse[1], diffuse[2]), vec3(specular[0], specular[1], specular[2]), shininess);
            triangle->setMaterial(material);
            scene->addGeometry(triangle);
          }
        }
        else {
          cerr << "Unknown Command: " << cmd << " Skipping \n"; 
        }
      }
      getline (in, str); 
    }
    
  } else {
    cerr << "Unable to Open Input Data File " << filename << "\n"; 
    throw 2; 
  }
}
