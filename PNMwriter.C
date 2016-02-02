#include <iostream>
#include <fstream>
#include <string>
#include <PNMwriter.h>
using namespace std;

PNMwriter::PNMwriter() {name = "PNMwriter";}
PNMwriter::~PNMwriter() {}
void PNMwriter::Write(const char *outFile)
{
	int h,w;
	w = img1->getWidth();
	h = img1->getHeight();
	ofstream outfile;
	outfile.open(outFile, ios::out | ios::binary);
	outfile << "P6" << endl << w << " " << h << endl << 255 << endl;

/*

	unsigned char* buffer = new unsigned char[3*w*h];
	img1->dataToBuffer(buffer);
	outfile.write((char*)buffer,  3*h*w);
	delete [] buffer;
*/

	outfile.write((char*)img1->getData(), 3*h*w);

	outfile.close();
}
