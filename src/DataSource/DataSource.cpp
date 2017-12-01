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
	CBitmap *fichier = new CBitmap();
	bool ok = fichier->LoadBMP( filename.c_str() );
	if( ok == false ){
		cout << "(EE) Image file (" << filename << ") not found !" << endl;
		exit( 0 );
	}
	CImage   *img = fichier->getImage();

	cout << "(II) Starting pixel data sending" << endl;
	int largeur = img->getLigne(0)->size();
	int hauteur = img->size();

    p.write( largeur );
    p.write( hauteur );

	for(int y = 0; y < hauteur; y += 8){
		for(int x = 0; x < largeur; x += 8){
			for(int yy = 0; yy < 8; yy++){
				for(int xx = 0; xx < 8; xx++){
        			CPixel *p1 = img->getPixel(x+xx, y+yy);
			        s.write  ( (unsigned char)p1->Red()   );
//			        wait( 10, SC_NS );
			        s.write( (unsigned char)p1->Green() );
//			        wait( 10, SC_NS );
			        s.write ( (unsigned char)p1->Blue()  );
//			        wait( 10, SC_NS );
				}
			}
		}
	}

	cout << "(II) Pixel sending finished" << endl;
	delete fichier;
}
