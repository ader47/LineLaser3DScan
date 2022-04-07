#include "Calibrate.h"

int CalibrateBoard::Get_CircleWidth()
{
	return circle_width;
}

int CalibrateBoard::Get_CircleHeight()
{
	return circle_height;
}

float CalibrateBoard::Get_SquareSize()
{
	return squaresize;
}

/// <summary>
/// 圆形标定板定义
/// </summary>
/// <param name="nums">标定板数量</param>
/// <param name="circle_width">宽上的圆的数目</param>
/// <param name="circle_height">高上的圆的数目</param>
/// <param name="squaresize">圆心距</param>
CalibrateBoard::CalibrateBoard(int nums,int circle_width, int circle_height, float squaresize)
{
	
	//初始化参数
	this->circle_height = circle_height;
	this->circle_width = circle_width;
	this->squaresize = squaresize;
	this->BoardNums = nums;
	//计算该标定板的世界坐标列表
	//是否设计成二维数组会更好
	calRealPoint(obj,circle_width,circle_height, nums,squaresize);
}

void CalibrateBoard::calRealPoint(std::vector<std::vector<cv::Point3f>>& obj, int boardwidth, int boardheight, int imgNumber, float squaresize)
{
	//	Mat imgpoint(boardheight, boardwidth, CV_32FC3,Scalar(0,0,0));
	std::vector<cv::Point3f> imgpoint;
	for (int rowIndex = 0; rowIndex < boardheight; rowIndex++)
		//从第一行第一列的点开始，求取它们的世界坐标
	{
		for (int colIndex = 0; colIndex < boardwidth; colIndex++)
		{
			//{行序列数*圆心距-（半个板子宽度），列序列数*圆心距-（半个板子高度）
			//得到的是相对于板子中心的世界坐标
			//定义标定板世界坐标的Z为0，原点为左上角
			imgpoint.push_back(
				cv::Point3f(
					(float)colIndex * squaresize - (boardwidth / 2 * squaresize), 
					(float)rowIndex * squaresize - (boardheight / 2 * squaresize),
					0
				)
			);
		}
	}
	for (int imgIndex = 0; imgIndex < imgNumber; imgIndex++)
	{
		obj.push_back(imgpoint);
		//把世界坐标点传出去
	}
}

bool CalibrateCamera::calibrate(CalibrateBoard *caliboard)
{
	float rms = calibrateCamera(
		caliboard->obj,
		this->imagePoint,
		this->imageSize,
		this->cameraMatrix,
		this->distCoeff,
		this->rvecsMat,
		this->tvecsMat,
		CV_CALIB_FIX_K3
	);
	//得到标定图片数量，其实也可以没有这个变量
	this->ImageNum = this->rvecsMat.size();
	//初始化误差数组
	this->Err_All = (double*)malloc(this->ImageNum *sizeof(double));
	//误差判别
	vector<cv::Point2f> image_points2;
	double err;
	for (int i = 0; i < this->ImageNum; i++)
	{
		vector<cv::Point3f> tempPointSet = caliboard->obj[i];
		/* 通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点 */
		projectPoints(tempPointSet, this->rvecsMat[i], this->tvecsMat[i], this->cameraMatrix, this->distCoeff, image_points2);
		/* 计算新的投影点和旧的投影点之间的误差*/
		vector<cv::Point2f> tempImagePoint = this->imagePoint[i];
		cv::Mat tempImagePointMat = cv::Mat(1, tempImagePoint.size(), CV_32FC2);
		cv::Mat image_points2Mat = cv::Mat(1, image_points2.size(), CV_32FC2);
		for (int j = 0; j < tempImagePoint.size(); j++)
		{
			image_points2Mat.at<cv::Vec2f>(0, j) = cv::Vec2f(image_points2[j].x, image_points2[j].y);
			tempImagePointMat.at<cv::Vec2f>(0, j) = cv::Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
		}
		err = norm(image_points2Mat, tempImagePointMat, cv::NORM_L2);
		this->total_err += err /= caliboard->Get_CircleHeight() * caliboard->Get_CircleWidth();
		this->Err_All[i] = err;
	}
	//标定失败判别？？？？？？？？？？？？？？？？？？
	//记得写
	return true;
}



