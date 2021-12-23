/* This program takes a video file, plays it in 1 window, plays the grayscale
 version of it in a 2nd window, performs Canny edge detection on the video and
 displays the result in a 3rd window, and plays all 3 versions simultaneously
 next to each other in a 4th window. */

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;


void help(const char **argv) {
    cout << "\n\n"
        << "Call:\n"
        << argv[0] << " <path/video_name>\n\n"
        << "For example: ./" << argv[0] << " ../tree.avi\n"
        << endl;
}

int main( int argc, const char** argv )
{
    help(argv);
    if(argc < 2) {
        cout << "\nERROR: You had too few parameters.\n" << endl;
        return -1;
    }
    
    
    VideoCapture capture;
    if(!capture.open(argv[1])){
        cout << "Could not open " << argv[1] << endl;
        return 1;
    }
    double rate=capture.get(CV_CAP_PROP_FPS);
    Mat MatFrame;
    Mat MatGray;
    Mat MatCanny;
    int delay=1000/rate;
    cout << "rate = " << rate << ", delay = " << delay << endl;
    cout << "\nEsq to exit, or let it run out, then any key to release capture and exit.\n" << endl;
    //int frame_count = 0;
    while(1)
    {
        capture >> MatFrame;
        if( !MatFrame.data ) {
            cout << "Done with capture" << endl;
            break;
        }

       resize(MatFrame, MatFrame, cv::Size(426, 240), 0, 0, INTER_CUBIC);
      // was cv::resize(MatFrame, MatFrame, cv::Size(960, 540), 0, 0, cv::INTER_CUBIC);
      // used https://aspectratiocalculator.com/16-9.html to calculate
      // the 16:9 aspect ratio 426 x 240

        //(1)
        imshow("Raw Video",MatFrame);
        //(2)
        cvtColor(MatFrame,MatGray,COLOR_BGR2GRAY);
        imshow("Gray Video",MatGray);
        //(3)
        Canny(MatGray,MatCanny,100,255);
        imshow("Canny Video",MatCanny);
        //question a
        Mat MatAll(MatFrame.rows,3* MatFrame.cols  ,CV_8UC3,Scalar::all(0));
        cvtColor(MatGray,MatGray,COLOR_GRAY2BGR);
        cvtColor(MatCanny,MatCanny,COLOR_GRAY2BGR);
        Mat MatSub = MatAll.colRange(0, MatFrame.cols);
        MatFrame.copyTo(MatSub);
        MatSub = MatAll.colRange( MatFrame.cols,2*MatFrame.cols);
        MatGray.copyTo(MatSub);
        MatSub = MatAll.colRange(2*MatFrame.cols,3*MatFrame.cols);
        MatCanny.copyTo(MatSub);
        //question b
        Scalar color = CV_RGB(255,0,0);
        putText(MatAll,"raw video",Point(50,30),CV_FONT_HERSHEY_DUPLEX,1.0f,color);
        putText(MatAll,"gray video",Point(50+MatFrame.cols,30),CV_FONT_HERSHEY_DUPLEX,1.0f,color);
        putText(MatAll,"canny video",Point(50+2*MatFrame.cols,30),CV_FONT_HERSHEY_DUPLEX,1.0f,color);
        imshow("all Video",MatAll);

        if ((cv::waitKey(delay) & 255) == 27)
            break;
    }
    waitKey();
    capture.release();
    return 0;

}
