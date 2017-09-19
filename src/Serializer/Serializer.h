/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef _serializer_
#define _serializer_

#include "systemc.h"

SC_MODULE(Serializer)
{
public:
    sc_in<bool> clk;
    sc_in<bool> reset;

    sc_fifo_in <int> e;
    sc_fifo_out<int> s;

	SC_CTOR(Serializer)
	{
        SC_CTHREAD(do_action, clk.pos());
        reset_signal_is(reset, true);
	}

private:
    void do_action();
 };

#endif
