#ifndef SCREEN_HEADER
#define SCREEN_HEADER

#include "variables.h"
#include <string>
#include <FreeImage.h>

class Screen
{
	public:
		Screen(int width, int height);
		Screen();
		virtual ~Screen();
		int getWidth();
		void setWidth(int w);
		int getHeight();
		void setHeight(int h);
		void putPixel(int x, int y, vec3 color);
		void snapshot(std::string filename);
		float getAspectRatio();
	private:
		int m_width, m_height;
		unsigned char *image;
		float m_aspectRatio;
};

#endif