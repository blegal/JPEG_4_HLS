#include "./DataSource/DataSource.h"

#include "./RGB2YUV/RGB2YUV.h"
#include "./Serializer/Serializer.h"
#include "./DCT2d/DCT2d.h"
#include "./Quantizer/Quantizer.h"
#include "./ZigZag/ZigZag.h"

#include "./DataSink/DataSink.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <math.h>

using namespace std;

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

int main (int argc, char * argv []){
	cout << "Initialisation des composants..." << endl;

	std::string filename = "Perroquets.bmp";
	if( argc > 1){
		filename = argv[1];
	}

	DataSource src ("DataSource", filename);
    RGB2YUV    yuv ("RGB2YUV"   );
    Serializer ser ("Serializer");
    DCT2d      dct ("DCT2d"     );
    Quantizer  qtz ("Quantizer" );
	ZigZag     zig ("ZigZag"    );
	DataSink   dst ("DataSink"  );

	cout << "Mapping des composants..." << endl;
	sc_fifo<int>  s1("FIFO_1", 65536);
	sc_fifo<int>  s2("FIFO_2", 65536);
	sc_fifo<int>  s3("FIFO_3", 65536);
	sc_fifo<int>  s4("FIFO_4", 65536);
	sc_fifo<int>  s5("FIFO_5", 65536);
	sc_fifo<int>  s6("FIFO_6", 65536);
	sc_fifo<int>  pa("FIFO_7", 65536);

	src.s(s1); /* => */ yuv.e(s1);
	yuv.s(s2); /* => */ ser.e(s2);
	ser.s(s3); /* => */ dct.e(s3);
	dct.s(s4); /* => */ qtz.e(s4);
	qtz.s(s5); /* => */ zig.e(s5);
	zig.s(s6); /* => */ dst.e(s6);

	src.p(pa); /* => */ dst.p(pa);

	cout << "Lancement de la simulation du circuit..." << endl;
	sc_start(1000,SC_MS);
	cout << "Fin de la simulation du circuit..." << endl;

    cv::Mat im1 = cv::imread(filename.c_str());
    cv::Mat im2 = cv::imread("ofile.jpg");
    cv::Mat diff_im = 16 * (im1 - im2);

    namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Display window", diff_im );
    cout << "PSNR = " << getPSNR(im1, im2) << endl;
    cv::waitKey(0);

    return 0;
}
