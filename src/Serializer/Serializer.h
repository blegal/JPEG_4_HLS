/*
 *  Adder.h
 *  SystemC_SimpleAdder
 *
 *  Created by Le Gal on 07/05/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "systemc.h"

SC_MODULE(Serializer)
{
//private:
//	int t[3];

public:
	sc_fifo_in <int> e;
    sc_fifo_out<int> s;

	SC_CTOR(Serializer)
	{
		SC_THREAD(do_conversion);
	}

    void do_conversion();
 };
