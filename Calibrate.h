#ifndef CALIBRATE_H
#define CALIBRATE_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
class CalibrateBoard
{
private:
	//计算世界坐标
	void calRealPoint(
		std::vector<std::vector<cv::Point3f>>& obj,
		int boardwidth,
		int boardheight,
		int imgNumber,
		float squaresize
	);
	//标定板参数
	int BoardNums;
	int circle_width;
	int circle_height;
	float squaresize;
public:
	int Get_CircleWidth();
	int Get_CircleHeight();
	float Get_SquareSize();
	//保存标定板的世界坐标
	std::vector<std::vector<cv::Point3f>> obj;
	CalibrateBoard(int nums,int circle_width,int circle_height,float squaresize);
};

class CalibrateCamera {
private:
	//保存标定时用的像素坐标
	std::vector<std::vector<cv::Point2f>> imagePoint;
	//保存标定使用的世界坐标
	std::vector<std::vector<cv::Point3f>> objRealPoint;
	//标定
	cv::Size imageSize;
	//内参矩阵、畸变矩阵
	cv::Mat cameraMatrix, distCoeff;
	//标定旋转向量
	vector<cv::Mat> rvecsMat;
	//标定位移向量
	vector<cv::Mat> tvecsMat;
	//标定图片数量
	int ImageNum;
	//所有标定图像误差总和
	double total_err;
	//每幅图像的平均误差
	double *Err_All;
	//拼接基准的旋转位移向量
	cv::Mat Base_RVecsMat;
	cv::Mat Base_TVecsMat;

public:
	//加载标定图片
	void LoadCalibImage(vector<cv::Mat> img);
	//通过旋转向量和
	cv::Point3f getWorldPoints(const cv::Point2f& inPoints, cv::Mat& rvec, cv::Mat& tvec);
	//畸变矫正（不保存原图像）
	void adjustImage(cv::Mat& Image);
	//标定,并计算误差
	bool calibrate(
		CalibrateBoard *caliboard
	);
	//计算基准参数
	void BaseCaculate(cv::Mat rgbImage, CalibrateBoard* caliboard);

	//Get
	cv::Mat GetCameraMatrix();
	cv::Mat GetDistCoeff();
	double GetAverage_err();
	int GetImageNum();
	double* GetErr_ALL();
	cv::Mat GetBaseRvecMat();
	cv::Mat GetBaseTvecMat();
};

class LaserPlane {
public:
	//光平面参数
	void CaculateLaserPlane();
	void LoadBoard(vector<cv::Mat> BoardLaser,CalibrateCamera *camera, CalibrateBoard* caliboard);
	void LoadLaser(vector<cv::Mat> BoardLaser, CalibrateCamera* camera);
	//get
	vector<cv::Mat>	GetRVecsMat();
	vector<cv::Mat>	GetTVecsMat();
	double Get_A();
	double Get_B();
	double Get_C();
	double Get_D();
private:
	//保存读取的标定像素点
	std::vector<std::vector<cv::Point2f>> imagePoint;
	//保存计算的旋转向量和位移向量，用于之后的向基准坐标系转换
	vector<cv::Mat> rvecsMat;
	vector<cv::Mat> tvecsMat;
	//保存所有转化到基准的点坐标
	std::vector<cv::Point3f> Points3ds;

	double A;
	double B;
	double C;
	double D;
};

class step {
private:
	cv::Mat move_step;
	vector<cv::Mat> rvecsMat;
	vector<cv::Mat> tvecsMat;
	CalibrateCamera* camera;
	CalibrateBoard* caliboard;
	int steps_between;
public:
	void LoadTrackImage(vector<cv::Mat> TrackImg);
	step(CalibrateBoard *caliboard,CalibrateCamera *camera,int steps_between);
	void CaculateStep();
	cv::Mat GetStep();

};
#endif