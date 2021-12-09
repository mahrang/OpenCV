/* This program superimposes 1 face onto another in a photo.
 Need to use photos provided with this code because it is written
 specifically for these photos.  If the location or size of faces in photos
 is different than those in the photos provided, this code won't work as
 well.
 Arguments passed need to be in this order:
 faceTemplate.jpg
 faces.png
 230
 155
 0.8
 0.2  */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;

void help(const char **argv) {
  cout << "This program alpha blends the first image onto the other. \n"
       << "alpha is the blending of the first image and beta onto the second\n"
       << endl;
}


int main( int argc, const char** argv )
{
    help(argv);
    if(argc != 7) {
        cout << "ERROR: Wrong # of parameters (7), you had " << argc  << "\n" << endl;
        return -1;
    }


  // Using the first two arguments, open up the image to be copied onto
  // (src1), and the image that will be copied from (src2).
  //
  cv::Mat src1 = cv::imread(argv[1],1);  // src1 = faceTemplate.jpg
  cv::Mat src2 = cv::imread(argv[2],1);  // src2 = faces.png

    int from_w = src1.size().width;
    int from_h = src1.size().height;
    int to_w = src2.size().width;
    int to_h = src2.size().height;


  if( argc==7 && !src1.empty() && !src2.empty() ) {

    // Four more arguments tell where in src1 to paste the chunk taken from
    // src2. Note that the width and height also specify what portion of
    // src2 to actually use.
    //
    int x = atoi(argv[3]);  // x = 230
    int y = atoi(argv[4]);  // y = 155

    // Make sure we don't exceed bounds:
    if((x < 0) || (y < 0) || (x > to_w - 1) || (y > to_h - 1) || (x+from_w > to_w - 1) || (y+from_h > to_h)) {
        cout << "\nError, at (x,y) (" << x << ", " << y <<"), your input image [w,h] [" << from_w << ", "
        << from_h << "] doesn't fit within the blend to image [w,h] [" << to_w << ", " << to_h  <<"]\n" << endl;
        return -1;
    }

    // Two more arguments set the blending coefficients.
    //
    double alpha = (double)atof(argv[5]);  // alpha = 0.8
    double beta  = (double)atof(argv[6]);  // beta = 0.2, beta = 1 - alpha

    cv::Mat roi1( src1, cv::Rect(0,0,from_w - 1,from_h - 1) ); //Just take the whole thing
    // roi2 is just the man's face in faces.png
    cv::Mat roi2( src2, cv::Rect(x,y,from_w - 1, from_h - 1) );

    // Blend together the image src2 onto the image src1
    // at the specified location.
    // addWeighted equation is roi2 = roi1 x alpha + roi2 x beta + gamma
    cv::addWeighted( roi1, alpha, roi2, beta, 0.0, roi2 );  // gamma = 0

    // Create a window to show the result and show it.
    //
    cv::namedWindow( "Alpha Blend", 1 );
    cv::imshow( "Alpha Blend", src2 );

    // Leave the window up and running until the user hits a key
    //
    cv::waitKey( 0 );

  }

  return 0;

}
