#include "ImageProcess.h"

cv::Point ROI::GetLeftUP()
{
	return LeftUP;
}

cv::Point ROI::GetRightDOWN()
{
	return RightDOWN;
}

ROI::ROI(cv::Point LeftUP, cv::Point RightDOWN)
{
	this->LeftUP = LeftUP;
	this->RightDOWN = RightDOWN;
}

void ROI::SetLeftUP(cv::Point p)
{
	this->LeftUP = p;
}

void ROI::SetRightDOWN(cv::Point p)
{
	this->RightDOWN = p;
}

void ROI::Select_ROI(int EVENT, int x, int y, int flags, void* userdata)
{
	switch (EVENT)
	{
	case cv::EVENT_LBUTTONDOWN:
	{
		cv::Point p(x, y);
		this->times++;
		switch (this->times)
		{
		case 1:
			LeftUP = p;
			break;
		case 2:
			RightDOWN = p;
			break;
		default:
			break;
		}
		//std::cout << p << std::endl;
	}
	break;
	}
}

std::vector<double> ProcessTool::AverageLine(cv::Mat img0, cv::Point2d leftup, cv::Point2f rightdown)
{
	//预处理
	cv::Mat  img;
	img = img0.clone();
	//GaussianBlur(img0, img0, Size(3, 3), 2, 2);
	cv::medianBlur(img0, img0, 5);
	cvtColor(img0, img0, CV_RGB2GRAY);
	threshold(img0, img0, 0, 255, cv::THRESH_OTSU);
	std::vector<double> result;
	for (size_t i = leftup.x; i < rightdown.x; i++)
	{
		//cout << "a" << endl;
		int sum = 0; int num = 0;
		for (size_t j = leftup.y; j < rightdown.y; j++)
		{
			if (img0.at<uchar>(j, i) == 255)
			{
				sum += j;
				num++;
			}
		}
		if (num == 0)
			continue;
		result.push_back(i);
		result.push_back(1.0 * sum / num);
	}
	ShowLine(result, img);
	return result;
}