void CalibrateCamera::LoadCalibImage(vector<cv::Mat> img)
{
	cv::Mat rgbImage, grayImage;
	//暂存每张图片的交点容器
	std::vector<cv::Point2f> corner;
	for (vector<cv::Mat>::iterator it = img.begin(); it != img.end(); it++)
	{
		//rgbImage = cv::imread(*it, CV_LOAD_IMAGE_COLOR);
		rgbImage = *it;
		imageSize = rgbImage.size();
		cv::cvtColor(rgbImage, grayImage, CV_BGR2GRAY);
		bool isFind;
		//对称圆形矩阵标定板
		isFind = findCirclesGrid(grayImage, cv::Size(7, 7), corner, cv::CALIB_CB_SYMMETRIC_GRID);
		if (isFind)
		{
			//画出找到的交点
			drawChessboardCorners(rgbImage, cv::Size(7, 7), corner, isFind);
			//将找到的交点放入容器
			this->imagePoint.push_back(corner);
			imshow("LoadCalibImage", rgbImage);
			cv::waitKey(1);
		}
	}
	cvDestroyWindow("LoadCalibImage");
}

cv::Point3f CalibrateCamera::getWorldPoints(const cv::Point2f& inPoints, cv::Mat& rvec, cv::Mat& tvec)
{
	cv::Mat rotationMatrix;//3*3
	Rodrigues(rvec, rotationMatrix);
	//激光在标定板平面上，标定板平面的世界坐标Z为0，是世界坐标
	double zConst = 0;
	double s;
	cv::Mat imagePoint = (cv::Mat_<double>(3, 1) << double(inPoints.x), double(inPoints.y), 1);
	//计算比例参数S
	cv::Mat tempMat, tempMat2;
	//R-1*M-1*uvPoint*s=[X,Y,Zc]+R-1*t
	//R-1*M-1*uvPoint*
	//利用Z=0来计算s的参数，这里并不是为了得出Z的值
	//使用第三个分量计算s
	tempMat = rotationMatrix.inv() * this->cameraMatrix.inv() * imagePoint;
	//[X,Y,Zc]+R-1*t
	tempMat2 = rotationMatrix.inv() * tvec;
	s = zConst + tempMat2.at<double>(2, 0);
	s /= tempMat.at<double>(2, 0);
	//计算世界坐标
	//s*Pc=M(RPo+T)-->Po=(R-1)[s*(M-1)Pc-T]
	//Mat wcPoint = rotationMatrix.inv() * (s * this->cameraMatrix.inv() * imagePoint - tvec);
	//计算x y的坐标
	cv::Mat wcPoint = rotationMatrix.inv() * (s * this->cameraMatrix.inv() * imagePoint - tvec);
	cv::Point3f worldPoint(wcPoint.at<double>(0, 0), wcPoint.at<double>(1, 0), wcPoint.at<double>(2, 0));
	return worldPoint;
}

void CalibrateCamera::adjustImage(cv::Mat& Image)
{
	cv::Mat mapx = cv::Mat(Image.size(), CV_32FC1);
	cv::Mat mapy = cv::Mat(Image.size(), CV_32FC1);
	cv::Mat R = cv::Mat::eye(3, 3, CV_32F);
	initUndistortRectifyMap(this->cameraMatrix, this->distCoeff, R, this->cameraMatrix, Image.size(), CV_32FC1, mapx, mapy);
	remap(Image, Image, mapx, mapy, cv::INTER_LINEAR);
	//C++调用完成局部变量自动回收不需要释放
}

int CalibrateCamera::GetImageNum()
{
	return ImageNum;
}

double* CalibrateCamera::GetErr_ALL()
{
	return Err_All;
}


cv::Mat CalibrateCamera::GetBaseRvecMat()
{
	return Base_RVecsMat;
}

cv::Mat CalibrateCamera::GetBaseTvecMat()
{
	return Base_TVecsMat;
}

