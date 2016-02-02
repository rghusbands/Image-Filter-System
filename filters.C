#include <filters.h>
#include <iostream>
#include <logging.h>
using namespace std;

Crop::Crop()
{
	Istart = Istop = Jstart = Jstop = -1;
	name = "Crop";
}
Crop::~Crop() {}
void Crop::Execute()
{
	OneInputCheck();
	if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop <0)
	{
		char msg[1024];
		sprintf(msg, "uninitialized region");
		DataFlowException ev(FilterName(), msg);
		throw ev;
	}
	if (Istart >= img1->getWidth() || Istop >= img1->getWidth())
	{
		char msg[1024];
		sprintf(msg, "region outside image width");
		DataFlowException ev(FilterName(), msg);
		throw ev;
	}
	if (Jstart >= img1->getHeight() || Jstop >= img1->getHeight())
	{
		char msg[1024];
		sprintf(msg, "region outside image height");
		DataFlowException ev(FilterName(), msg);
		throw ev;
	}
	if (Istop < Istart || Jstop < Jstart)
	{
		char msg[1024];
		sprintf(msg, "invalid region");
		throw DataFlowException (FilterName(), msg);
	}
	int height = Jstop - Jstart + 1;
	int width = Istop - Istart + 1;
	int inputWidth = img1->getWidth();
	GetOutput()->SetSize(width, height);
	int i, j;
	Pixel pix;
	for (i = Istart; i <= Istop; i++)
	{
		for (j = Jstart; j <= Jstop; j++)
		{
			pix = img1->getPixel(i, j);
			GetOutput()->setPixel(i-Istart, j-Jstart, pix);
		}
	}
}

Transpose::Transpose() {name = "Transpose";}
Transpose::~Transpose() {}
void Transpose::Execute()
{
	OneInputCheck();
	int M = img1->getHeight();
	int N = img1->getWidth();
	GetOutput()->SetSize(M, N);
	
	int i, j;
	Pixel pix;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			pix = img1->getPixel(j, i);
			GetOutput()->setPixel(i, j, pix);
		}
	}
}

Invert::Invert() {name = "Invert";}
Invert::~Invert() {}
void Invert::Execute()
{
	OneInputCheck();
	int W = img1->getWidth(); 
	int H = img1->getHeight();
	GetOutput()->SetSize(W, H);
	int h, w;
	Pixel pix, newPix;
	for (h = 0; h<H; h++)
	{
		for (w = 0; w<W; w++)
		{
			pix = img1->getPixel(w, h);
			newPix.r = 255-pix.r;
			newPix.g = 255-pix.g;
			newPix.b = 255-pix.b;
			GetOutput()->setPixel(w, h, newPix);
		}
	}
}

Checkerboard::Checkerboard() {name = "Checkerboard";}
Checkerboard::~Checkerboard() {}
void Checkerboard::Execute()
{
	int W = img1->getWidth();
	int H = img1->getHeight();
	int W2 = img2->getWidth();
	int H2 = img2->getHeight();
	TwoInputCheck();
	if (H != H2)
	{
		char msg[1024];
		sprintf(msg, "Heights don't match: %d, %d", img1->getHeight(), img2->getHeight());
		DataFlowException ev(FilterName(), msg);
		throw ev;
	}
	if (W != W2)
	{
		char msg[1024];
		sprintf(msg, "Widths don't match: %d, %d", img1->getWidth(), img2->getWidth());
		DataFlowException ev(FilterName(), msg);
		throw ev;
	}
	GetOutput()->SetSize(W, H);
	int h, w;
	Pixel pix;
	for (h = 0; h<H; h++)
	{
		for (w = 0; w<W; w++)
		{
			if ((h/10+w/10)%2 == 0)
			{
				pix = img1->getPixel(w,h);
				GetOutput()->setPixel(w,h,pix);
			}
			else
			{
				pix = img2->getPixel(w,h);
				GetOutput()->setPixel(w,h,pix);
			}
		}
	}
}

Color::Color(int w, int h, unsigned char red, unsigned char green, unsigned char blue)
{
	name = "Color";
	width = w;
	height = h;
	r = red;
	g = green;
	b = blue;
}
Color::~Color() {}
void Color::Execute()
{
	int h, w;
	Pixel pix;
	GetOutput()->SetSize(width, height);
	for (h = 0; h<height; h++)
	{
		for (w = 0; w<width; w++)
		{
			pix.r = r;
			pix.g = g;
			pix.b = b;
			GetOutput()->setPixel(w, h, pix);
		}
	}
}

