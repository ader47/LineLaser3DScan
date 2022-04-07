#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iomanip>
#include <iostream>
#include <vector>

class ROI {
private:
	cv::Point LeftUP;
	cv::Point RightDOWN;
	int times=0;
public:
	cv::Point GetLeftUP();
	cv::Point GetRightDOWN();
	ROI(cv::Point LeftUP, cv::Point RightDOWN);
	void SetLeftUP(cv::Point p);
	void SetRightDOWN(cv::Point p);
	void Select_ROI(int EVENT, int x, int y, int flags, void* userdata);
};


class ProcessTool 
{
public:
	std::vector<double> AverageLine(cv::Mat img, cv::Point2d leftup, cv::Point2f rightdown);
	std::vector<double> StegerLine(cv::Mat img0, int col = 3, int row = 9, int sqrtx = 1, int sqrty = 1 ,int shreshold = 80, float distance = 0.5, bool isFloat = false);
private:
	void ShowLine(std::vector<double> Points, cv::Mat image);
};

#endif