std::vector<double> ProcessTool::StegerLine(cv::Mat img0,int col,int row,int sqrtx,int sqrty,int shreshold,float distance,bool isFloat)
{
	if (img0.channels() == 3)
		cvtColor(img0,img0, CV_BGR2GRAY);
	cv::Mat img;
	img = img0.clone();
	//高斯滤波
	img.convertTo(img, CV_32FC1);
	//奇数,选择线宽
	GaussianBlur(img, img, cv::Size(col, row), sqrtx, sqrty);
	//cv::threshold(img, img, 70, 255, cv::THRESH_BINARY);
	//cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5), cv::Point(-1, -1));
	//cv::morphologyEx(img, img, CV_MOP_OPEN, kernel);
	//高斯卷积，得到一个山峰强度的光条图
	//高斯卷积核实际上就是一个正态函数
	// 
	//构造了求导数的卷积核
	//这里使用的是数值计算的偏导数而非得到求导公式
	cv::Mat m1, m2;
	m1 = (cv::Mat_<float>(1, 2) << 1, -1);//x偏导（创造一个Mat类矩阵）一阶偏导=f(x+1,y)-f(x,y)
	m2 = (cv::Mat_<float>(2, 1) << 1, -1);//y偏导（创造矩阵）一阶偏导=f(x,y+1)-f(x,y)
	cv::Mat dx, dy;
	//使用m1卷积 当前坐标的灰度值-（x+1）的灰度值
	filter2D(img, dx, CV_32FC1, m1);//卷积
	filter2D(img, dy, CV_32FC1, m2);//卷积
	//二阶偏导数
	cv::Mat m3, m4, m5;
	m3 = (cv::Mat_<float>(1, 3) << 1, -2, 1);//求二阶x偏导的矩阵=f(x+1,y)+f(x-1,y)-2f(x,y)
	m4 = (cv::Mat_<float>(3, 1) << 1, -2, 1);//二阶y偏导的矩阵
	m5 = (cv::Mat_<float>(2, 2) << 1, -1, -1, 1);//二阶xy偏导矩阵=f(x+1,y+1)-f(x+1,y)-f(x,y+1)+f(x,y)

	//Hessian矩阵是一个对称矩阵，而二次型矩阵也是对称矩阵
	cv::Mat dxx, dyy, dxy;
	//求得对应点的偏导数值
	filter2D(img, dxx, CV_32FC1, m3);
	filter2D(img, dyy, CV_32FC1, m4);
	filter2D(img, dxy, CV_32FC1, m5);

	//hessian矩阵
	double maxD = -1;
	int imgcol = img.cols;
	int imgrow = img.rows;
	std::vector<double> Pt;
	for (int i = 0; i < imgcol; i++)
	{
		for (int j = 0; j < imgrow; j++)
		{
			//大于一个阈值的时候开始计算
			if (img0.at<uchar>(j, i) > shreshold)
			{
				cv::Mat hessian(2, 2, CV_32FC1);
				//得到对应点的hessian矩阵
				//对每个点，构造出hessian矩阵
				hessian.at<float>(0, 0) = dxx.at<float>(j, i);
				hessian.at<float>(0, 1) = dxy.at<float>(j, i);
				hessian.at<float>(1, 0) = dxy.at<float>(j, i);
				hessian.at<float>(1, 1) = dyy.at<float>(j, i);

				cv::Mat eValue;
				cv::Mat eVectors;
				//hessian矩阵2*2 对称矩阵， 有两个特征值
				//获取当前点的特征值和特征向量
				// 存在两个特征值及对应特征向量
				// 特征值一个为正一个为负数
				//		eValue: [3.3130465;
				//				-37.06522]
				//	eVectors : [0.89511645, 0.44583231;
				//				-0.44583231, 0.89511645]
				eigen(hessian, eValue, eVectors);
				//std::cout << "eValue:" << eValue << std::endl << "eVectors:" << eVectors << std::endl;
				//nx为特征值最大对应的x，ny为特征值最大对应的y
				double nx, ny;
				double fmaxD = 0;
				//求特征值绝对值最大时对应的特征向量
				//Hessian矩阵的特征值就是形容其在该点附近特征向量方向的凹凸性，特征值越大，凸性越强。
				if (fabs(eValue.at<float>(0, 0)) >= fabs(eValue.at<float>(1, 0)))
				{
					nx = eVectors.at<float>(0, 0);
					ny = eVectors.at<float>(0, 1);
					fmaxD = eValue.at<float>(0, 0);
				}
				else
				{
					nx = eVectors.at<float>(1, 0);
					ny = eVectors.at<float>(1, 1);
					fmaxD = eValue.at<float>(1, 0);
				}
				// 使用泰勒展开表示光强的分布函数f(x+t*nx,y+t*ny)可以表示当前坐标附近的光强分布
				// f(x+t*nx,y+t*ny) hessian矩阵特征值最大的对应的特征向量(nx，ny)表示梯度上升最快的方向（光强改变最快），要往这个方向改变  
				// 由于x，y，nx,ny已知，这个当前坐标附近的光强分布函数可以看作是关于t的一个分布函数
				// 则可以对t求导，令导数为0的地方就是光强最强的地方（极值），也就是激光中心点。
				// 如果t*nx和t*ny都小于0.5说明这个极值点就位于当前像素内，附近光强分布函数适用
				// 如果t*nx和t*ny都很大，附近光强分布函数不适用，则跳过这个点，继续扫描距离激光中心更近的点
				double t = -
					(nx * dx.at<float>(j, i) + ny * dy.at<float>(j, i))
					/
					(nx * nx * dxx.at<float>(j, i) + 2 * nx * ny * dxy.at<float>(j, i) + ny * ny * dyy.at<float>(j, i));
				//t* nx和t* nx代表光条中心点距离当前像素的距离
				if (fabs(t * nx) <= distance && fabs(t * ny) <= distance)
				{
					if (isFloat)
					{
						Pt.push_back(i + t * nx);
						Pt.push_back(j + t * ny);
					}
					else 
					{
						Pt.push_back(i);
						Pt.push_back(j);
					}
				}
			}
		}
	}
	cvtColor(img0, img0, CV_GRAY2BGR);
	ShowLine(Pt, img0);
	return Pt;
}

void ProcessTool::ShowLine(std::vector<double> Points, cv::Mat image)
{
	for (int k = 0; k < Points.size() / 2; k++)
	{
		cv::Point rpt;
		rpt.x = Points[2 * k + 0];
		rpt.y = Points[2 * k + 1];
		image.at<cv::Vec3b>(rpt.y, rpt.x) = cv::Vec3b(0, 0, 255);
	}
	cv::imshow("GetLine", image);
	cv::waitKey(1);
}

