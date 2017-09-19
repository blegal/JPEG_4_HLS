/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "systemc.h"

SC_MODULE(DataSink)
{
	sc_fifo_in<signed short> e; // pixel values
	sc_fifo_in<int> p; // parameters

	void do_print();

	SC_CTOR(DataSink)
	{
		SC_THREAD(do_print);
	}

};
