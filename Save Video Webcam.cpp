/* This program records and saves video from file or webcam into "output.mp4"
 file.
 If input video is provided, program will play video and save it in "output.mp4".
 If no input is provided, program will stream webcam and save the stream in
 "output.mp4". */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int main(int argc, const char * argv[]) {
    
    cv::VideoCapture cap;
    
    if (argc == 2) {      // if input is video file
        cap.open(argv[1]);
    } else cap.open(0);  // if no input provided, webcam will be used
    
    if (!cap.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
        return -1;
    }
    
    cv::VideoWriter out("output.mp4", CV_FOURCC('a','v','c','1'), 30.0,
                        cv::Size( 960, 540 ));
    if (!out.isOpened()) {
        cout << "Unable to record video"  << endl;
        return -1;
    }

    while(true) {
        cv::Mat frame;
        cap >> frame;
        if(frame.empty()) break;
        cv::resize(frame, frame, cv::Size(960, 540), 0, 0, cv::INTER_CUBIC);
        cv::imshow("Camera feed", frame);
        out << frame;
        if (cv::waitKey(10) == 27) break;
    }
    cap.release();
    out.release();
    return 0;
}