cv::Mat CalibrateCamera::GetCameraMatrix()
{
	return cameraMatrix;
}

cv::Mat CalibrateCamera::GetDistCoeff()
{
	return distCoeff;
}

/// <summary>
/// 计算基准参数
/// </summary>
/// <param name="ImagePath">基准标定板图片路径</param>
/// <param name="caliboard">标定板参数，用来获取世界坐标</param>
void CalibrateCamera::BaseCaculate(cv::Mat rgbImage, CalibrateBoard *caliboard)
{
	//检测圆形标定板

	cv::Mat grayImage;
	//cout << "开始计算基准" << endl;
	std::vector<cv::Point2f> corner;
	//rgbImage = cv::imread(ImagePath, CV_LOAD_IMAGE_COLOR);
	cv::cvtColor(rgbImage, grayImage, CV_BGR2GRAY);
	bool isFind;
	//对称圆形矩阵标定板，不对称的更好？
	isFind = findCirclesGrid(grayImage, cv::Size(7, 7), corner, cv::CALIB_CB_SYMMETRIC_GRID);
	if (isFind)
	{
		//画出找到的交点
		drawChessboardCorners(rgbImage, cv::Size(7, 7), corner, isFind);
		//计算视图的外参数 旋转向量和平移向量
		solvePnP(caliboard->obj[0], corner, cameraMatrix, distCoeff, this->Base_RVecsMat, this->Base_TVecsMat, false, cv::SOLVEPNP_DLS);
		imshow("BaseCaculate", rgbImage);
		cv::waitKey(1);
	}
	cv::destroyWindow("BaseCaculate");
	//失败的情况？？？？
}

double CalibrateCamera::GetAverage_err()
{
	return this->total_err / ImageNum;
}

void LaserPlane::CaculateLaserPlane()
{
	//最小二乘法拟合平面
	//获取cv::Mat的坐标系以纵向为x轴，横向为y轴，而cvPoint等则相反
	cv::Mat A = cv::Mat::zeros(3, 3, CV_64FC1);
	cv::Mat B = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat X = cv::Mat::zeros(3, 1, CV_64FC1);
	double x2 = 0, xiyi = 0, xi = 0, yi = 0, zixi = 0, ziyi = 0, zi = 0, y2 = 0;
	for (int i = 0; i < Points3ds.size(); i++)
	{
		x2 += (double)Points3ds[i].x * (double)Points3ds[i].x;
		y2 += (double)Points3ds[i].y * (double)Points3ds[i].y;
		xiyi += (double)Points3ds[i].x * (double)Points3ds[i].y;
		xi += (double)Points3ds[i].x;
		yi += (double)Points3ds[i].y;
		zixi += (double)Points3ds[i].z * (double)Points3ds[i].x;
		ziyi += (double)Points3ds[i].z * (double)Points3ds[i].y;
		zi += (double)Points3ds[i].z;
	}
	A.at<double>(0, 0) = x2;
	A.at<double>(1, 0) = xiyi;
	A.at<double>(2, 0) = xi;
	A.at<double>(0, 1) = xiyi;
	A.at<double>(1, 1) = y2;
	A.at<double>(2, 1) = yi;
	A.at<double>(0, 2) = xi;
	A.at<double>(1, 2) = yi;
	A.at<double>(2, 2) = Points3ds.size();
	B.at<double>(0, 0) = zixi;
	B.at<double>(1, 0) = ziyi;
	B.at<double>(2, 0) = zi;
	//计算平面系数
	X = A.inv() * B;
	//Ax+by+cz=D
	this->C = 1;
	this->A = X.at<double>(0, 0);
	this->B = X.at<double>(1, 0);
	this->D = X.at<double>(2, 0);
	/*参数矩阵
	[	-0.02887032035488244;
		-1.46513614437962;
		25.03915056354312
	]
	//  A -0.0162722 B -0.825857   C -0.563645   D -14.1135
	//两种拟合方法计算出来相似，成比例
	*/
	return;
}

