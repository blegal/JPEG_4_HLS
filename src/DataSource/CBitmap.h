/*
 *  CBitmap.h
 *  CBitmap
 *
 *  Created by Le Gal on 24/10/06.
 *  Copyright 2006 ENSEIRB. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>

#include "CImage.h"

using namespace std;

#ifndef CBITMAP_H_
#define CBITMAP_H_

class CBitmap{
private:
	short 	bfType; 			//	19778	must always be set to 'BM' to declare that this is a .bmp-file.
	int		bfSize;				//	??	specifies the size of the file in bytes.
	short	bfReserved1;		//	0	must always be set to zero.
	short	bfReserved2;		//	0	must always be set to zero.
	int		bfOffBits;			//	1078	specifies the offset from the beginning of the file to the bitmap data.
	int		biSize;				//	40	specifies the size of the BITMAPINFOHEADER structure, in bytes.
	int		biWidth;			//	100	specifies the width of the image, in pixels.
	int		biHeight;			//	100	specifies the height of the image, in pixels.
	short	biPlanes;			//	1	specifies the number of planes of the target device, must be set to zero.
	short	biBitCount;			//	8	specifies the number of bits per pixel.
	int		biCompression;		//	0	Specifies the type of compression, usually set to zero (no compression).
	int		biSizeImage;		//	0	specifies the size of the image data, in bytes. If there is no compression, it is valid to set this member to zero.
	int		biXPelsPerMeter;	//	0	specifies the the horizontal pixels per meter on the designated targer device, usually set to zero.
	int		biYPelsPerMeter;	//	0	specifies the the vertical pixels per meter on the designated targer device, usually set to zero.
	int		biClrUsed;			//	0	specifies the number of colors used in the bitmap, if set to zero the number of colors is calculated using the biBitCount member.
	int		biClrImportant;		//	0	specifies the number of color that are 'important' for the bitmap, if set to zero, all colors are important.

	CImage *image;

public:
	CBitmap();
	
	bool LoadBMP(string name);
		
	bool SaveBMP(string name);
	
	void dump();
	
	CImage *getImage();

	void setImage(CImage* _image);
	
	
};

#endif /*CBITMAP_H_*/
