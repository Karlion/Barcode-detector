#include "BarcodeDetection.h"

BarcodeDetector::BarcodeDetector() : ddepth(CV_16S) {}

Mat BarcodeDetector::getBarcodeLocation(Mat image)
{
	this->image = image;
	Mat graddiff = gradDifference();
	return getImageWithRectangle(graddiff);
}

Mat BarcodeDetector::gradDifference()
{
	Mat gradX, gradY;
	Mat absGradX, absGradY;
	cvtColor(this->image, this->grayImage, CV_BGR2GRAY);
	Sobel(this->grayImage, gradX, ddepth, 1, 0);
	Sobel(this->grayImage, gradY, ddepth, 0, 1);
	convertScaleAbs(gradX, absGradX);
	convertScaleAbs(gradY, absGradY);

	return absGradX - absGradY;
}

Mat BarcodeDetector::getImageWithRectangle(Mat gradDiff)
{
	blur(gradDiff, this->imageSmooth, Size(31, 31));
	double minValue, maxValue;
	Point minPoint, maxPoint;	
	minMaxLoc(this->imageSmooth, &minValue, &maxValue, &minPoint, &maxPoint);

	if (maxValue > 135.0)
	{
		Mat thres;
		threshold(this->imageSmooth, thres, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
		Rect rect = crop(thres, maxPoint);
		Scalar borderColor(0, 0, 255);
		int borderWidth = 3;
		rectangle(this->image, rect, borderColor, borderWidth);
	}
	return this->image;
}

Rect BarcodeDetector::crop(Mat thresImage, Point MaxPoint){
	int x = MaxPoint.x;
	int y = MaxPoint.y;

	Rect Location;

	int leftLocation = -1, rightLocation = -1, upLocation = -1, downLocation = -1;

	for (int i(x); thresImage.ptr<uchar>(y)[i] != 0; i--) 
		leftLocation = i;
	for (int i(x); thresImage.ptr<uchar>(y)[i] != 0; i++) 
		rightLocation = i;
	for (int i(y); thresImage.ptr<uchar>(i)[x] != 0; i++) 
		downLocation = i;
	for (int i(y); thresImage.ptr<uchar>(i)[x] != 0; i--) 
		upLocation = i;

	Location.x = leftLocation;
	Location.y = upLocation;
	Location.width = rightLocation - leftLocation;
	Location.height = downLocation - upLocation;

	return Location;
}