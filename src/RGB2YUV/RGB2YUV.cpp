/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "RGB2YUV.h"


#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)


#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a<b)?b:a)
#define LIMIT(a,b,c) MIN(MAX(a,b),c)

const int Wl = 12; // 5 EST LA VALEUR MINIMUM AFIN D'ASSURER LA QUALITE VISUELLE

const int C1 = ((1<<Wl) * 0.299);
const int C2 = ((1<<Wl) * 0.587);
const int C3 = ((1<<Wl) * 0.114);
const int C4 = ((1<<Wl) * 0.16874);
const int C5 = ((1<<Wl) * 0.33126);
const int C6 = ((1<<Wl) * 0.5);
const int C7 = ((1<<Wl) * 0.41869);
const int C8 = ((1<<Wl) * 0.08131);

void rgb2yuv(int vR, int vG, int vB, int ycbcr[3]){
	const int Y   = 0 + (int)C1 * vR + (int)C2 * vG + (int)C3 * vB;
	const int Cb  = 0 - (int)C4 * vR - (int)C5 * vG + (int)C6 * vB;
	const int Cr  = 0 + (int)C6 * vR - (int)C7 * vG - (int)C8 * vB;
	const int fY  =  (Y  >> (Wl)) - 128;
	const int fCb =  (Cb >> (Wl));
	const int fCr =  (Cr >> (Wl));
	ycbcr[0]  = LIMIT(fY,  -128, 127);
	ycbcr[1]  = LIMIT(fCb, -128, 127);
	ycbcr[2]  = LIMIT(fCr, -128, 127);
}

void RGB2YUV::do_conversion(){
	int t[3];
	while( true ){

		int r = e.read();
		int g = e.read();
		int b = e.read();

		rgb2yuv(r, g, b, t);

	    s.write( t[0] );
	    s.write( t[1] );
	    s.write( t[2] );
	}
}
