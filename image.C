#include <image.h>
#include <source.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

Image::Image()
{
	width = 0;
	height = 0;
	data = NULL;
	s = NULL;
}

Image::Image(const Image &obj)
{
	width = obj.width;
	height = obj.height;
	data = new Pixel;
	*data = *obj.data;
}

Image::Image(int d1, int d2, Pixel* pix1)
{
	width = d1;
	height = d2;
	data = pix1;
}

Image::~Image()
{
	if (data != NULL)
	{
		delete [] data;
	}
}

int Image::getWidth() const
{
	return width;
}

int Image::getHeight() const
{
	return height;
}

int Image::getMaxVal() const
{
	return maxval;
}

Pixel* Image::getData() const
{
	return data;
}

void Image::setMaxVal(int num)
{
	maxval = num;
}

void Image::setWidth(int num)
{
	width = num;
}

void Image::setHeight(int num)
{
	height = num;
}
void Image::setDataSize(int num)
{
	data = new Pixel[num];
}

void Image::setData(int j, unsigned char* pixelArray2)
{
	data[j/3].r = pixelArray2[j];
	data[j/3].g = pixelArray2[j + 1];
	data[j/3].b = pixelArray2[j + 2];
}

Pixel Image::getPixel(int w, int h) const
{
	return data[h*width+w];
}

void Image::setPixel(int w, int h, Pixel p)
{
	data[h*width+w] = p;
}

void Image::SetSize(int w, int h)
{
	width = w;
	height = h;
	if (data != NULL)
	{
		delete [] data;
	}
	data = new Pixel[h*w];
}

void Image::dataToBuffer(unsigned char* buff)
{
	for (int i = 0; i<(3*width*height); i+=3)
	{
		buff[i] = data[i/3].r;
		buff[i+1] = data[i/3].g;
		buff[i+2] = data[i/3].b;
	}
}

void Image::setSource(Source* source)
{
	s = source;
}

void Image::Update() const
{
	if (s != NULL)
	{
		s->Update();
	}
}
