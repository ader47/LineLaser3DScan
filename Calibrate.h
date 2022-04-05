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
	//������������
	void calRealPoint(
		std::vector<std::vector<cv::Point3f>>& obj,
		int boardwidth,
		int boardheight,
		int imgNumber,
		float squaresize
	);
	//�궨�����
	int BoardNums;
	int circle_width;
	int circle_height;
	float squaresize;
public:
	int Get_CircleWidth();
	int Get_CircleHeight();
	float Get_SquareSize();
	//����궨�����������
	std::vector<std::vector<cv::Point3f>> obj;
	CalibrateBoard(int nums,int circle_width,int circle_height,float squaresize);
};

class CalibrateCamera {
private:
	//����궨ʱ�õ���������
	std::vector<std::vector<cv::Point2f>> imagePoint;
	//����궨ʹ�õ���������
	std::vector<std::vector<cv::Point3f>> objRealPoint;
	//�궨
	cv::Size imageSize;
	//�ڲξ��󡢻������
	cv::Mat cameraMatrix, distCoeff;
	//�궨��ת����
	vector<cv::Mat> rvecsMat;
	//�궨λ������
	vector<cv::Mat> tvecsMat;
	//�궨ͼƬ����
	int ImageNum;
	//���б궨ͼ������ܺ�
	double total_err;
	//ÿ��ͼ���ƽ�����
	double *Err_All;
	//ƴ�ӻ�׼����תλ������
	cv::Mat Base_RVecsMat;
	cv::Mat Base_TVecsMat;

public:
	//���ر궨ͼƬ
	void LoadCalibImage(vector<cv::Mat> img);
	//ͨ����ת������
	cv::Point3f getWorldPoints(const cv::Point2f& inPoints, cv::Mat& rvec, cv::Mat& tvec);
	//���������������ԭͼ��
	void adjustImage(cv::Mat& Image);
	//�궨,���������
	bool calibrate(
		CalibrateBoard *caliboard
	);
	//�����׼����
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
	//��ƽ�����
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
	//�����ȡ�ı궨���ص�
	std::vector<std::vector<cv::Point2f>> imagePoint;
	//����������ת������λ������������֮������׼����ϵת��
	vector<cv::Mat> rvecsMat;
	vector<cv::Mat> tvecsMat;
	//��������ת������׼�ĵ�����
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