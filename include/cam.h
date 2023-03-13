#pragma once
#include "opencv2/core/utility.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

class Camera {
public:
	Camera();
	~Camera();
	void compareFrames(Mat,Mat,Mat);
	bool detectMovement(Mat);
	void drawRectangle(Mat);
	void saveVideo();
	void captureVideo();
	VideoCapture cap;
private:
	Mat frame;
	Mat prev_frame;
	Mat current_frame;
	Mat next_frame;
	Mat display_frame;
	Mat isMotion;
	Mat eval1;
	Mat eval2;
	Mat kernel;
	int num_changes;
	int x_begin;
	int x_end;
	int y_begin;
	int y_end;
	int x_min;
	int x_max;
	int y_min;
	int y_max;
	double width;
	double height;
};
