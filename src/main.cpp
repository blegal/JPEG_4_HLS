#include "./DataSource/DataSource.h"
#include "./Encoder/Encoder.h"
#include "./Encoder/HardEncoder.h"
#include "./DataSink/DataSink.h"

//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <math.h>

using namespace std;
/*
double getPSNR(const cv::Mat& I1, const cv::Mat& I2)
{
    cv::Mat s1;
    absdiff(I1, I2, s1);       // |I1 - I2|
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2

    cv::Scalar s = sum(s1);         // sum elements per channel

    double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels

    if( sse <= 1e-10) // for small values return zero
        return 0;
    else
    {
        double  mse =sse /(double)(I1.channels() * I1.total());
        double psnr = 10.0*log10((255*255)/mse);
        return psnr;
    }
}
*/
int sc_main (int argc, char * argv []){
	cout << "Initialisation des composants..." << endl;

	std::string filename = "../data/Image_2.bmp";
	if( argc > 1){
		filename = argv[1];
	}

	DataSource  src ("DataSource", filename);
#if 0
    Encoder     enc ("Encoder" );
#else
    HardEncoder enc ("Encoder" );
#endif
	DataSink    dst ("DataSink");

	cout << "Mapping des composants..." << endl;
	sc_fifo<unsigned char> s1("FIFO_1", 65536);
	sc_fifo<signed short>  s6("FIFO_6", 65536);
	sc_fifo<int>           pa("FIFO_7", 65536);

    sc_clock clock("clock", 10, SC_NS, 0.5);
    sc_signal< bool > reset;
    reset = false;

    enc.clk  (clock);
    enc.reset(reset);
    src.s(s1); /* => */ enc.e(s1);
	enc.s(s6); /* => */ dst.e(s6);
	src.p(pa); /* => */ dst.p(pa);

	cout << "Lancement de la simulation du circuit..." << endl;
	sc_start(1, SC_MS);
	cout << "Fin de la simulation du circuit..." << endl;
/*
    cv::Mat im1 = cv::imread(filename.c_str());
    cv::Mat im2 = cv::imread("ofile.jpg");
    cv::Mat diff_im = (im1 - im2);

    cout << "PSNR = " << getPSNR(im1, im2) << endl;

    namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
    char c = 'a';
    do{
        cv::imshow( "Display window", diff_im );
        c = cv::waitKey(0);
        if( c == 'a' ) diff_im *= 2;
        if( c == 'z' ) diff_im /= 2;
    }while( c != 'q' );
*/
    return 0;
}
