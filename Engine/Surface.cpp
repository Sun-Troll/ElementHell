#include "Surface.h"
#include <cassert>

Surface::Surface(int width, int height)
	:
	width(width),
	height(height),
	pPixels(new Color[width * height])
{
}

Surface::Surface(const Surface& rhs)
	:
	width(rhs.width),
	height(rhs.height),
	pPixels(new Color[width * height])
{
	const int nPixels = width * height;
	for (int i = 0; i < nPixels; ++i)
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
}

Surface& Surface::operator=(const Surface& rhs)
{
	width = rhs.width;
	height = rhs.height;
	const int nPixels = width * height;
	Color* pTemp = new Color[nPixels];
	for (int i = 0; i < nPixels; ++i)
	{
		pTemp[i] = rhs.pPixels[i];
	}
	delete[] pPixels;
	pPixels = pTemp;
	return *this;
}

void Surface::PutPixel(int x, int y, Color c)
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel(int x, int y) const
{
	assert(x >= 0);
	assert(x < width);
	assert(y >= 0);
	assert(y < height);
	return pPixels[y * width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

RectI Surface::GetRect() const
{
	return { 0, width, 0, height };
}