/// <summary>
/// 加载无激光的标定板，计算出外参
/// </summary>
/// <param name="path">图片路径</param>
void LaserPlane::LoadBoard(vector<cv::Mat> BoardnoLaser, CalibrateCamera* camera,CalibrateBoard* caliboard)
{
	rvecsMat.resize(BoardnoLaser.size());
	tvecsMat.resize(BoardnoLaser.size());
	std::vector<cv::Point2f> corner;
	//读取每幅图片的角点信息
	for (vector<cv::Mat>::iterator it = BoardnoLaser.begin(); it != BoardnoLaser.end(); it++)
	{
		//Mat caltab_plane_board = imread(
		//	*it,
		//	CV_LOAD_IMAGE_GRAYSCALE
		//);
		cv::Mat caltab_plane_board = *it;
		bool isFind_20 = findCirclesGrid(
			caltab_plane_board,
			cv::Size(7, 7),
			corner
		);
		imagePoint.push_back(corner);
		corner.clear();
	}
	//计算两个视图的外参数 旋转向量和平移向量
	for (int n = 0; n < BoardnoLaser.size(); n++)
	{
		//cout << "计算第" << n << "幅图片" << endl;
		solvePnP(
			caliboard->obj[n],
			imagePoint[n],
			camera->GetCameraMatrix(),
			camera->GetDistCoeff(),
			rvecsMat[n],
			tvecsMat[n],
			false,
			cv::SOLVEPNP_DLS
		);
	}
}

/// <summary>
/// 加载激光线上的点，并转化到基准坐标系下，为拟合平面做准备
/// </summary>
/// <param name="path">图片路径</param>
void LaserPlane::LoadLaser(vector<cv::Mat> BoardLaser, CalibrateCamera* camera)
{
	//对应的旋转矩阵
	vector<cv::Mat>::iterator it1 = rvecsMat.begin();
	//对应的位移矩阵
	vector<cv::Mat>::iterator it2 = tvecsMat.begin();
	//基准
	cv::Mat rotationMatrix2;//3*3
	Rodrigues(camera->GetBaseRvecMat(), rotationMatrix2);
	for (vector<cv::Mat>::iterator it0 = BoardLaser.begin();
		it0 != BoardLaser.end();
		it0++,it1++,it2++)
	{
		std::vector<cv::Point3f> Points3d;
		cv::Point3f temp;
		//注意要看是否读取成功，不成功rod_lightline为空
		//Mat rod_lightline = imread(*it0, CV_LOAD_IMAGE_GRAYSCALE);
		cv::Mat rod_lightline = *it0;
		//这里可以改成步长和种子点搜索法
		threshold(rod_lightline, rod_lightline, 80, 255, cv::THRESH_BINARY);
		for (size_t i = 0; i < rod_lightline.rows; i++)
		{
			int sum = 0; int num = 0; size_t j = 0;
			for (j = 0; j < rod_lightline.cols; j++)
			{
				if (rod_lightline.at<uchar>(i, j) == 255)
				{
					sum += j;
					num++;
				}
			}
			if (num == 0)
				continue;
			//一张图片对应一个旋转向量和一个位移向量 
			//rvecMat和tvecsMat对应22张图片的旋转向量和位移向量
			//将像素坐标转换为世界坐标，因为激光在标定板上，所以世界坐标的Z可以设为0，这个在计算s的时候会用到
			//输入了像素坐标
			temp = camera->getWorldPoints(cv::Point2f(1.0 * sum / num, i), *it1,*it2);
			//到这里计算出的是激光条纹在标定板上的世界坐标，Z为0
			cv::Mat Point3d_mat = (cv::Mat_<double>(3, 1) << double(temp.x), double(temp.y), double(temp.z));
			//要转换的
			cv::Mat rotationMatrix1;//3*3
			Rodrigues(*it1, rotationMatrix1);
			//将两个不同的世界坐标转换到同一个基准下
			//s* Pc = M(RPo + T)
			//Pc=R(Po-T)
			//rotationMatrix1 * (Point3d_mat - *it2)计算出了世界坐标对应的相机坐标
			//Po=R-1*Pc+T
			//计算出了在基准下的世界坐标
			cv::Mat Point3d_toBase_mat = rotationMatrix2.inv() * rotationMatrix1 * (Point3d_mat - *it2) + camera->GetBaseTvecMat();
			//
			//cout << "基准Z：" << Point3d_toBase_mat.at<double>(2, 0) << endl;
			this->Points3ds.push_back(
				cv::Point3f(
					Point3d_toBase_mat.at<double>(0, 0),
					Point3d_toBase_mat.at<double>(1, 0),
					Point3d_toBase_mat.at<double>(2, 0)
				)
			);
		}
	}
}



