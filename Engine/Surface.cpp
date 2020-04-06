#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface(const std::string& filename)
{
	std::ifstream file(filename, std::ios::binary);
	assert(file);

	BITMAPFILEHEADER bmFileHead;
	file.read(reinterpret_cast<char*>(&bmFileHead), sizeof(bmFileHead));

	BITMAPINFOHEADER bmInfoHead;
	file.read(reinterpret_cast<char*>(&bmInfoHead), sizeof(bmInfoHead));

	assert(bmInfoHead.biBitCount == 24 || bmInfoHead.biBitCount == 32);
	assert(bmInfoHead.biCompression == BI_RGB);

	width = bmInfoHead.biWidth;
	const bool is32b = bmInfoHead.biBitCount == 32;
	int yStart;
	int yEnd;
	int dir;
	if (bmInfoHead.biHeight > 0)
	{
		height = bmInfoHead.biHeight;
		yStart = height - 1;
		yEnd = -1;
		dir = -1;
	}
	else
	{
		height = -bmInfoHead.biHeight;
		yStart = 0;
		yEnd = height;
		dir = 1;
	}
	pPixels = new Color[width * height];
	file.seekg(bmFileHead.bfOffBits);
	const int padding = (4 - (width * 3) % 4) % 4;

	for (int y = yStart; y != yEnd; y += dir)
	{
		for (int x = 0; x < width; ++x)
		{
			const unsigned char b = file.get();
			const unsigned char g = file.get();
			const unsigned char r = file.get();
			PutPixel(x, y, { r, g, b });
			if (is32b)
			{
				file.seekg(1, std::ios::cur);
			}
		}
		if (!is32b)
		{
			file.seekg(padding, std::ios::cur);
		}
	}
}

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
