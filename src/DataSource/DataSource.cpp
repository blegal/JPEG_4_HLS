/*
 *  Adder.cpp
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "DataSource.h"

void DataSource::do_gen()           // process
{
	int largeur = width;
	int hauteur = height;

	p.write( width  );
	p.write( height );

	for(int y = 0; y < hauteur; y += 8){
		for(int x = 0; x < largeur; x += 8){
//			printf("Sending macro-bloc (%d, %d)\n", x, y);
			for(int yy = 0; yy < 8; yy++){
				for(int xx = 0; xx < 8; xx++){
                    CvScalar p = cvGet2D(image, (y + yy), (x + xx));
					s.write  ( p.val[2] );
					s.write  ( p.val[1] );
					s.write  ( p.val[0] );
				}
			}
		}
	}
    cvReleaseCapture( &capture );
//	cout << "(II) Pixel sending finished" << endl;
}
