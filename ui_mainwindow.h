/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_3;
    QGroupBox *groupBox_12;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_10;
    QGridLayout *gridLayout_7;
    QWidget *widget;
    QGroupBox *groupBox_13;
    QLabel *label_2;
    QGroupBox *groupBox_9;
    QGroupBox *groupBox_11;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_4;
    QLabel *label_11;
    QPushButton *pushButton_flashcamera;
    QComboBox *comboBox_camera_select;
    QGroupBox *groupBox_14;
    QGroupBox *groupBox_7;
    QGridLayout *gridLayout_8;
    QPushButton *pushButton_camerastart;
    QPushButton *pushButton_camerapause;
    QPushButton *pushButton_camerastop;
    QPushButton *pushButton_cameracontinue;
    QGroupBox *groupBox_8;
    QWidget *tab_2;
    QGridLayout *gridLayout_3;
    QSplitter *splitter;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QPushButton *BN_Select_LaserLine;
    QPushButton *BN_Select_Board_noLaser;
    QPushButton *BN_Select_Board_Laser;
    QPushButton *BN_Select_Clib_Picture;
    QPushButton *BN_Select_Step_Pic;
    QPushButton *BN_Select_Base_Picture;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget_CalibPic;
    QListWidget *listWidget_BasePic;
    QListWidget *listWidget_Board_noLaser;
    QListWidget *listWidget_Board_Laser;
    QListWidget *listWidget_Step_Pic;
    QListWidget *listWidget_LaserLine;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QComboBox *comboBox_Methods;
    QPushButton *pushButton;
    QLabel *label_12;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QLabel *label_8;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox;
    QSpinBox *spinBox_5;
    QLabel *label_7;
    QSpinBox *spinBox_2;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBox_4;
    QLabel *label_6;
    QCheckBox *checkBox_3;
    QSpinBox *spinBox_6;
    QRadioButton *radioButton_X_add;
    QLabel *label;
    QRadioButton *radioButton_Y_add;
    QPushButton *pushButton_Caculate;
    QLabel *label_10;
    QLabel *label_13;
    QSpinBox *spinBox_8;
    QDoubleSpinBox *doubleSpinBox_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_2;
    QVTKWidget *qvtkWidget;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_6;
    QSpinBox *spinBox_green;
    QLabel *Lable_Size;
    QSpinBox *spinBox_blue;
    QLabel *Lable_Blue;
    QLabel *Lable_Red;
    QSlider *horizontalSlider_Red;
    QPushButton *pushButton_2;
    QSlider *horizontalSlider_Green;
    QLabel *Lable_Green;
    QSpinBox *spinBox_size;
    QSlider *horizontalSlider_Size;
    QSlider *horizontalSlider_Blue;
    QSpinBox *spinBox_red;
    QPushButton *pushButton_cloud_clear;
    QWidget *tab_4;
    QTextBrowser *textBrowser_2;
    QLabel *label_9;
    QPushButton *pushButton_clearClib;
    QPushButton *pushButton_save;
    QPushButton *pushButton_load;
    QLabel *label_isCamera;
    QLabel *label_isCalibed;
    QLabel *label_flagCalibed;
    QLabel *label_flagCamera;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1214, 797);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_3 = new QHBoxLayout(tab);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        groupBox_12 = new QGroupBox(tab);
        groupBox_12->setObjectName(QString::fromUtf8("groupBox_12"));
        groupBox_12->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(groupBox_12);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_10 = new QGroupBox(groupBox_12);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setMinimumSize(QSize(640, 360));
        groupBox_10->setMaximumSize(QSize(1920, 1080));
        gridLayout_7 = new QGridLayout(groupBox_10);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        widget = new QWidget(groupBox_10);
        widget->setObjectName(QString::fromUtf8("widget"));

        gridLayout_7->addWidget(widget, 0, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox_10);

        groupBox_13 = new QGroupBox(groupBox_12);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        groupBox_13->setMaximumSize(QSize(16777215, 32));
        groupBox_13->setStyleSheet(QString::fromUtf8("QGroupBox{border:none}"));
        label_2 = new QLabel(groupBox_13);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(0, 0, 281, 20));

        verticalLayout_3->addWidget(groupBox_13);

        groupBox_9 = new QGroupBox(groupBox_12);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setMaximumSize(QSize(16777215, 120));

        verticalLayout_3->addWidget(groupBox_9);


        horizontalLayout_3->addWidget(groupBox_12);

        groupBox_11 = new QGroupBox(tab);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setMaximumSize(QSize(400, 16777215));
        verticalLayout = new QVBoxLayout(groupBox_11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_6 = new QGroupBox(groupBox_11);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setMaximumSize(QSize(16777215, 90));
        gridLayout_4 = new QGridLayout(groupBox_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_11 = new QLabel(groupBox_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_4->addWidget(label_11, 3, 0, 1, 1);

        pushButton_flashcamera = new QPushButton(groupBox_6);
        pushButton_flashcamera->setObjectName(QString::fromUtf8("pushButton_flashcamera"));

        gridLayout_4->addWidget(pushButton_flashcamera, 3, 1, 1, 1);

        comboBox_camera_select = new QComboBox(groupBox_6);
        comboBox_camera_select->setObjectName(QString::fromUtf8("comboBox_camera_select"));

        gridLayout_4->addWidget(comboBox_camera_select, 0, 0, 1, 2);


        verticalLayout->addWidget(groupBox_6);

        groupBox_14 = new QGroupBox(groupBox_11);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));

        verticalLayout->addWidget(groupBox_14);

        groupBox_7 = new QGroupBox(groupBox_11);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setMaximumSize(QSize(16777215, 90));
        gridLayout_8 = new QGridLayout(groupBox_7);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        pushButton_camerastart = new QPushButton(groupBox_7);
        pushButton_camerastart->setObjectName(QString::fromUtf8("pushButton_camerastart"));

        gridLayout_8->addWidget(pushButton_camerastart, 0, 0, 1, 1);

        pushButton_camerapause = new QPushButton(groupBox_7);
        pushButton_camerapause->setObjectName(QString::fromUtf8("pushButton_camerapause"));

        gridLayout_8->addWidget(pushButton_camerapause, 0, 1, 1, 1);

        pushButton_camerastop = new QPushButton(groupBox_7);
        pushButton_camerastop->setObjectName(QString::fromUtf8("pushButton_camerastop"));

        gridLayout_8->addWidget(pushButton_camerastop, 1, 0, 1, 1);

        pushButton_cameracontinue = new QPushButton(groupBox_7);
        pushButton_cameracontinue->setObjectName(QString::fromUtf8("pushButton_cameracontinue"));

        gridLayout_8->addWidget(pushButton_cameracontinue, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(groupBox_11);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));

        verticalLayout->addWidget(groupBox_8);


        horizontalLayout_3->addWidget(groupBox_11);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_3 = new QGridLayout(tab_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        splitter = new QSplitter(tab_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        groupBox_2 = new QGroupBox(splitter);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 50));
        groupBox_2->setMaximumSize(QSize(16777215, 50));
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox{border:none}"));
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        BN_Select_LaserLine = new QPushButton(groupBox_2);
        BN_Select_LaserLine->setObjectName(QString::fromUtf8("BN_Select_LaserLine"));

        gridLayout_5->addWidget(BN_Select_LaserLine, 0, 5, 1, 1);

        BN_Select_Board_noLaser = new QPushButton(groupBox_2);
        BN_Select_Board_noLaser->setObjectName(QString::fromUtf8("BN_Select_Board_noLaser"));

        gridLayout_5->addWidget(BN_Select_Board_noLaser, 0, 2, 1, 1);

        BN_Select_Board_Laser = new QPushButton(groupBox_2);
        BN_Select_Board_Laser->setObjectName(QString::fromUtf8("BN_Select_Board_Laser"));

        gridLayout_5->addWidget(BN_Select_Board_Laser, 0, 3, 1, 1);

        BN_Select_Clib_Picture = new QPushButton(groupBox_2);
        BN_Select_Clib_Picture->setObjectName(QString::fromUtf8("BN_Select_Clib_Picture"));

        gridLayout_5->addWidget(BN_Select_Clib_Picture, 0, 0, 1, 1);

        BN_Select_Step_Pic = new QPushButton(groupBox_2);
        BN_Select_Step_Pic->setObjectName(QString::fromUtf8("BN_Select_Step_Pic"));

        gridLayout_5->addWidget(BN_Select_Step_Pic, 0, 4, 1, 1);

        BN_Select_Base_Picture = new QPushButton(groupBox_2);
        BN_Select_Base_Picture->setObjectName(QString::fromUtf8("BN_Select_Base_Picture"));

        gridLayout_5->addWidget(BN_Select_Base_Picture, 0, 1, 1, 1);

        splitter->addWidget(groupBox_2);
        groupBox = new QGroupBox(splitter);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(16777215, 16777215));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox{border:none}"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget_CalibPic = new QListWidget(groupBox);
        listWidget_CalibPic->setObjectName(QString::fromUtf8("listWidget_CalibPic"));
        listWidget_CalibPic->setContextMenuPolicy(Qt::CustomContextMenu);

        horizontalLayout->addWidget(listWidget_CalibPic);

        listWidget_BasePic = new QListWidget(groupBox);
        listWidget_BasePic->setObjectName(QString::fromUtf8("listWidget_BasePic"));

        horizontalLayout->addWidget(listWidget_BasePic);

        listWidget_Board_noLaser = new QListWidget(groupBox);
        listWidget_Board_noLaser->setObjectName(QString::fromUtf8("listWidget_Board_noLaser"));

        horizontalLayout->addWidget(listWidget_Board_noLaser);

        listWidget_Board_Laser = new QListWidget(groupBox);
        listWidget_Board_Laser->setObjectName(QString::fromUtf8("listWidget_Board_Laser"));

        horizontalLayout->addWidget(listWidget_Board_Laser);

        listWidget_Step_Pic = new QListWidget(groupBox);
        listWidget_Step_Pic->setObjectName(QString::fromUtf8("listWidget_Step_Pic"));

        horizontalLayout->addWidget(listWidget_Step_Pic);

        listWidget_LaserLine = new QListWidget(groupBox);
        listWidget_LaserLine->setObjectName(QString::fromUtf8("listWidget_LaserLine"));

        horizontalLayout->addWidget(listWidget_LaserLine);

        splitter->addWidget(groupBox);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 60));
        groupBox_3->setMaximumSize(QSize(16777215, 60));
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox{border:none}"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        comboBox_Methods = new QComboBox(groupBox_3);
        comboBox_Methods->setObjectName(QString::fromUtf8("comboBox_Methods"));
        comboBox_Methods->setMinimumSize(QSize(0, 20));

        gridLayout_2->addWidget(comboBox_Methods, 0, 3, 1, 2);

        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(pushButton, 0, 7, 1, 1);

        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 0, 0, 1, 1);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(500, 55));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 0, 9, 1, 1);

        spinBox_3 = new QSpinBox(groupBox_5);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

        gridLayout->addWidget(spinBox_3, 1, 4, 1, 1);

        spinBox = new QSpinBox(groupBox_5);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout->addWidget(spinBox, 1, 1, 1, 1);

        spinBox_5 = new QSpinBox(groupBox_5);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));

        gridLayout->addWidget(spinBox_5, 1, 9, 1, 1);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 0, 5, 1, 1);

        spinBox_2 = new QSpinBox(groupBox_5);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

        gridLayout->addWidget(spinBox_2, 1, 2, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

        gridLayout->addWidget(doubleSpinBox, 1, 10, 1, 1);

        label_3 = new QLabel(groupBox_5);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_5);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        spinBox_4 = new QSpinBox(groupBox_5);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));

        gridLayout->addWidget(spinBox_4, 1, 5, 1, 1);

        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 10, 1, 1);

        checkBox_3 = new QCheckBox(groupBox_5);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        gridLayout->addWidget(checkBox_3, 1, 11, 1, 1);


        gridLayout_2->addWidget(groupBox_5, 0, 9, 2, 1);

        spinBox_6 = new QSpinBox(groupBox_3);
        spinBox_6->setObjectName(QString::fromUtf8("spinBox_6"));

        gridLayout_2->addWidget(spinBox_6, 1, 7, 1, 1);

        radioButton_X_add = new QRadioButton(groupBox_3);
        radioButton_X_add->setObjectName(QString::fromUtf8("radioButton_X_add"));

        gridLayout_2->addWidget(radioButton_X_add, 1, 3, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 2, 1, 1);

        radioButton_Y_add = new QRadioButton(groupBox_3);
        radioButton_Y_add->setObjectName(QString::fromUtf8("radioButton_Y_add"));

        gridLayout_2->addWidget(radioButton_Y_add, 1, 4, 1, 1);

        pushButton_Caculate = new QPushButton(groupBox_3);
        pushButton_Caculate->setObjectName(QString::fromUtf8("pushButton_Caculate"));
        pushButton_Caculate->setMinimumSize(QSize(0, 25));

        gridLayout_2->addWidget(pushButton_Caculate, 0, 6, 1, 1);

        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(label_10, 1, 6, 1, 1);

        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 0, 1, 1, 1);

        spinBox_8 = new QSpinBox(groupBox_3);
        spinBox_8->setObjectName(QString::fromUtf8("spinBox_8"));

        gridLayout_2->addWidget(spinBox_8, 1, 1, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

        gridLayout_2->addWidget(doubleSpinBox_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_3, 1, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_2 = new QVBoxLayout(tab_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        qvtkWidget = new QVTKWidget(tab_3);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        verticalLayout_2->addWidget(qvtkWidget);

        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMaximumSize(QSize(16777215, 67));
        gridLayout_6 = new QGridLayout(groupBox_4);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        spinBox_green = new QSpinBox(groupBox_4);
        spinBox_green->setObjectName(QString::fromUtf8("spinBox_green"));

        gridLayout_6->addWidget(spinBox_green, 1, 2, 1, 1);

        Lable_Size = new QLabel(groupBox_4);
        Lable_Size->setObjectName(QString::fromUtf8("Lable_Size"));

        gridLayout_6->addWidget(Lable_Size, 0, 6, 1, 1);

        spinBox_blue = new QSpinBox(groupBox_4);
        spinBox_blue->setObjectName(QString::fromUtf8("spinBox_blue"));

        gridLayout_6->addWidget(spinBox_blue, 1, 4, 1, 1);

        Lable_Blue = new QLabel(groupBox_4);
        Lable_Blue->setObjectName(QString::fromUtf8("Lable_Blue"));

        gridLayout_6->addWidget(Lable_Blue, 0, 4, 1, 1);

        Lable_Red = new QLabel(groupBox_4);
        Lable_Red->setObjectName(QString::fromUtf8("Lable_Red"));

        gridLayout_6->addWidget(Lable_Red, 0, 0, 1, 1);

        horizontalSlider_Red = new QSlider(groupBox_4);
        horizontalSlider_Red->setObjectName(QString::fromUtf8("horizontalSlider_Red"));
        horizontalSlider_Red->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(horizontalSlider_Red, 0, 1, 2, 1);

        pushButton_2 = new QPushButton(groupBox_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout_6->addWidget(pushButton_2, 0, 8, 2, 1);

        horizontalSlider_Green = new QSlider(groupBox_4);
        horizontalSlider_Green->setObjectName(QString::fromUtf8("horizontalSlider_Green"));
        horizontalSlider_Green->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(horizontalSlider_Green, 0, 3, 2, 1);

        Lable_Green = new QLabel(groupBox_4);
        Lable_Green->setObjectName(QString::fromUtf8("Lable_Green"));

        gridLayout_6->addWidget(Lable_Green, 0, 2, 1, 1);

        spinBox_size = new QSpinBox(groupBox_4);
        spinBox_size->setObjectName(QString::fromUtf8("spinBox_size"));

        gridLayout_6->addWidget(spinBox_size, 1, 6, 1, 1);

        horizontalSlider_Size = new QSlider(groupBox_4);
        horizontalSlider_Size->setObjectName(QString::fromUtf8("horizontalSlider_Size"));
        horizontalSlider_Size->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(horizontalSlider_Size, 0, 7, 2, 1);

        horizontalSlider_Blue = new QSlider(groupBox_4);
        horizontalSlider_Blue->setObjectName(QString::fromUtf8("horizontalSlider_Blue"));
        horizontalSlider_Blue->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(horizontalSlider_Blue, 0, 5, 2, 1);

        spinBox_red = new QSpinBox(groupBox_4);
        spinBox_red->setObjectName(QString::fromUtf8("spinBox_red"));

        gridLayout_6->addWidget(spinBox_red, 1, 0, 1, 1);

        pushButton_cloud_clear = new QPushButton(groupBox_4);
        pushButton_cloud_clear->setObjectName(QString::fromUtf8("pushButton_cloud_clear"));

        gridLayout_6->addWidget(pushButton_cloud_clear, 0, 9, 2, 1);


        verticalLayout_2->addWidget(groupBox_4);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        textBrowser_2 = new QTextBrowser(tab_4);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(30, 130, 361, 321));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(30, 110, 81, 16));
        pushButton_clearClib = new QPushButton(tab_4);
        pushButton_clearClib->setObjectName(QString::fromUtf8("pushButton_clearClib"));
        pushButton_clearClib->setGeometry(QRect(160, 60, 81, 23));
        pushButton_clearClib->setAutoFillBackground(false);
        pushButton_save = new QPushButton(tab_4);
        pushButton_save->setObjectName(QString::fromUtf8("pushButton_save"));
        pushButton_save->setGeometry(QRect(160, 30, 75, 20));
        pushButton_load = new QPushButton(tab_4);
        pushButton_load->setObjectName(QString::fromUtf8("pushButton_load"));
        pushButton_load->setGeometry(QRect(260, 30, 75, 20));
        label_isCamera = new QLabel(tab_4);
        label_isCamera->setObjectName(QString::fromUtf8("label_isCamera"));
        label_isCamera->setGeometry(QRect(10, 30, 61, 16));
        label_isCalibed = new QLabel(tab_4);
        label_isCalibed->setObjectName(QString::fromUtf8("label_isCalibed"));
        label_isCalibed->setGeometry(QRect(30, 60, 31, 16));
        label_flagCalibed = new QLabel(tab_4);
        label_flagCalibed->setObjectName(QString::fromUtf8("label_flagCalibed"));
        label_flagCalibed->setGeometry(QRect(80, 60, 54, 16));
        label_flagCamera = new QLabel(tab_4);
        label_flagCamera->setObjectName(QString::fromUtf8("label_flagCamera"));
        label_flagCamera->setGeometry(QRect(80, 30, 54, 16));
        tabWidget->addTab(tab_4, QString());

        verticalLayout_4->addWidget(tabWidget);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setMaximumSize(QSize(16777215, 50));

        verticalLayout_4->addWidget(textBrowser);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1214, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_12->setTitle(QString());
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\346\230\276\347\244\272", nullptr));
        groupBox_13->setTitle(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\270\247\347\216\207\346\230\276\347\244\272", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "\347\204\212\346\216\245\346\216\247\345\210\266", nullptr));
        groupBox_11->setTitle(QString());
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\351\200\211\346\213\251", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\345\237\272\346\234\254\344\277\241\346\201\257", nullptr));
        pushButton_flashcamera->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260\347\233\270\346\234\272", nullptr));
        groupBox_14->setTitle(QCoreApplication::translate("MainWindow", "\345\257\274\350\275\250\346\216\247\345\210\266", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "\350\247\246\345\217\221\346\216\247\345\210\266", nullptr));
        pushButton_camerastart->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pushButton_camerapause->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        pushButton_camerastop->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        pushButton_cameracontinue->setText(QCoreApplication::translate("MainWindow", "Continue", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "\351\242\204\345\244\204\347\220\206", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Tab 1", nullptr));
        groupBox_2->setTitle(QString());
        BN_Select_LaserLine->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\277\200\345\205\211\347\272\277\346\235\241\357\274\210\345\217\257\351\200\211\357\274\211", nullptr));
        BN_Select_Board_noLaser->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\227\240\346\277\200\345\205\211\346\240\207\345\256\232\346\235\277", nullptr));
        BN_Select_Board_Laser->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\234\211\346\277\200\345\205\211\346\240\207\345\256\232\346\235\277", nullptr));
        BN_Select_Clib_Picture->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\233\270\346\234\272\346\240\207\345\256\232\345\233\276\347\211\207", nullptr));
        BN_Select_Step_Pic->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\255\245\351\225\277\350\256\241\347\256\227\345\233\276\347\211\207", nullptr));
        BN_Select_Base_Picture->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\347\202\271\344\272\221\346\213\274\346\216\245\345\237\272\345\207\206\345\233\276\347\211\207", nullptr));
        groupBox->setTitle(QString());
        groupBox_3->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\351\207\215\345\273\272", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\273\244\346\263\242\345\215\212\345\276\204", nullptr));
        groupBox_5->setTitle(QString());
        label_8->setText(QCoreApplication::translate("MainWindow", "\345\215\267\347\247\257\346\240\270Y\346\240\207\345\207\206\345\267\256", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\345\215\267\347\247\257\346\240\270X\346\240\207\345\207\206\345\267\256", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\351\230\210\345\200\274", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\215\267\347\247\257\346\240\270X", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\345\215\267\347\247\257\346\240\270Y", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\347\241\256\345\256\232\347\262\276\345\272\246", nullptr));
        checkBox_3->setText(QCoreApplication::translate("MainWindow", "\344\272\232\345\203\217\347\264\240", nullptr));
        radioButton_X_add->setText(QCoreApplication::translate("MainWindow", "X\350\275\264\346\226\271\345\220\221\346\213\274\346\216\245", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\344\270\255\345\277\203\347\272\277\346\217\220\345\217\226\347\256\227\346\263\225\357\274\232", nullptr));
        radioButton_Y_add->setText(QCoreApplication::translate("MainWindow", "Y\346\226\271\345\220\221\346\213\274\346\216\245", nullptr));
        pushButton_Caculate->setText(QCoreApplication::translate("MainWindow", "\344\273\205\350\256\241\347\256\227\346\240\207\345\256\232\345\217\202\346\225\260", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\346\255\245\351\225\277\351\227\264\351\232\224\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\347\202\271\344\270\252\346\225\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "CloudSetting", nullptr));
        Lable_Size->setText(QCoreApplication::translate("MainWindow", "Size:", nullptr));
        Lable_Blue->setText(QCoreApplication::translate("MainWindow", "Blue:", nullptr));
        Lable_Red->setText(QCoreApplication::translate("MainWindow", "Red:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215\345\210\235\350\257\225\350\247\206\350\247\222", nullptr));
        Lable_Green->setText(QCoreApplication::translate("MainWindow", "Green:", nullptr));
        pushButton_cloud_clear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\347\202\271\344\272\221\346\225\260\346\215\256", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "\351\241\265", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\346\240\207\345\256\232\350\257\257\345\267\256", nullptr));
        pushButton_clearClib->setText(QCoreApplication::translate("MainWindow", "\346\270\205\351\231\244\346\240\207\345\256\232\344\277\241\346\201\257", nullptr));
        pushButton_save->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\346\240\207\345\256\232", nullptr));
        pushButton_load->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\240\207\345\256\232", nullptr));
        label_isCamera->setText(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\350\277\236\346\216\245\357\274\232", nullptr));
        label_isCalibed->setText(QCoreApplication::translate("MainWindow", "\346\240\207\345\256\232\357\274\232", nullptr));
        label_flagCalibed->setText(QCoreApplication::translate("MainWindow", "No", nullptr));
        label_flagCamera->setText(QCoreApplication::translate("MainWindow", "No", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "\351\241\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
