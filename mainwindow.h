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

#include <QContextMenuEvent>  //���ڲ����Ҽ��¼�
#include <qmessagebox.h>
#include <vector>
#include <QFileDialog>
#include <QPushButton>

// Point Cloud Library
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/point_cloud_color_handlers.h>

#include<pcl/filters/statistical_outlier_removal.h>   //ͳ���˲���ͷ�ļ�

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
    //����궨��ͼƬ·����������Ըĳ�mat���͵�
    std::vector<cv::Mat> Camera_Calib;
    //ƴ�ӻ�׼��ͼƬ·��
    cv::Mat Base;
    //û�м���ı궨���ͼƬ·�������ڼ����ƽ��
    std::vector<cv::Mat> Plane_Board_noLaser;
    //����ı궨�壬���ڼ����ƽ��
    std::vector<cv::Mat> Plane_Laser;
    //���������ͼƬ·��
    std::vector<cv::Mat> Step_Calculate;
    //���������ͼƬ·��
    std::vector<cv::Mat> Scan_Laser;
    //PCL
    pcl::visualization::PCLVisualizer::Ptr viewer;
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
    //�������Ƿ�
    //���
    CalibrateCamera* camera;
    //����ƽ��
    LaserPlane* ALaserPlane;
    //����
    step* Astep;
    //�궨��־
    bool isCameraCalib;
    bool isPlaneCalib;
    bool isStepCalib;
    bool isLaserImg;
    bool isBaseCalib;
    bool isCalibed;
    //�ɼ�ͼ��
   // void GraspImage();
    unsigned int red, green, blue,size;
    //��ʱû�е�
    GetLineMethods getlinemethod;
    //�Ҽ��˵�
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

    void RGBsliderReleased();

    void pSliderValueChanged(int value);

    void redSliderValueChanged(int value);

    void greenSliderValueChanged(int value);

    void blueSliderValueChanged(int value);

    void onCustomContextMenuRequested(QPoint pos);

    void onActionDelete();

    void onActionClear();

    void setEven(int value);
};
#endif // MAINWINDOW_H
