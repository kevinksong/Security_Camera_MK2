#include "opencv2/core/utility.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <ctype.h>
#include "cam.h"
using namespace cv;
using namespace std;

int main()
{
    Camera cam = Camera();
    while (true) {
        cam.captureVideo();
        if (waitKey(30) == 27) 		//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            cout << "esc key pressed by user" << endl;
            break;
        }
    }
    return 0;
}