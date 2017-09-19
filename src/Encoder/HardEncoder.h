/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _hardencoder_
#define _hardencoder_

#include "systemc.h"

#include "../RGB2YUV/RGB2YUV.h"
#include "../Serializer/Serializer.h"
#include "../DCT2d/DCT2d.h"
#include "../Quantizer/Quantizer.h"
#include "../ZigZag/ZigZag.h"

SC_MODULE(HardEncoder)
{
public:
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_fifo_in <unsigned char > e;
    sc_fifo_out<  signed short> s;

	SC_CTOR(HardEncoder)
	{
        SC_CTHREAD(do_action, clk.pos());
        reset_signal_is(reset, true);
	}

private:
    void do_action();
};

#endif
