#ifndef SCENE_HEADER
#define SCENE_HEADER

#include "variables.h"
#include "Geometry.hpp"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Camera.hpp"
#include "Screen.hpp"
#include "Ray.hpp"
#include <iostream>
#include <vector>
#include <math.h>

class Scene
{
	public:
		Scene();
		virtual ~Scene();
		//void render(Camera* camera, Screen* screen, unsigned char*& image);
		void render(Camera* camera, Screen* screen);
		vec3 trace(Ray ray, int depth);
		void addGeometry(Geometry* geometry);
		int getNumbersGeometries();
		void addLight( Light* light);
		int getNumbersLights();
		int getMaxDepth();
		void setMaxDepth(int depth);

	private:
		std::vector<Geometry*> m_geometries;
		std::vector<Light*> m_lights;
		int m_maxDepth;
};

#endif