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
transform: main.o Transform.o readfile.o Camera.o Scene.o Screen.o Material.o include/Geometry.hpp Sphere.o Triangle.o Ray.o Light.o PointLight.o DirectionalLight.o include/variables.h include/readfile.h
	$(CC) $(CFLAGS) -o $(APPNAME) $(BUILDDIR)/main.o $(BUILDDIR)/Transform.o $(BUILDDIR)/readfile.o $(BUILDDIR)/Camera.o $(BUILDDIR)/Scene.o $(BUILDDIR)/Screen.o $(BUILDDIR)/Material.o $(BUILDDIR)/Sphere.o $(BUILDDIR)/Triangle.o $(BUILDDIR)/Ray.o $(BUILDDIR)/Light.o $(BUILDDIR)/PointLight.o $(BUILDDIR)/DirectionalLight.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp include/Transform.h
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/main.o -c main.cpp
readfile.o: src/readfile.cpp include/readfile.h
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/readfile.o -c src/readfile.cpp
Transform.o: src/Transform.cpp include/Transform.h 
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Transform.o -c src/Transform.cpp  
Camera.o: src/Camera.cpp include/Camera.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Camera.o -c src/Camera.cpp 
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
PointLight.o: src/PointLight.cpp include/PointLight.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/PointLight.o -c src/PointLight.cpp
DirectionalLight.o: src/DirectionalLight.cpp include/DirectionalLight.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/DirectionalLight.o -c src/DirectionalLight.cpp
clean: 
	$(RM) $(BUILDDIR)/*.o $(APPNAME)
	rmdir $(BUILDDIR)


 
