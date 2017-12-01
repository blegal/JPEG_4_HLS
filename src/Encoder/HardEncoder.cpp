#include "HardEncoder.h"

#include <cstdlib>

using namespace std;

#ifdef MACOS
#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <fcntl.h>
	#include <sys/ioctl.h>
	#include <errno.h>
	#include <paths.h>
	#include <termios.h>
	#include <sysexits.h>
	#include <sys/param.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <time.h>
	#include <cassert>
	#include <stdint.h>
	#include <signal.h>
#else
    #include <stdio.h>
    #include <string.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <errno.h>
    #include <paths.h>
    #include <termios.h>
    #include <sysexits.h>
    #include <sys/param.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <time.h>
    #include <cassert>
#endif

void HardEncoder::do_action()
{
    int fileDescriptor = -1;

//#define MACOS
#ifdef MACOS
    vector<std::string> vs;
    vs.push_back("/dev/cu.usbserial-210274532517B");
    vs.push_back("/dev/cu.usbserial-210274532517A");
    vs.push_back("/dev/cu.usbserial-210274532245B");
    vs.push_back("/dev/cu.usbserial-210274532245A");
    vs.push_back("/dev/cu.usbserial-A503PYMW");
    vs.push_back("/dev/cu.usbserial-210274533335B");
    vs.push_back("/dev/cu.usbserial-210274533335A");
    vs.push_back("/dev/cu.usbserial-210274531985B");
    vs.push_back("/dev/cu.usbserial-210274531985A");

    for (int i = 0; i < vs.size(); i += 1) {
        std::string s = vs.at(i);
        fileDescriptor = open(s.c_str(), O_RDWR | O_NOCTTY);
        if (fileDescriptor != -1)
            break;
    }

    if (fileDescriptor == -1) {
        printf("(II) Connection to board : FAILED\n");
        exit(0);
    }

    printf("(II) Connection to board : OK\n");

    struct termios theTermios;
    memset(&theTermios, 0, sizeof(struct termios));
    cfmakeraw(&theTermios);
    cfsetspeed(&theTermios, 921600);
    theTermios.c_cflag = CREAD | CLOCAL;     // turn on READ
    theTermios.c_cflag |= CS8;
    theTermios.c_cc[VMIN] = 0;
    theTermios.c_cc[VTIME] = 5;     // 5 sec timeout
    ioctl(fileDescriptor, TIOCSETA, &theTermios);
#else
    fileDescriptor = open("/dev/ttyUSB1", O_RDWR | O_NOCTTY );
    if(fileDescriptor == -1)
    {
        printf("Impossible d'ouvrir ttyUSB1 !\n");
        exit( 0 );
    }
    struct termios t;
    tcgetattr(fileDescriptor, &t); // recupère les attributs
    cfmakeraw(&t); // Reset les attributs
    t.c_cflag     = CREAD | CLOCAL;     // turn on READ
    t.c_cflag    |= CS8;
    t.c_cc[VMIN]  = 0;
    t.c_cc[VTIME] = 50;     // 5 sec timeout
    //cfsetspeed(&t, B115200); // règle la vitesse
    cfsetispeed(&t, B921600);
    cfsetospeed(&t, B921600);
    tcsetattr(fileDescriptor, TCSAFLUSH, &t); // envoie le tout au driver
#endif

    int cpt = 0;
    while( true ){
//        printf("Processing MB : %d\\n", cpt++);
        char ibuffer[3 * 64];
        for(int i = 0; i < 3 * 64; i += 1) ibuffer[i] = e.read();
        int wBytes = write( fileDescriptor, ibuffer, 3 * 64 * sizeof(unsigned char) );
        assert( wBytes == (3 * 64 * sizeof(unsigned char)) );

        signed short obuffer[3 * 64];
        int rBytes = read( fileDescriptor, obuffer, 3 * 64 * sizeof(signed short) );
        assert( rBytes == (3 * 64 * sizeof(signed short)) );
        for(int i = 0; i < 3 * 64; i += 1){
            obuffer[i] = ((obuffer[i] & 0xFF) << 8) | ((obuffer[i] >> 8) & 0xFF);
        }
        for(int i = 0; i < 3 * 64; i += 1) s.write( obuffer[i] );
    }
}
