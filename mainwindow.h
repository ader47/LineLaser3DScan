#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
//#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"
#include <QDebug>

#include <QContextMenuEvent>  //用于产生右键事件
#include <qmessagebox.h>
#include <vector>
#include <QFileDialog>
#include <QPushButton>
#include <windows.h>


// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include <pcl/filters/statistical_outlier_removal.h>   //统计滤波器头文件
#include <pcl/filters/radius_outlier_removal.h>


// Visualization Toolkit (VTK)
#include <vtkRenderWindow.h>
#include <vtkRenderWindow.h>
#include <vtkPNGReader.h>
#include <vtkImageData.h>
#include <vtkLogoRepresentation.h>
#include <vtkLogoWidget.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkScalarBarWidget.h>
#include <vtkScalarBarActor.h>
#include <vtkScalarBarRepresentation.h>
#include <vtkColorTransferFunction.h>

#include <ImageProcess.h>
#include <MyMatQuery.h>
#include <Calibrate.h>
#include <QListWidget>

//
#include "strmif.h"
#include <initguid.h>
#include<vector>
#include<string>
#pragma comment(lib, "setupapi.lib")

#define VI_MAX_CAMERAS 20
DEFINE_GUID(CLSID_SystemDeviceEnum, 0x62be5d10, 0x60eb, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(CLSID_VideoInputDeviceCategory, 0x860bb310, 0x5d01, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);
DEFINE_GUID(IID_ICreateDevEnum, 0x29840822, 0x5b84, 0x11d0, 0xbd, 0x3b, 0x00, 0xa0, 0xc9, 0x11, 0xce, 0x86);

#include "Threads.h"

enum GetLineMethods {Average,Steger};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //相机标定的图片路径，后面可以改成mat类型的
    std::vector<cv::Mat> Camera_Calib;
    //拼接基准的图片路径
    cv::Mat Base;
    //没有激光的标定板的图片路径，用于计算光平面
    std::vector<cv::Mat> Plane_Board_noLaser;
    //激光的标定板，用于计算光平面
    std::vector<cv::Mat> Plane_Laser;
    //步长计算的图片路径
    std::vector<cv::Mat> Step_Calculate;
    //步长计算的图片路径
    std::vector<cv::Mat> Scan_Laser;
    //PCL
    pcl::visualization::PCLVisualizer::Ptr viewer;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_filtered;
    //激光三角法
    //相机
    CalibrateCamera* camera;
    //激光平面
    LaserPlane* ALaserPlane;
    //步长
    step* Astep;
    //标定标志
    bool isCameraCalib;
    bool isPlaneCalib;
    bool isStepCalib;
    bool isLaserImg;
    bool isBaseCalib;
    bool isCalibed;
    //点云显示
    unsigned int red, green, blue,size;

    //相机相关
    const std::string winName = "camera";
    CameraDisplay* CameraDisp;
    QTimer* tim;
    float fps;
    vector<string> CameraName;//存储摄像头名称
    int listDevices(vector<string>& list);

    //暂时没有到
    GetLineMethods getlinemethod;

    //右键菜单
    QMenu* popMenu_In_ListWidget_;
    QAction* action_Delete_In_ListWidget_;
    QAction* action_Clear_In_ListWidget_;
    QListWidget* currentListWidget;

private slots:
    void on_BN_Select_Clib_Picture_clicked();

    void on_BN_Select_Base_Picture_clicked();

    void on_BN_Select_Board_noLaser_clicked();

    void on_BN_Select_Board_Laser_clicked();

    void on_BN_Select_Step_Pic_clicked();

    void on_BN_Select_LaserLine_clicked();

    void on_pushButton_Caculate_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clearClib_clicked();

    void on_pushButton_cloud_clear_clicked();

    void on_pushButton_flashcamera_clicked();

    void on_pushButton_camerastart_clicked();

    void on_pushButton_camerapause_clicked();

    void on_pushButton_cameracontinue_clicked();

    void on_pushButton_camerastop_clicked();

    void RGBsliderReleased();

    void pSliderValueChanged(int value);

    void redSliderValueChanged(int value);

    void greenSliderValueChanged(int value);

    void blueSliderValueChanged(int value);

    void onCustomContextMenuRequested(QPoint pos);

    void onActionDelete();

    void onActionClear();

    void setEven(int value);

    void onTimeOut();
};
#endif // MAINWINDOW_H
