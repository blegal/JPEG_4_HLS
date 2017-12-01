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
		fin  ("FIFO_I", 192),
    	fou  ("FIFO_O", 192)
	{
		enc.clk(clk); enc.reset(reset);
		enc.e(fin);
		enc.s(fou);

		SC_CTHREAD(do_action, clk.pos());
		reset_signal_is(reset, true);
	}

private:
    Encoder enc;
	sc_fifo<unsigned char>  fin;
	sc_fifo<signed  short> fou;


	void do_action(){
		unsigned char  i_buffer[192];

		while( true ){

			//
			// ON MEMORISE LES DONNEES PROVENANT DE L'UART
			//
			for(int i = 0; i < 192; i += 1)
				i_buffer[ i ] = e.read();

			//
			// ON TRANSMET LES DONNEES VERS LE SYSTEME
			//
			for(int i = 0; i < 192; i += 1)
				fin.write( i_buffer[ i ] );

			//
			// ON RECUPERE LES DONNEES DEPUIS LE SYSTEME
			// ON ENVOIE LES DONNEES VERS L'UART
			//
			for(int i = 0; i < 192; i += 1){
				signed short v = fou.read();
				s.write( (v >>    8) );
				s.write( (v  & 0xFF) );
			}
		}
	}
};

#endif