CheckSum::CheckSum() {name = "CheckSum";}
CheckSum::~CheckSum() {}
void CheckSum::OutputCheckSum(const char* inFile)
{
	OneInputCheck();
	int w = img1->getWidth();
	int h = img1->getHeight();
	int i, j;
	int R, G, B;
	R = G = B = 0;
	Pixel pix;
	for (i = 0; i<h; i++)
	{
		for (j = 0; j<w; j++)
		{
			pix = img1->getPixel(j, i);
			R += pix.r;
			G += pix.g;
			B += pix.b;
		}
	}
	R = R%256;
	G = G%256;
	B = B%256;
	file = fopen(inFile, "w");
	fprintf(file, "CHECKSUM: %u, %u, %u\n", R, G, B);
	fclose(file);
}

Shrinker::Shrinker() {name = "Shrinker";}
Shrinker::~Shrinker() {}
void Shrinker::Execute()
{	
	OneInputCheck();
	int h, w, i, j;
	h = img1->getHeight();
	w = img1->getWidth();
	GetOutput()->SetSize(w/2, h/2);
	int imax = w/2;
	int jmax = h/2;
	for (i=0; i < imax; i++)
	{
		for (j=0; j < jmax; j++)
		{
			Pixel thepix = img1->getPixel(2*i, 2*j);
			GetOutput()->setPixel(i, j, thepix);
		}
	}
}

LRConcat::LRConcat() {name = "LRConcat";}
LRConcat::~LRConcat() {}
void LRConcat::Execute()
{
	TwoInputCheck();
	if (img1->getHeight() != img2->getHeight())
	{
		char msg[1024];
		sprintf(msg, "heights must match: %d, %d", img1->getHeight(), img2->getHeight());
		DataFlowException ev(SinkName(), msg);
		throw ev;
	}
	int h, w, w2, i, j, j2;
	Pixel pix1, pix2;
	h = img1->getHeight();
	w = img1->getWidth();
	w2 = img2->getWidth();
	GetOutput()->SetSize(w+w2, h);
	for (i=0; i<h; i++)
	{
		for (j=0; j<w; j++)
		{
			pix1 = img1->getPixel(j, i);
			GetOutput()->setPixel(j, i, pix1);
		}
		for (j2=0; j2<w2; j2++)
		{
			pix2 = img2->getPixel(j2, i);
			GetOutput()->setPixel(j2+w, i, pix2);
		}
	}
}

TBConcat::TBConcat() {name = "TBConcat";}
TBConcat::~TBConcat() {}
void TBConcat::Execute()
{
	TwoInputCheck();
	if (img1->getWidth() != img2->getWidth())
	{
		char msg[1024];
		sprintf(msg, "widths must match: %d, %d", img1->getWidth(), img2->getWidth());
		DataFlowException ev(SinkName(), msg);
		throw ev;
	}
	int h, h2, w, i, j, j2;
	Pixel pix1, pix2;
	h = img1->getHeight();
	h2 = img2->getHeight();
	w = img1->getWidth();
	GetOutput()->SetSize(w, h+h2);
	for (i=0; i<h; i++)
	{
		for (j=0; j<w; j++)
		{
			pix1 = img1->getPixel(j, i);
			GetOutput()->setPixel(j, i, pix1);
		}
	}	
	for (i=0; i<h2; i++)
	{
		for (j=0; j<w; j++)
		{
			pix2 = img2->getPixel(j,i);
			GetOutput()->setPixel(j, i+h, pix2);
		}
	}
}

Blender::Blender() {name = "Blender";}
Blender::~Blender() {}
void Blender::Execute()
{
	TwoInputCheck();
	if (factor < 0 || factor > 1)
	{
		char msg[1024];
		sprintf(msg, "factor does not work: %f", factor);
		DataFlowException ev(SinkName(), msg);
		throw ev;
	}
	int i, j, h, w;
	Pixel pix1, pix2, newpix;
	h = img1->getHeight();
	w = img1->getWidth();
	GetOutput()->SetSize(w, h);
	for (i=0; i<h; i++)
	{
		for (j=0; j<w; j++)
		{
			pix1 = img1->getPixel(j,i);
			pix2 = img2->getPixel(j,i);
			newpix.r = (pix1.r * factor) + (pix2.r * (1-factor));
			newpix.g = (pix1.g * factor) + (pix2.g * (1-factor));
			newpix.b = (pix1.b * factor) + (pix2.b * (1-factor));
			GetOutput()->setPixel(j, i, newpix);
		}
	}
}
