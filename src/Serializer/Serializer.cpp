/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "Serializer.h"

void Serializer::do_action(){
	int y[64];
	int cr[64];
	int cb[64];

	while( true ){
		for(int p=0; p<64; p++){
			y [p] = e.read();
			cb[p] = e.read();
			cr[p] = e.read();
		}

		for(int k=0; k<64; k++){ s.write( y[k]  ); }

		for(int k=0; k<64; k++){ s.write( cb[k] ); }

		for(int k=0; k<64; k++){ s.write( cr[k] ); }
	}
}

