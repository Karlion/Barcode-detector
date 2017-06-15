#include "opencv2/opencv.hpp"

using namespace cv;

class BarcodeDetector {
public:
	BarcodeDetector();
	Mat getBarcodeLocation(Mat);

private:

	Mat image;
	Mat grayImage;
	Mat imageSmooth;

	Rect crop(Mat, Point);
	Mat gradDifference();
	Mat getImageWithRectangle(Mat);

	const int ddepth;
};