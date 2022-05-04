#ifndef CLOUDPROCESS_H
#define CLOUDPROCESS_H
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
//统计滤波器头文件
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

    //计算两个点之间的向量
    std::vector<double> PointK(pcl::PointXYZRGB A, pcl::PointXYZRGB B);
    //计算两个点之间的距离
    double PointDistance(pcl::PointXYZRGB A, pcl::PointXYZRGB B);
    //两个向量点乘
    inline double dotMul(std::vector<double> a, std::vector<double> b);
    //求向量的模
    inline double vNorm(std::vector<double> a);
};
#endif