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
/// Բ�α궨�嶨��
/// </summary>
/// <param name="nums">�궨������</param>
/// <param name="circle_width">���ϵ�Բ����Ŀ</param>
/// <param name="circle_height">���ϵ�Բ����Ŀ</param>
/// <param name="squaresize">Բ�ľ�</param>
CalibrateBoard::CalibrateBoard(int nums,int circle_width, int circle_height, float squaresize)
{
	
	//��ʼ������
	this->circle_height = circle_height;
	this->circle_width = circle_width;
	this->squaresize = squaresize;
	this->BoardNums = nums;
	//����ñ궨������������б�
	//�Ƿ���Ƴɶ�ά��������
	calRealPoint(obj,circle_width,circle_height, nums,squaresize);
}

void CalibrateBoard::calRealPoint(std::vector<std::vector<cv::Point3f>>& obj, int boardwidth, int boardheight, int imgNumber, float squaresize)
{
	//	Mat imgpoint(boardheight, boardwidth, CV_32FC3,Scalar(0,0,0));
	std::vector<cv::Point3f> imgpoint;
	for (int rowIndex = 0; rowIndex < boardheight; rowIndex++)
		//�ӵ�һ�е�һ�еĵ㿪ʼ����ȡ���ǵ���������
	{
		for (int colIndex = 0; colIndex < boardwidth; colIndex++)
		{
			//{��������*Բ�ľ�-��������ӿ�ȣ�����������*Բ�ľ�-��������Ӹ߶ȣ�
			//�õ���������ڰ������ĵ���������
			//����궨�����������ZΪ0��ԭ��Ϊ���Ͻ�
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
		//����������㴫��ȥ
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
	//�õ��궨ͼƬ��������ʵҲ����û���������
	this->ImageNum = this->rvecsMat.size();
	//��ʼ���������
	this->Err_All = (double*)malloc(this->ImageNum *sizeof(double));
	//����б�
	vector<cv::Point2f> image_points2;
	double err;
	for (int i = 0; i < this->ImageNum; i++)
	{
		vector<cv::Point3f> tempPointSet = caliboard->obj[i];
		/* ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ�� */
		projectPoints(tempPointSet, this->rvecsMat[i], this->tvecsMat[i], this->cameraMatrix, this->distCoeff, image_points2);
		/* �����µ�ͶӰ��;ɵ�ͶӰ��֮������*/
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
	//�궨ʧ���б𣿣���������������������������������
	//�ǵ�д
	return true;
}



void CalibrateCamera::LoadCalibImage(vector<cv::Mat> img)
{
	cv::Mat rgbImage, grayImage;
	//�ݴ�ÿ��ͼƬ�Ľ�������
	std::vector<cv::Point2f> corner;
	for (vector<cv::Mat>::iterator it = img.begin(); it != img.end(); it++)
	{
		//rgbImage = cv::imread(*it, CV_LOAD_IMAGE_COLOR);
		rgbImage = *it;
		imageSize = rgbImage.size();
		cv::cvtColor(rgbImage, grayImage, CV_BGR2GRAY);
		bool isFind;
		//�Գ�Բ�ξ���궨��
		isFind = findCirclesGrid(grayImage, cv::Size(7, 7), corner, cv::CALIB_CB_SYMMETRIC_GRID);
		if (isFind)
		{
			//�����ҵ��Ľ���
			drawChessboardCorners(rgbImage, cv::Size(7, 7), corner, isFind);
			//���ҵ��Ľ����������
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
	//�����ڱ궨��ƽ���ϣ��궨��ƽ�����������ZΪ0������������
	double zConst = 0;
	double s;
	cv::Mat imagePoint = (cv::Mat_<double>(3, 1) << double(inPoints.x), double(inPoints.y), 1);
	//�����������S
	cv::Mat tempMat, tempMat2;
	//R-1*M-1*uvPoint*s=[X,Y,Zc]+R-1*t
	//R-1*M-1*uvPoint*
	//����Z=0������s�Ĳ��������ﲢ����Ϊ�˵ó�Z��ֵ
	//ʹ�õ�������������s
	tempMat = rotationMatrix.inv() * this->cameraMatrix.inv() * imagePoint;
	//[X,Y,Zc]+R-1*t
	tempMat2 = rotationMatrix.inv() * tvec;
	s = zConst + tempMat2.at<double>(2, 0);
	s /= tempMat.at<double>(2, 0);
	//������������
	//s*Pc=M(RPo+T)-->Po=(R-1)[s*(M-1)Pc-T]
	//Mat wcPoint = rotationMatrix.inv() * (s * this->cameraMatrix.inv() * imagePoint - tvec);
	//����x y������

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
	//C++������ɾֲ������Զ����ղ���Ҫ�ͷ�
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
/// �����׼����
/// </summary>
/// <param name="ImagePath">��׼�궨��ͼƬ·��</param>
/// <param name="caliboard">�궨�������������ȡ��������</param>
void CalibrateCamera::BaseCaculate(cv::Mat rgbImage, CalibrateBoard *caliboard)
{
	//���Բ�α궨��

	cv::Mat grayImage;
	//cout << "��ʼ�����׼" << endl;
	std::vector<cv::Point2f> corner;
	//rgbImage = cv::imread(ImagePath, CV_LOAD_IMAGE_COLOR);
	cv::cvtColor(rgbImage, grayImage, CV_BGR2GRAY);
	bool isFind;
	//�Գ�Բ�ξ���궨�壬���ԳƵĸ��ã�
	isFind = findCirclesGrid(grayImage, cv::Size(7, 7), corner, cv::CALIB_CB_SYMMETRIC_GRID);
	if (isFind)
	{
		//�����ҵ��Ľ���
		drawChessboardCorners(rgbImage, cv::Size(7, 7), corner, isFind);
		//������ͼ������� ��ת������ƽ������
		solvePnP(caliboard->obj[0], corner, cameraMatrix, distCoeff, this->Base_RVecsMat, this->Base_TVecsMat, false, cv::SOLVEPNP_DLS);
		imshow("BaseCaculate", rgbImage);
		cv::waitKey(1);
	}
	cv::destroyWindow("BaseCaculate");
	//ʧ�ܵ������������
}

double CalibrateCamera::GetAverage_err()
{
	return this->total_err / ImageNum;
}

void LaserPlane::CaculateLaserPlane()
{
	//��С���˷����ƽ��
	//��ȡcv::Mat������ϵ������Ϊx�ᣬ����Ϊy�ᣬ��cvPoint�����෴
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
	//����ƽ��ϵ��
	X = A.inv() * B;
	//Ax+by+cz=D
	this->C = 1;
	this->A = X.at<double>(0, 0);
	this->B = X.at<double>(1, 0);
	this->D = X.at<double>(2, 0);
	/*��������
	[	-0.02887032035488244;
		-1.46513614437962;
		25.03915056354312
	]
	//  A -0.0162722 B -0.825857   C -0.563645   D -14.1135
	//������Ϸ�������������ƣ��ɱ���
	*/
	return;
}

//void LaserPlane::CaculateLaserPlane()
//{
//	CvMat* points_mat = cvCreateMat(this->Points3ds.size(), 3, CV_32FC1);//���������洢��Ҫ��ϵ�ľ��� 
//	for (int i = 0; i < this->Points3ds.size(); ++i)
//	{
//		//points_data.fl[]���д洢����Ҫ��ϵĵ�
//		points_mat->data.fl[i * 3 + 0] = this->Points3ds[i].x;//�����ֵ���г�ʼ��   X������ֵ
//		points_mat->data.fl[i * 3 + 1] = this->Points3ds[i].y;//  Y������ֵ
//		points_mat->data.fl[i * 3 + 2] = this->Points3ds[i].z;//  Z������ֵ</span>
//	}
//	float* plane = (float*)malloc(sizeof(float) * 4);
//	// Estimate geometric centroid.
//	int nrows = points_mat->rows;
//	int ncols = points_mat->cols;
//	int type = points_mat->type;
//	//cout << "nrows" << nrows << "ncols" << ncols << "type" << type << endl;
//	//������һ��һ��3�еľ���
//	CvMat* centroid = cvCreateMat(1, ncols, type);
//	//���Ϊ0 [0,0,0]
//	cvSet(centroid, cvScalar(0));
//	//cout << centroid->data.fl << endl;
//	//������е��ƽ��x��y,z
//	for (int c = 0; c < ncols; c++) {
//		for (int r = 0; r < nrows; r++)
//		{
//			//���е�x��y,z���
//			centroid->data.fl[c] += points_mat->data.fl[ncols * r + c];
//		}
//		//���Ե����Ŀ���õ�ƽ��ֵ
//		centroid->data.fl[c] /= nrows;
//	}
//	// Subtract geometric centroid from each point.
//	//����һ�������У�3�еľ��󣬴洢����ƽ��λ�õ�ƫ�ƣ�ʵ��-ƽ��λ��
//	CvMat* points2 = cvCreateMat(nrows, ncols, type);
//	for (int r = 0; r < nrows; r++)
//		for (int c = 0; c < ncols; c++)
//			points2->data.fl[ncols * r + c] = points_mat->data.fl[ncols * r + c] - centroid->data.fl[c];
//	// Evaluate SVD of covariance matrix.
//	//����Э��������SVD
//	CvMat* A_mat = cvCreateMat(ncols, ncols, type);
//	CvMat* W_mat = cvCreateMat(ncols, ncols, type);
//	CvMat* V_mat = cvCreateMat(ncols, ncols, type);
//	//Э���������㷽��
//	//covMatrix=X(t)*X/(m-1)
//	//cvGEMM�������˷�����������������˼��
//	//A_mat=1*points2.inv()*points_mat
//	//
//	cvGEMM(points2, points_mat, 1, NULL, 0, A_mat, CV_GEMM_A_T);
//	cvSVD(A_mat, W_mat, NULL, V_mat, CV_SVD_V_T);
//	// Assign plane coefficients by singular vector corresponding to smallest singular value.
//	plane[ncols] = 0;
//	for (int c = 0; c < ncols; c++) {
//		plane[c] = V_mat->data.fl[ncols * (ncols - 1) + c];
//		plane[ncols] += plane[c] * centroid->data.fl[c];
//	}
//	this->A = plane[0];
//	this->B = plane[1];
//	this->C = plane[2];
//	this->D = plane[3];
//	//cout << "A" << A << "B" << B << "C" << C << "D" << D << endl;
//
//	// Release allocated resources.
//	cvReleaseMat(&centroid);
//	cvReleaseMat(&points2);
//	cvReleaseMat(&A_mat);
//	cvReleaseMat(&W_mat);
//	cvReleaseMat(&V_mat);
//}

/// <summary>
/// �����޼���ı궨�壬��������
/// </summary>
/// <param name="path">ͼƬ·��</param>
void LaserPlane::LoadBoard(vector<cv::Mat> BoardnoLaser, CalibrateCamera* camera,CalibrateBoard* caliboard)
{
	rvecsMat.resize(BoardnoLaser.size());
	tvecsMat.resize(BoardnoLaser.size());
	std::vector<cv::Point2f> corner;
	//��ȡÿ��ͼƬ�Ľǵ���Ϣ
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
	//����������ͼ������� ��ת������ƽ������
	for (int n = 0; n < BoardnoLaser.size(); n++)
	{
		//cout << "�����" << n << "��ͼƬ" << endl;
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
/// ���ؼ������ϵĵ㣬��ת������׼����ϵ�£�Ϊ���ƽ����׼��
/// </summary>
/// <param name="path">ͼƬ·��</param>
void LaserPlane::LoadLaser(vector<cv::Mat> BoardLaser, CalibrateCamera* camera)
{
	//��Ӧ����ת����
	vector<cv::Mat>::iterator it1 = rvecsMat.begin();
	//��Ӧ��λ�ƾ���
	vector<cv::Mat>::iterator it2 = tvecsMat.begin();
	//��׼
	cv::Mat rotationMatrix2;//3*3
	Rodrigues(camera->GetBaseRvecMat(), rotationMatrix2);
	for (vector<cv::Mat>::iterator it0 = BoardLaser.begin();
		it0 != BoardLaser.end();
		it0++,it1++,it2++)
	{
		std::vector<cv::Point3f> Points3d;
		cv::Point3f temp;
		//ע��Ҫ���Ƿ��ȡ�ɹ������ɹ�rod_lightlineΪ��
		//Mat rod_lightline = imread(*it0, CV_LOAD_IMAGE_GRAYSCALE);
		cv::Mat rod_lightline = *it0;
		//������Ըĳɲ��������ӵ�������
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
			//һ��ͼƬ��Ӧһ����ת������һ��λ������ 
			//rvecMat��tvecsMat��Ӧ22��ͼƬ����ת������λ������
			//����������ת��Ϊ�������꣬��Ϊ�����ڱ궨���ϣ��������������Z������Ϊ0������ڼ���s��ʱ����õ�
			//��������������
			temp = camera->getWorldPoints(cv::Point2f(1.0 * sum / num, i), *it1,*it2);
			//�������������Ǽ��������ڱ궨���ϵ��������꣬ZΪ0
			cv::Mat Point3d_mat = (cv::Mat_<double>(3, 1) << double(temp.x), double(temp.y), double(temp.z));
			//Ҫת����
			cv::Mat rotationMatrix1;//3*3
			Rodrigues(*it1, rotationMatrix1);
			//��������ͬ����������ת����ͬһ����׼��
			//s* Pc = M(RPo + T)
			//Pc=R(Po-T)
			//rotationMatrix1 * (Point3d_mat - *it2)����������������Ӧ���������
			//Po=R-1*Pc+T
			//��������ڻ�׼�µ���������
			//Mat Point3d_toBase_mat = rotationMatrix2.inv() * rotationMatrix1 * (Point3d_mat - *it2) + camera->GetBaseTvecMat();
			cv::Mat Point3d_toBase_mat = rotationMatrix2.inv() * rotationMatrix1 * (Point3d_mat - *it2) + camera->GetBaseTvecMat();
			//
			//cout << "��׼Z��" << Point3d_toBase_mat.at<double>(2, 0) << endl;
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
	//ʹ��ԭ���������λ��
	cv::Mat Point3d_mat = (cv::Mat_<double>(3, 1) << 0.0, 0.0, 0.0);
	cv::Mat rotationMatrix1;//3*3
	Rodrigues(rvecsMat[0], rotationMatrix1);
	cv::Mat rotationMatrix2;//3*3
	Rodrigues(rvecsMat[1], rotationMatrix2);
	cv::Mat rotationMatrixBase;//3*3
	Rodrigues(this->camera->GetBaseRvecMat(), rotationMatrixBase);//��׼
	//cout << rotationMatrixBase << endl;
	cv::Mat Point3d_1toBase_mat = rotationMatrixBase.inv() * rotationMatrix1 * (Point3d_mat - tvecsMat[0]) + this->camera->GetBaseTvecMat();
	cv::Mat Point3d_2toBase_mat = rotationMatrixBase.inv() * rotationMatrix2 * (Point3d_mat - tvecsMat[1]) + this->camera->GetBaseTvecMat();
	cv::Mat move_steps = Point3d_2toBase_mat - Point3d_1toBase_mat;//1-20�ƶ�����
	//cout << move_steps << endl;
	//����ȷ��
	this->move_step = move_steps / steps_between;//�����ƶ�����
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
