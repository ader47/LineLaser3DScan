#ifndef CLOUDPROCESS_H
#define CLOUDPROCESS_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//ͳ���˲���ͷ�ļ�
#include <pcl/filters/statistical_outlier_removal.h>   
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/fast_bilateral.h>
#include <pcl/filters/extract_indices.h>

#include <vector>

class CloudProcessTool
{
private:


public:
	CloudProcessTool();
	~CloudProcessTool();

	void cutCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, float distance);
	
	void cutCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, pcl::PointIndices::Ptr inliers);

    //����������֮�������
    std::vector<double> PointK(pcl::PointXYZRGB A, pcl::PointXYZRGB B);
    //����������֮��ľ���
    double PointDistance(pcl::PointXYZRGB A, pcl::PointXYZRGB B);
    //�����������
    inline double dotMul(std::vector<double> a, std::vector<double> b);
    //��������ģ
    inline double vNorm(std::vector<double> a);
};
#endif