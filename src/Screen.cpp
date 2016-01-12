#include "Screen.hpp"

Screen::Screen(int width, int height):
m_width(width), m_height(height)
{
	image = new unsigned char[m_width*m_height*3];
	m_aspectRatio = (float) m_width / m_height;
}

Screen::Screen()
{
	
}

int Screen::getWidth()
{
	return m_width;
}

void Screen::setWidth(int w)
{
	m_width=w;
}

int Screen::getHeight()
{
	return m_height;
}

void Screen::setHeight(int h)
{
	m_height=h;
}

float Screen::getAspectRatio()
{
	return m_aspectRatio;
}

void Screen::putPixel(int x, int y, vec3 color)
{
	image[(y * m_width + x) * 3] = color.z < 256?(int)color.z&0xFF:255;
	image[(y * m_width + x) * 3 + 1] = color.y < 256?(int)color.y&0xFF:255;
	image[(y * m_width + x) * 3 + 2] = color.x < 256?(int)color.x&0xFF:255;
}

void Screen::snapshot(std::string filename)
{
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_ConvertFromRawBits(image, m_width, m_height, m_width*3, 24, 0xff, 0, 0, true);
  	FreeImage_Save(FIF_BMP, bitmap, filename.c_str(),0);
  	FreeImage_DeInitialise();
}

Screen::~Screen()
{
	delete image;
}