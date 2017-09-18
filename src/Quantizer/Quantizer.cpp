/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "Quantizer.h"



// q = 90%
static const unsigned char _YTable[64]  = {
        3,   2,   2,   3,   5,   8,  10,  12,
        2,   2,   3,   4,   5,  12,  12,  11,
        3,   3,   3,   5,   8,  11,  14,  11,
        3,   3,   4,   6,  10,  17,  16,  12,
        4,   4,   7,  11,  14,  22,  21,  15,
        5,   7,  11,  13,  16,  21,  23,  18,
       10,  13,  16,  17,  21,  24,  24,  20,
       14,  18,  19,  20,  22,  20,  21,  20
};

// q = 90%
static const unsigned char _UVTable[64] = {
        3,   4,   5,   9,  20,  20,  20,  20,
        4,   4,   5,  13,  20,  20,  20,  20,
        5,   5,  11,  20,  20,  20,  20,  20,
        9,  13,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20,
       20,  20,  20,  20,  20,  20,  20,  20
}; // why one more ?

void Quantizer::do_conversion(){
	while( true ){

		for(int y=0;y<64;y++){
			s.write( e.read() / _YTable[y] );
		}
		for(int y=0;y<64;y++){
			s.write( e.read() / _UVTable[y] );
		}
		for(int y=0;y<64;y++){
			s.write( e.read() / _UVTable[y] );
		}
	}
}
