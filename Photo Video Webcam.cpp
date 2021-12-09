/*  This program will display a photo, play a video, or stream the webcam feed
 back to the user depending on the input file provided.
 If file on disk is an image, argument passed should be "--image <file path>".
 If file on disk is a video, argument passed should be "--video <file path>".
 If no file is provided, it will stream the webcam feed back to the user. */

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;

int showImageFromDisk(string imagePath) {
    cv::Mat image = cv::imread(imagePath);
    // process image
    cv::imshow("Image from disk", image);
    cv::waitKey();
    return 0;
}

int showVideoFromDisk(string videoPath) {
    cv::VideoCapture videoCapture(videoPath);
    if (!videoCapture.isOpened()) {
        cout << "Error opening video stream of file" << endl;
        return -1;
    }
    while (true) {
        cv::Mat frame;
        videoCapture >> frame;
        // process frame here
        if (frame.empty()) break;
        cv::resize(frame, frame, cv::Size(960, 540), 0, 0, cv::INTER_CUBIC);
        cv::imshow("Video frame", frame);
        if (cv::waitKey(10) == 27) break;
    }
    videoCapture.release();
    cv::waitKey();
    return 0;
}

int streamWebcamFeed() {
    cv::VideoCapture videoCapture(0);
    if (!videoCapture.isOpened()) {
        cout << "Unable to connect to webcam"  << endl;
        return -1;
    }
    while(true) {
        cv::Mat frame;
        videoCapture >> frame;
        if(frame.empty()) break;
        cv::imshow("Camera feed", frame);
        if (cv::waitKey(10) == 27) break;
    }
    videoCapture.release();
    return 0;
}


int main(int argc, const char * argv[]) {
    if (argc == 3) {
        string readType(argv[1]);
        string filePath(argv[2]);
        if (readType == "--image") {
            return showImageFromDisk(filePath);
        } else if (readType == "--video") {
            return showVideoFromDisk(filePath);
        } else {
            return streamWebcamFeed();
        }
    } else {
        return streamWebcamFeed();
    }
    return 0;
}
