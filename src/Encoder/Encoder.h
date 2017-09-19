/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _encoder_
#define _encoder_

#include "systemc.h"

#include "../RGB2YUV/RGB2YUV.h"
#include "../Serializer/Serializer.h"
#include "../DCT2d/DCT2d.h"
#include "../Quantizer/Quantizer.h"
#include "../ZigZag/ZigZag.h"

SC_MODULE(Encoder)
{
public:
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_fifo_in <unsigned char > e;
    sc_fifo_out<  signed short> s;

	SC_CTOR(Encoder):
		yuv ("RGB2YUV"   ),
		ser ("Serializer"),
		dct ("DCT2d"     ),
		qtz ("Quantizer" ),
		zig ("ZigZag"    ),
		s2  ("FIFO_2", 64),
		s3  ("FIFO_3", 64),
		s4  ("FIFO_4", 64),
		s5  ("FIFO_5", 64)
	{
		yuv.clk(clk); yuv.reset(reset);
		ser.clk(clk); ser.reset(reset);
		dct.clk(clk); dct.reset(reset);
		qtz.clk(clk); qtz.reset(reset);
		zig.clk(clk); zig.reset(reset);

		yuv.e(e);
		yuv.s(s2); /* => */ ser.e(s2);
		ser.s(s3); /* => */ dct.e(s3);
		dct.s(s4); /* => */ qtz.e(s4);
		qtz.s(s5); /* => */ zig.e(s5);
		zig.s(s);
	}

private:
    RGB2YUV    yuv;
    Serializer ser;
    DCT2d      dct;
    Quantizer  qtz;
	ZigZag     zig;

	sc_fifo<int>  s2;
	sc_fifo<int>  s3;
	sc_fifo<int>  s4;
	sc_fifo<int>  s5;
};

#endif
