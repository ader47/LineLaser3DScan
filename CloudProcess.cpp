#include "CloudProcess.h"

CloudProcessTool::CloudProcessTool()
{

}

CloudProcessTool::~CloudProcessTool()
{
}

void CloudProcessTool::cutCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, float distance)
{
    int index1 = 0, index2 = 1;
    pcl::PointIndices::Ptr inliers(new pcl::PointIndices());
    
    while (index2 < cloud->size())
    {
        double RealDis = PointDistance(cloud->points[index1], cloud->points[index2]);
        //可以去除一次离群点，也可以通过向量夹角再次判断
        if (RealDis < distance || RealDis > 3)
            inliers->indices.push_back(index2++);
        else
            index1 = index2++;
    }
    cutCloud(cloud,inliers); 
}

void CloudProcessTool::cutCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr& cloud, pcl::PointIndices::Ptr inliers)
{
    pcl::ExtractIndices<pcl::PointXYZRGB> extract;
    extract.setInputCloud(cloud);
    extract.setIndices(inliers);
    extract.setNegative(true);
    extract.filter(*cloud);
}

std::vector<double> CloudProcessTool::PointK(pcl::PointXYZRGB A, pcl::PointXYZRGB B)
{
    double d2 = pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2);
    double dx = A.x - B.x;
    double dy = A.y - B.y;
    double dz = A.z - B.z;
    std::vector<double> res;
    res.push_back(dx / d2);
    res.push_back(dy / d2);
    res.push_back(dz / d2);
    return res;
}

double CloudProcessTool::PointDistance(pcl::PointXYZRGB A, pcl::PointXYZRGB B)
{
    double d2 = pow(A.x - B.x, 2) + pow(A.y - B.y, 2) + pow(A.z - B.z, 2);
    double distance = sqrt(d2);
    return distance;
}

inline double CloudProcessTool::dotMul(std::vector<double> a, std::vector<double> b)
{
    if (a.size() != b.size()) return 99999;
    double res = 0;
    for (int i = 0; i < a.size(); i++)
        res += a[i] * b[i];
    return res;
}

inline double CloudProcessTool::vNorm(std::vector<double> a)
{
    double res = 0;
    for (int i = 0; i < a.size(); i++)
        res += pow(a[i], 2);
    return sqrt(res);
}
