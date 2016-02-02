
#ifndef FILTERS_H
#define FILTERS_H

#include <iostream>
using namespace std;

#include <filter.h>
#include <sink.h>

class Filters : public Filter
{
    public:

};

class Crop : public Filters
{
    public:
	Crop();
	void Execute();
	void SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
		{
			Istart = Istart_;
			Istop = Istop_;
			Jstart = Jstart_;
			Jstop = Jstop_;
		}
	const char* FilterName() {return name;}
	~Crop();

    private:
	int Istart, Istop, Jstart, Jstop;
	const char* name;
};
class Transpose : public Filters
{
    public:
	Transpose();
	void Execute();
	const char* FilterName() {return name;}
	~Transpose();

    private:
	const char* name;
};
class Invert : public Filters
{
    public:
	Invert();
	void Execute();
	const char* FilterName() {return name;}
	~Invert();
    private:
	const char* name;
};
class Checkerboard : public Filters
{
    public:
	Checkerboard();
	void Execute();
	const char* FilterName() {return name;}
	~Checkerboard();
    private:
	const char* name;
};
class Color : public Source
{
    public:
	Color(int, int, unsigned char, unsigned char, unsigned char);
	void Execute();
	const char* SourceName() {return name;}
	~Color();
    private:
	const char* name;
	unsigned char r,g,b;
	int width, height;
};
class CheckSum : public Sink
{
    public:
	CheckSum();
	const char* SinkName() {return name;}
	void OutputCheckSum(const char*);
	~CheckSum();
    private:
	FILE* file;
	const char* name;
};

class Shrinker : public Filters
{
    public:
	Shrinker();
	void Execute();
	const char* FilterName() {return name;}
	~Shrinker();
    private:
	const char* name;
};

class LRConcat : public Filters
{
    public:
	LRConcat();
	void Execute();
	const char* FilterName() {return name;}
	~LRConcat();
    private:
	const char* name;
};

class TBConcat : public Filters
{
    public:
	TBConcat();
	void Execute();
	const char* FilterName() {return name;}
	~TBConcat();
    private:
	const char* name;
};

class Blender : public Filters
{
    public:
	Blender();
	void Execute();
	void SetFactor(float num) {factor = num;}
	const char* FilterName() {return name;}
	~Blender();
    protected:
	float factor;
    private:
	const char* name;
};


#endif
