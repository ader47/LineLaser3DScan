#include "Threads.h"
CameraDisplay::~CameraDisplay()
{
	videocapture->release();
	delete videocapture;
}

cv::Mat CameraDisplay::GetFrame()
{
	mutex.lock();
	res = matFrame.clone();
	mutex.unlock();
	return this->res;
}

float CameraDisplay::GetFPS()
{
	float fps = 0;
	if (videocapture->isOpened())
	{
		fps = videocapture->get(cv::CAP_PROP_FRAME_COUNT);
	}
	return 0;
}

void CameraDisplay::run()
{
	isStart = true;
	while (isStart)
	{
		cv::Mat graymat;
		std::vector<cv::Point2f> corner;
		mutex.lock();
		videocapture->read(matFrame);
		cv::cvtColor(matFrame, graymat, CV_BGR2GRAY);
		bool isFind;
		//对称圆形矩阵标定板
		isFind = findCirclesGrid(graymat, cv::Size(7, 7), corner, cv::CALIB_CB_SYMMETRIC_GRID);
		if (isFind)
			drawChessboardCorners(matFrame, cv::Size(7, 7), corner, isFind);
		imshow(winName, matFrame);
		mutex.unlock();
	}
}

void CameraDisplay::StopThread()
{
	isStart = false;
}

CameraDisplay::CameraDisplay(int CameraID,std::string winName, QObject* parent)
{
	this->winName = winName;
	videocapture = new cv::VideoCapture(CameraID);
}