vector<cv::Mat> LaserPlane::GetRVecsMat()
{
	return rvecsMat;
}
vector<cv::Mat> LaserPlane::GetTVecsMat()
{
	return tvecsMat;
}
double LaserPlane::Get_A()
{
	return this->A;
}

double LaserPlane::Get_B()
{
	return this->B;
}

double LaserPlane::Get_C()
{
	return this->C;
}

double LaserPlane::Get_D()
{
	return this->D;
}

void step::LoadTrackImage(vector<cv::Mat> TrackImg)
{
	std::vector<cv::Point2f> corner;
	vector<cv::Mat>::iterator it1 = rvecsMat.begin();
	vector<cv::Mat>::iterator it2 = tvecsMat.begin();
	for (vector<cv::Mat>::iterator it = TrackImg.begin(); it != TrackImg.end(); it++,it1++,it2++)
	{
		//cvDestroyWindow("image1");
		//Mat caltab_at_position = imread(
		//	*it,
		//	CV_LOAD_IMAGE_GRAYSCALE
		//);
		cv::Mat caltab_at_position = *it;
		bool isFind = findCirclesGrid(
			caltab_at_position,
			cv::Size(7, 7),
			corner
		);
		cornerSubPix(
			caltab_at_position,
			corner,
			cv::Size(11, 11),
			cv::Size(-1, -1),
			cv::TermCriteria(
				CV_TERMCRIT_EPS | CV_TERMCRIT_ITER,
				30,
				0.1
			)
		);

		drawChessboardCorners(
			caltab_at_position,
			cv::Size(7, 7),
			corner,
			isFind
		);
		solvePnP(caliboard->obj[0], corner, this->camera->GetCameraMatrix(), this->camera->GetDistCoeff(), *it1, *it2, false, cv::SOLVEPNP_DLS);
	}
}

void step::CaculateStep()
{
	//使用原点坐标计算位移
	cv::Mat Point3d_mat = (cv::Mat_<double>(3, 1) << 0.0, 0.0, 0.0);
	cv::Mat rotationMatrix1;//3*3
	Rodrigues(rvecsMat[0], rotationMatrix1);
	cv::Mat rotationMatrix2;//3*3
	Rodrigues(rvecsMat[1], rotationMatrix2);
	cv::Mat rotationMatrixBase;//3*3
	Rodrigues(this->camera->GetBaseRvecMat(), rotationMatrixBase);//基准
	//cout << rotationMatrixBase << endl;
	cv::Mat Point3d_1toBase_mat = rotationMatrixBase.inv() * rotationMatrix1 * (Point3d_mat - tvecsMat[0]) + this->camera->GetBaseTvecMat();
	cv::Mat Point3d_2toBase_mat = rotationMatrixBase.inv() * rotationMatrix2 * (Point3d_mat - tvecsMat[1]) + this->camera->GetBaseTvecMat();
	cv::Mat move_steps = Point3d_2toBase_mat - Point3d_1toBase_mat;//1-20移动距离
	//cout << move_steps << endl;
	//步长确定
	this->move_step = move_steps / steps_between;//单步移动距离
}

cv::Mat step::GetStep()
{
	return move_step;
}

step::step(CalibrateBoard *caliboard,CalibrateCamera *camera, int steps_between)
{
	this->steps_between = steps_between;
	this->caliboard = caliboard;
	this->camera = camera;
	this->rvecsMat.resize(2);
	this->tvecsMat.resize(2);
}
