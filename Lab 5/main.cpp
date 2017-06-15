#define _CRT_SECURE_NO_WARNINGS
#include"opencv2\opencv.hpp"
#include<iostream>
#include<vector>
#include<string>
#include"BarcodeDetection.h"

using namespace std;
using namespace cv;

Mat DownloadImage(string filename)
{
	auto image = imread(filename);
	if (image.empty())
		throw runtime_error("Can't load image");
	return image;
}

void main()
{
	BarcodeDetector detector;

	vector<string> names = { "test.jpg", "test1.jpg", "test2.jpg" };

	for (auto name : names)
	{
		Mat image = DownloadImage(name);

		detector.getBarcodeLocation(image);

		namedWindow("barcodes", WINDOW_AUTOSIZE);
		imshow("barcodes", image);
		waitKey(0);
	}

}