#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <logging.h>
#include <PNMreader.h>

using namespace std;


PNMreader::PNMreader(char* inFile)
{	
	name = "PNMreader";
	file = new char[strlen(inFile)+1];
	strcpy(file, inFile);
}

PNMreader::~PNMreader()
{
	delete [] file;
}

void PNMreader::Execute()
{
	int width, height, maxval;
	int num;
	string filetype;	

	ifstream infile;
	infile.open("3D_input.pnm", ios::in | ios::binary);
	infile >> filetype >> width >> height >> maxval;

	num = 3*width*height;	//3 is from size of Pixel

	GetOutput()->SetSize(width, height);
	GetOutput()->setMaxVal(maxval);

	unsigned char* buffer = new unsigned char[num];
	infile.seekg(17);
	infile.read((char *)buffer, num);
	for (int j = 0; j<num; j+=3)
	{
		GetOutput()->setData(j, buffer);
	}
	delete [] buffer;
	infile.close();

}

