
#ifndef IMAGE_H
#define IMAGE_H

class Source;

struct Pixel
{
	unsigned char r,g,b;
};


class Image
{
    public:
	Image();
	Image(const Image &obj);
	Image(int, int, Pixel*);

	int getWidth() const;
	int getHeight() const;
	int getMaxVal() const;
	Pixel* getData() const;
	void setMaxVal(int);
	void setWidth(int);
	void setHeight(int);
	void setDataSize(int);
	void setData(int, unsigned char*);
	Pixel getPixel(int, int) const;
	void setPixel(int, int, Pixel);
	void SetSize(int, int);
	void dataToBuffer(unsigned char*);

	void setSource(Source*);
	void Update() const;

	~Image();

    protected:
	int width, height, maxval;
	Pixel* data;
	Source* s;
};

#endif
