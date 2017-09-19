/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _uart_wrapper_
#define _uart_wrapper_

#include "Encoder.h"

SC_MODULE(uart_wrapper)
{
public:
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_fifo_in <unsigned char> e;
    sc_fifo_out<unsigned char> s;

	SC_CTOR(uart_wrapper):
		enc ("Encoder"   ),
		ff  ("FIFO_5", 64)
	{
		enc.clk(clk); enc.reset(reset);
		enc.e(e);
		enc.s(ff);

		SC_CTHREAD(do_action, clk.pos());
		reset_signal_is(reset, true);
	}

private:
    Encoder enc;
	sc_fifo<signed short> ff;

	void do_action(){
		while( true ){
			signed short v = ff.read();
			s.write( (v >>    8) );
			s.write( (v  & 0xFF) );
		}
	}
};

#endif
