#include "cam.h"

using namespace std;
using namespace cv;

Camera::Camera() {
	//initialize videocapture
	cap = VideoCapture(0);
	namedWindow("Display Window");
	if (cap.isOpened()) {
		//width of the video capture device
		width = cap.get(CAP_PROP_FRAME_WIDTH);
		//height of the box
		height = cap.get(CAP_PROP_FRAME_HEIGHT);

		cout << "Width: " << width << " Height:" << height << endl;
		//capture prev_frame
		cap >> prev_frame;
		cvtColor(prev_frame, prev_frame, COLOR_RGB2GRAY);
		//capture current_frame
		cap >> current_frame;
		cvtColor(current_frame, current_frame, COLOR_RGB2GRAY);
		//capture next_frame
		cap >> next_frame;
		cvtColor(next_frame, next_frame, COLOR_RGB2GRAY);
		kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	}
	x_begin = 10;
	x_end = width - 10;
	y_begin = 10;
	y_end = height - 10;
}

Camera::~Camera() {
	cap.release();
}
void Camera::drawRectangle(Mat frame) {
	if (x_min - 10 > 0) {
		x_min -= 10;
	}
	if (y_min - 10 > 0) {
		y_min -= 10;
	}
	if (x_max + 10 < display_frame.cols - 1) {
		x_max += 10;
	}
	if (y_max + 10 < display_frame.rows - 1) {
		y_max += 10;
	}
	Point x(x_min, y_min);
	Point y(x_max, y_max);
	Rect rect(x, y);
	rectangle(frame, rect, Scalar(0, 255, 255), 1, 4);
}

void Camera::captureVideo() {
	cap >> frame;
	display_frame = frame;
	cvtColor(frame, frame, COLOR_RGB2GRAY);
	compareFrames(prev_frame, current_frame, next_frame);
	if (detectMovement(isMotion)) {
		cout << "Movement detected." << endl;
		drawRectangle(display_frame);
	}
	imshow("Display Window", display_frame);

	//put frames in correct order again
	prev_frame = current_frame;
	current_frame = next_frame;
	next_frame = frame;
	//necessary for some reason
	waitKey(25);
}


void Camera::compareFrames(Mat prev, Mat curr, Mat next) {
	//convert frames to grayscale for comparison
	absdiff(prev, curr, eval1);
	absdiff(curr, next, eval2);
	bitwise_and(eval1, eval2, isMotion);
	threshold(isMotion, isMotion, 35, 255, THRESH_BINARY);
	erode(isMotion, isMotion, kernel);
}

bool Camera::detectMovement(Mat motion) {
	Scalar mean, stdDev;
	int numChanges = 0;
	x_min = motion.cols;
	x_max = 0;
	y_min = motion.rows;
	y_max = 0;
	meanStdDev(motion, mean, stdDev);
	if (stdDev[0] < 20) {
		for (int j = y_begin;j < y_end;j += 2) {
			for (int i = x_begin;i < x_end;i += 2) {
				if (static_cast<int>(motion.at<uchar>(j, i)) == 255) {
					numChanges++;
					if (x_min > i) {
						x_min = i;
					}
					if (x_max < i) {
						x_max = i;
					}
					if (y_min > j) {
						y_min = j;
					}
					if (y_max < j ){
						y_max = j;
					}
				}
			}
		}
	}
	if (numChanges != 0) {
		return true;
	}
	return false;
}

