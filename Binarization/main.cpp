/* This program takes a color image, converts it to grayscale, Gaussian blurs and
 downscales the grayscale image by a factor of 2 twice, then uses Canny edge
 detection to binarize the twice-reduced image.  It outputs the RGB pixel value
 at a particular point in the color image, the gray pixel value at that point in
 the grayscale image, and the pixel value at that point in the binarized photo.
 Then it sets the pixel value at that point in the binarized photo to a different
 value and displays the resulting binarized photo and the grayscale image.
 Color image used was fruits.jpg  */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
    
int main( int argc, char** argv ) {
    
  cv::Mat img_rgb, img_gry, img_cny, img_pyr, img_pyr2;

  cv::namedWindow( "Example Gray", cv::WINDOW_AUTOSIZE );
  cv::namedWindow( "Example Canny", cv::WINDOW_AUTOSIZE );

  img_rgb = cv::imread( argv[1] );

  cv::cvtColor( img_rgb, img_gry, cv::COLOR_BGR2GRAY);

  //cv::pyrDown performs Gaussian blurring & downsampling by a factor of 2
  cv::pyrDown( img_gry, img_pyr );
  cv::pyrDown( img_pyr, img_pyr2 );  //img_pyr2 is 1/4 width & height of original

  cv::Canny( img_pyr2, img_cny, 10, 100, 3, true );

  int x = 16, y = 32;
  cv::Vec3b intensity = img_rgb.at< cv::Vec3b >(y, x);  //reads in RGB pixel

  //Assigns the RGB pixel values at x = 16, y = 32 to variables
  uchar blue  = intensity[0];
  uchar green = intensity[1];
  uchar red   = intensity[2];

  cout << "At (x,y) = (" << x << ", " << y <<
    "): (blue, green, red) = (" <<
    (unsigned int)  blue <<
    ", " << (unsigned int) green << ", " <<
    (unsigned int)  red << ")" << endl;

  cout << "Gray pixel there is: " <<
    (unsigned int)  img_gry.at<uchar>(y, x) << endl;

  x /= 4; y /= 4;  //since img_pyr2 is 1/4 width & height of img_rgb

  cout << "Pyramid2 pixel there is: " <<
    (unsigned int)img_pyr2.at<uchar>(y, x) << endl;

  img_cny.at<uchar>(x, y) = 128; // Set the Canny pixel there to 128

  cv::imshow( "Example Gray", img_gry );
  cv::imshow( "Example Canny", img_cny );

  cv::waitKey(0);

}
