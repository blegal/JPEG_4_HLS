/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "systemc.h"

SC_MODULE(DataSource)          // module (class) declaration
{
private:
	CvCapture* capture;
	IplImage*  image;	

public:
	int width;
	int height;

	sc_fifo_out<int> s; // pixel values
	sc_fifo_out<int> p; // parameters

	DataSource(sc_module_name nm, const std::string ifile) : sc_module(nm)
	//SC_CTOR(ImageIn)
	{
	    capture = cvCreateFileCapture( ifile.c_str() );
	    image   = cvQueryFrame( capture );
	    printf("+ Image characteristics:\n");
	    printf("  -> nSize        = %d\n", image->nSize);
	    printf("  -> nChannels    = %d\n", image->nChannels);
	    printf("  -> alphaChannel = %d\n", image->alphaChannel);
	    printf("  -> depth        = %d\n", image->depth);
	    printf("  -> colorModel   = %s\n", image->colorModel);
	    printf("  -> channelSeq   = %s\n", image->channelSeq);
	    printf("  -> dataOrder    = %d\n", image->dataOrder);
	    printf("  -> width        = %d\n", image->width);
	    printf("  -> height       = %d\n", image->height);
		width   = image->width;
		height  = image->height;
		SC_THREAD(do_gen);
	}

  	SC_HAS_PROCESS(DataSource);

    void do_gen();
};
