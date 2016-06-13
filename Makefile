CC = g++
CFLAGS = -g -DGL_GLEXT_PROTOTYPES -std=c++11
INCFLAGS = -I./glm-0.9.2.7 -I./include/
LDFLAGS = -lfreeimage

RM = /bin/rm -f
BUILDDIR = build
APPNAME = rtal

all: createBuild transform
createBuild:
	mkdir -p $(BUILDDIR)
transform: main.o Transform.o readfile.o Camera.o PerspectiveCamera.o OrthographicCamera.o Scene.o Screen.o Material.o include/Geometry.hpp Sphere.o Triangle.o Ray.o Light.o Plane.o Box.o Cylinder.o Cone.o Torus.o PointLight.o SpotLight.o DirectionalLight.o Intersection.o include/variables.h include/readfile.h
	$(CC) $(CFLAGS) -o $(APPNAME) $(BUILDDIR)/main.o $(BUILDDIR)/Transform.o $(BUILDDIR)/readfile.o $(BUILDDIR)/Camera.o $(BUILDDIR)/OrthographicCamera.o $(BUILDDIR)/PerspectiveCamera.o $(BUILDDIR)/Scene.o $(BUILDDIR)/Screen.o $(BUILDDIR)/Material.o $(BUILDDIR)/Sphere.o $(BUILDDIR)/Triangle.o $(BUILDDIR)/Ray.o $(BUILDDIR)/Box.o $(BUILDDIR)/Cylinder.o $(BUILDDIR)/Cone.o $(BUILDDIR)/Torus.o $(BUILDDIR)/Light.o $(BUILDDIR)/Plane.o $(BUILDDIR)/PointLight.o $(BUILDDIR)/SpotLight.o $(BUILDDIR)/DirectionalLight.o $(BUILDDIR)/Intersection.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp include/Transform.h
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/main.o -c main.cpp
readfile.o: src/readfile.cpp include/readfile.h
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/readfile.o -c src/readfile.cpp
Transform.o: src/Transform.cpp include/Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Transform.o -c src/Transform.cpp  
Camera.o: src/Camera.cpp include/Camera.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Camera.o -c src/Camera.cpp 
OrthographicCamera.o: src/OrthographicCamera.cpp include/OrthographicCamera.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/OrthographicCamera.o -c src/OrthographicCamera.cpp 
PerspectiveCamera.o: src/PerspectiveCamera.cpp include/PerspectiveCamera.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/PerspectiveCamera.o -c src/PerspectiveCamera.cpp 
Scene.o: src/Scene.cpp include/Scene.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Scene.o -c src/Scene.cpp
Screen.o: src/Screen.cpp include/Screen.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Screen.o -c src/Screen.cpp
Material.o: src/Material.cpp include/Material.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Material.o -c src/Material.cpp
Sphere.o: src/Sphere.cpp include/Sphere.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Sphere.o -c src/Sphere.cpp
Triangle.o: src/Triangle.cpp include/Triangle.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Triangle.o -c src/Triangle.cpp
Ray.o: src/Ray.cpp include/Ray.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Ray.o -c src/Ray.cpp
Light.o: src/Light.cpp include/Light.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Light.o -c src/Light.cpp
Plane.o: src/Plane.cpp include/Plane.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Plane.o -c src/Plane.cpp
Box.o: src/Box.cpp include/Box.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Box.o -c src/Box.cpp
Cylinder.o: src/Cylinder.cpp include/Cylinder.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Cylinder.o -c src/Cylinder.cpp
Cone.o: src/Cone.cpp include/Cone.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Cone.o -c src/Cone.cpp
Torus.o: src/Torus.cpp include/Torus.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Torus.o -c src/Torus.cpp
PointLight.o: src/PointLight.cpp include/PointLight.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/PointLight.o -c src/PointLight.cpp
SpotLight.o: src/SpotLight.cpp include/SpotLight.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/SpotLight.o -c src/SpotLight.cpp
DirectionalLight.o: src/DirectionalLight.cpp include/DirectionalLight.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/DirectionalLight.o -c src/DirectionalLight.cpp
Intersection.o: src/Intersection.cpp include/Intersection.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Intersection.o -c src/Intersection.cpp
clean: 
clean: 
	$(RM) $(BUILDDIR)/*.o $(APPNAME)
	rmdir $(BUILDDIR)


 
