/*
 *  Adder.cpp
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "DataSource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

void DataSource::do_gen()           // process
{
	cv::Mat im1   = cv::imread( filename.c_str() );
	cv::Size size = im1.size();
	int cn = im1.channels();

	int largeur = size.width;
	int hauteur = size.height;
	assert( largeur != 0 );
	assert( hauteur != 0 );

	p.write( size.width  );
	p.write( size.height );

	for(int y = 0; y < hauteur; y += 8){
		for(int x = 0; x < largeur; x += 8){
//			printf("Sending macro-bloc (%d, %d)\n", x, y);
			for(int yy = 0; yy < 8; yy++){
				for(int xx = 0; xx < 8; xx++){
					uint8_t* pixelPtr = (uint8_t*)im1.data;

					unsigned char B = pixelPtr[(yy+y) * largeur * cn + (x + xx) * cn + 0]; // B
					unsigned char G = pixelPtr[(yy+y) * largeur * cn + (x + xx) * cn + 1]; // G
					unsigned char R = pixelPtr[(yy+y) * largeur * cn + (x + xx) * cn + 2]; // R
					s.write  ( R );
					s.write  ( G );
					s.write  ( B );

//                    CvScalar p = cvGet2D(image, (y + yy), (x + xx));
//					s.write  ( p.val[2] );
//					s.write  ( p.val[1] );
//					s.write  ( p.val[0] );
				}
			}
		}
	}
//    cvReleaseCapture( &capture );
//	cout << "(II) Pixel sending finished" << endl;
}
