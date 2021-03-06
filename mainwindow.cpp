#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <warning.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0,"采集");
    ui->tabWidget->setTabText(1,"标定");
    ui->tabWidget->setTabText(2, "重建");
    ui->tabWidget->setTabText(3, "详细信息");
    //显示模式
    ui->listWidget_BasePic->setViewMode(QListWidget::IconMode);
    //大小
    ui->listWidget_BasePic->setIconSize(QSize(100, 100));
    //间距
    ui->listWidget_BasePic->setSpacing(10);
    //布局
    ui->listWidget_BasePic->setResizeMode(QListView::Adjust);
    //不能移动
    ui->listWidget_BasePic->setMovement(QListView::Static);

    ui->listWidget_Board_Laser->setViewMode(QListWidget::IconMode);
    ui->listWidget_Board_Laser->setIconSize(QSize(100, 100));
    ui->listWidget_Board_Laser->setSpacing(10);
    ui->listWidget_Board_Laser->setResizeMode(QListView::Adjust);
    ui->listWidget_Board_Laser->setMovement(QListView::Static);

    ui->listWidget_Board_noLaser->setViewMode(QListWidget::IconMode);
    ui->listWidget_Board_noLaser->setIconSize(QSize(100, 100));
    ui->listWidget_Board_noLaser->setSpacing(10);
    ui->listWidget_Board_noLaser->setResizeMode(QListView::Adjust);
    ui->listWidget_Board_noLaser->setMovement(QListView::Static);

    ui->listWidget_CalibPic->setViewMode(QListWidget::IconMode);
    ui->listWidget_CalibPic->setIconSize(QSize(100, 100));
    ui->listWidget_CalibPic->setSpacing(10);
    ui->listWidget_CalibPic->setResizeMode(QListView::Adjust);
    ui->listWidget_CalibPic->setMovement(QListView::Static);

    ui->listWidget_LaserLine->setViewMode(QListWidget::IconMode);
    ui->listWidget_LaserLine->setIconSize(QSize(100, 100));
    ui->listWidget_LaserLine->setSpacing(10);
    ui->listWidget_LaserLine->setResizeMode(QListView::Adjust);
    ui->listWidget_LaserLine->setMovement(QListView::Static);

    ui->listWidget_Step_Pic->setViewMode(QListWidget::IconMode);
    ui->listWidget_Step_Pic->setIconSize(QSize(100, 100));
    ui->listWidget_Step_Pic->setSpacing(10);
    ui->listWidget_Step_Pic->setResizeMode(QListView::Adjust);
    ui->listWidget_Step_Pic->setMovement(QListView::Static);


    ui->horizontalSlider_Red->setMinimum(0);
    ui->horizontalSlider_Red->setMaximum(255);
    ui->horizontalSlider_Red->setSliderPosition(0);
    ui->horizontalSlider_Green->setMinimum(0);
    ui->horizontalSlider_Green->setMaximum(255);
    ui->horizontalSlider_Green->setSliderPosition(0);
    ui->horizontalSlider_Blue->setMinimum(0);
    ui->horizontalSlider_Blue->setMaximum(255);
    
    ui->horizontalSlider_Size->setMinimum(1);
    ui->horizontalSlider_Size->setMaximum(6);
    ui->horizontalSlider_Size->setSliderPosition(2);
    ui->spinBox_red->setMinimum(0);
    ui->spinBox_red->setMaximum(255);
    ui->spinBox_green->setMinimum(0);
    ui->spinBox_green->setMaximum(255);
    ui->spinBox_blue->setMinimum(0);
    ui->spinBox_blue->setMaximum(255);
    ui->spinBox_size->setMinimum(1);
    ui->spinBox_size->setMaximum(6);
    connect(ui->horizontalSlider_Red, SIGNAL(valueChanged(int)), ui->spinBox_red, SLOT(setValue(int)));
    connect(ui->spinBox_red, SIGNAL(valueChanged(int)), ui->horizontalSlider_Red, SLOT(setValue(int)));
    connect(ui->horizontalSlider_Green, SIGNAL(valueChanged(int)), ui->spinBox_green, SLOT(setValue(int)));
    connect(ui->spinBox_green, SIGNAL(valueChanged(int)), ui->horizontalSlider_Green, SLOT(setValue(int)));
    connect(ui->horizontalSlider_Blue, SIGNAL(valueChanged(int)), ui->spinBox_blue, SLOT(setValue(int)));
    connect(ui->spinBox_blue, SIGNAL(valueChanged(int)), ui->horizontalSlider_Blue, SLOT(setValue(int)));
    connect(ui->horizontalSlider_Size, SIGNAL(valueChanged(int)), ui->spinBox_size, SLOT(setValue(int)));
    connect(ui->spinBox_size, SIGNAL(valueChanged(int)), ui->horizontalSlider_Size, SLOT(setValue(int)));

    connect(ui->horizontalSlider_Red, SIGNAL(valueChanged(int)), this, SLOT(redSliderValueChanged(int)));
    connect(ui->horizontalSlider_Green, SIGNAL(valueChanged(int)), this, SLOT(greenSliderValueChanged(int)));
    connect(ui->horizontalSlider_Blue, SIGNAL(valueChanged(int)), this, SLOT(blueSliderValueChanged(int)));
    connect(ui->horizontalSlider_Red, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
    connect(ui->horizontalSlider_Green, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
    connect(ui->horizontalSlider_Blue, SIGNAL(sliderReleased()), this, SLOT(RGBsliderReleased()));
    connect(ui->horizontalSlider_Size, SIGNAL(valueChanged(int)), this, SLOT(pSliderValueChanged(int)));

    ui->comboBox_Methods->addItem("Average");
    ui->comboBox_Methods->addItem("Steger");

    popMenu_In_ListWidget_ = new QMenu(this);
    action_Delete_In_ListWidget_ = new QAction(tr("Delete"), this);
    action_Clear_In_ListWidget_ = new QAction(tr("ClearAll"), this);
    popMenu_In_ListWidget_->addAction(action_Delete_In_ListWidget_);
    popMenu_In_ListWidget_->addAction(action_Clear_In_ListWidget_);

    ui->listWidget_CalibPic->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    ui->listWidget_LaserLine->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    ui->listWidget_Step_Pic->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    ui->listWidget_BasePic->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    ui->listWidget_Board_Laser->setProperty("contextMenuPolicy", Qt::CustomContextMenu);
    ui->listWidget_Board_noLaser->setProperty("contextMenuPolicy", Qt::CustomContextMenu);

    connect(ui->listWidget_CalibPic, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->listWidget_LaserLine, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->listWidget_Step_Pic, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->listWidget_BasePic, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->listWidget_Board_Laser, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));
    connect(ui->listWidget_Board_noLaser, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onCustomContextMenuRequested(QPoint)));

    connect(this->action_Delete_In_ListWidget_, SIGNAL(triggered()), this, SLOT(onActionDelete()));
    connect(this->action_Clear_In_ListWidget_, SIGNAL(triggered()), this, SLOT(onActionClear()));

    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(setEven(int)));
    connect(ui->spinBox_3, SIGNAL(valueChanged(int)), this, SLOT(setEven(int)));

    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(255);
    ui->spinBox_2->setMinimum(0);
    ui->spinBox_3->setMinimum(0);
    ui->spinBox_4->setMinimum(0);
    ui->spinBox_5->setMinimum(0);
    
    ui->spinBox_2->setValue(17);
    ui->spinBox_2->setSingleStep(2);
    ui->spinBox_3->setValue(17);
    ui->spinBox_3->setSingleStep(2);
    ui->doubleSpinBox->setValue(0.6);
    ui->doubleSpinBox->setSingleStep(0.02);
    ui->spinBox->setValue(200);
    ui->spinBox_4->setValue(7);
    ui->spinBox_5->setValue(7);
    ui->spinBox_6->setValue(19);
    
    ui->doubleSpinBox_2->setValue(0.3);
    ui->spinBox_8->setValue(4);

    red = 0;
    green = 255;
    blue = 128;
    size = 2;
    ui->horizontalSlider_Green->setSliderPosition(255);
    ui->horizontalSlider_Blue->setSliderPosition(128);
    ui->spinBox_blue->setValue(128);

    isCameraCalib = false;
    isPlaneCalib = false;
    isLaserImg = false;
    isStepCalib = false;
    isBaseCalib = false;
    isCalibed = false;
    getlinemethod = Steger;

    
    int num = listDevices(CameraName);
    for (int i = 0; i < num; i++)
        ui->comboBox_camera_select->addItem(QString::number(i)+":"+QString::fromStdString(CameraName[i]));
    viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    viewer->addCoordinateSystem();
    ui->qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui->qvtkWidget->GetInteractor(), ui->qvtkWidget->GetRenderWindow());
    ui->qvtkWidget->update();
    ui->radioButton_X_add->setChecked(true);

    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    HWND hwnd = (HWND)cvGetWindowHandle(winName.c_str());
    HWND paraent = GetParent(hwnd);//得到nameWindow窗口的父句柄
    SetParent(hwnd, (HWND)ui->widget->winId());//设置ui控件的句柄是父句柄
    ShowWindow(paraent, SW_HIDE);//隐藏掉nameWindow窗口
    cv::resizeWindow(winName, cv::Size(ui->widget->width(), ui->widget->height()));

    CameraDisp = NULL;
    tim = new QTimer();
    tim->setInterval(100);
    connect(tim, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    tim->start();
    
}

MainWindow::~MainWindow()
{
    delete ui;
}
/// <summary>
/// 获取相机列表
/// </summary>
/// <param name="list"></param>
/// <returns></returns>
int MainWindow::listDevices(vector<string>& list)
{
    ICreateDevEnum* pDevEnum = NULL;
    IEnumMoniker* pEnum = NULL;
    int deviceCounter = 0;
    CoInitialize(NULL);

    HRESULT hr = CoCreateInstance(
        CLSID_SystemDeviceEnum,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ICreateDevEnum,
        reinterpret_cast<void**>(&pDevEnum)
    );

    if (SUCCEEDED(hr))
    {
        hr = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnum, 0);
        if (hr == S_OK) {

            IMoniker* pMoniker = NULL;
            while (pEnum->Next(1, &pMoniker, NULL) == S_OK)
            {
                IPropertyBag* pPropBag;
                hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
                    (void**)(&pPropBag));

                if (FAILED(hr)) {
                    pMoniker->Release();
                    continue; // Skip this one, maybe the next one will work.
                }

                VARIANT varName;
                VariantInit(&varName);
                hr = pPropBag->Read(L"Description", &varName, 0);
                if (FAILED(hr))
                {
                    hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                }

                if (SUCCEEDED(hr))
                {
                    hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                    int count = 0;
                    char tmp[255] = { 0 };
                    while (varName.bstrVal[count] != 0x00 && count < 255)
                    {
                        tmp[count] = (char)varName.bstrVal[count];
                        count++;
                    }
                    list.push_back(tmp);
                }

                pPropBag->Release();
                pPropBag = NULL;

                pMoniker->Release();
                pMoniker = NULL;
                deviceCounter++;
            }
            pDevEnum->Release();
            pDevEnum = NULL;

            pEnum->Release();
            pEnum = NULL;
        }
    }
    return deviceCounter;
}
/// <summary>
/// 设置控件只能为奇数
/// </summary>
/// <param name="value"></param>
void MainWindow::setEven(int value)
{
    QSpinBox* currentSpinBox = qobject_cast<QSpinBox*>(sender());
    if (value % 2 == 0)
    {
        QMessageBox::warning(this,"warning","Can not be even number!");
        currentSpinBox->setValue(++value);
    }
}


/// <summary>
/// 右键菜单删除操作
/// </summary>
void MainWindow::onActionDelete()
{
    QList<QListWidgetItem*> items = currentListWidget->selectedItems();
    if (items.count() > 0)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Remove Item"),
            QStringLiteral("Remove %1 item").arg(QString::number(items.count())), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            foreach(QListWidgetItem * var, items) {
                //！！！！！！！！！！！！删除Mat数组！！！！！！！！！！
                currentListWidget->removeItemWidget(var);
                items.removeOne(var);
                delete var;
            }
            ui->textBrowser->append("Deleted!");
        }
    }
}

/// <summary>
/// 右键菜单清空操作
/// </summary>
void MainWindow::onActionClear()
{
    QList<QListWidgetItem*> items = currentListWidget->selectedItems();
    if (items.count() > 0)
    {
        if (QMessageBox::Yes == QMessageBox::question(this, QStringLiteral("Clear"),
            QStringLiteral("Clear?").arg(QString::number(items.count())), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes))
        {
            //！！！！！！！！！！！！删除Mat数组！！！！！！！！！！
            currentListWidget->clear();
            ui->textBrowser->append("Cleared!");
        }
    }
}

/// <summary>
/// 弹出右键菜单操作
/// </summary>
/// <param name="pos"></param>
void MainWindow::onCustomContextMenuRequested(QPoint pos)
{
    qDebug() << ui->comboBox_Methods->currentIndex();
    currentListWidget = qobject_cast<QListWidget*>(sender());
    popMenu_In_ListWidget_->exec(QCursor::pos());
}


/// <summary>
/// 选择标定图片按钮
/// </summary>
void MainWindow::on_BN_Select_Clib_Picture_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;

    ui->textBrowser->append("选择标定图片");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral("选择相机标定图片"),
        "D:/2021_9_18/calibrate_camera",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));
    QList<QString>::Iterator it = fileName.begin();
    ui->textBrowser->append(QString::fromStdString("共选择" + std::to_string(fileName.length()) + "标定图片"));
    //显示缩略图
    for (; it != fileName.end(); it++) {
        QListWidgetItem* imageItem = new QListWidgetItem;
        imageItem->setIcon(QIcon(*it));
        imageItem->setText(*it);
        imageItem->setSizeHint(QSize(120, 100));
        ui->listWidget_CalibPic->addItem(imageItem);
        //加入路径
        Camera_Calib.push_back(cv::imread((*it).toStdString(), CV_LOAD_IMAGE_COLOR));
    }
}


/// <summary>
/// 选择基准图片按钮
/// </summary>
void MainWindow::on_BN_Select_Base_Picture_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;
    ui->textBrowser->append("选择拼接基准");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral("选择拼接基准"),
        "D:/2021_9_18/calibrate_camera",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));
    if (fileName.length() != 1)
    {
        QMessageBox::warning(this, tr(""), "");
        ui->textBrowser->append("");
        return;
    }
    else
    {
        QList<QString>::Iterator it = fileName.begin();
        for (; it != fileName.end(); it++) {
            QListWidgetItem* imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(*it));
            imageItem->setText(*it);
            imageItem->setSizeHint(QSize(120, 100));
            ui->listWidget_BasePic->addItem(imageItem);
            //加入路径
            Base = cv::imread((*it).toStdString(),CV_LOAD_IMAGE_COLOR);
        }
    }
}

/// <summary>
/// 选择无激光的标定板按钮
/// </summary>
void MainWindow::on_BN_Select_Board_noLaser_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;
    ui->textBrowser->append("");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral(""),
        "D:/2021_9_18/calibrate_line",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));

        QList<QString>::Iterator it = fileName.begin();
        for (; it != fileName.end(); it++) {
            QListWidgetItem* imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(*it));
            imageItem->setText(*it);
            imageItem->setSizeHint(QSize(120, 100));
            ui->listWidget_Board_noLaser->addItem(imageItem);
            Plane_Board_noLaser.push_back(cv::imread((*it).toStdString(), CV_LOAD_IMAGE_GRAYSCALE));
        }
}

/// <summary>
/// 选择有激光的标定板按钮
/// </summary>
void MainWindow::on_BN_Select_Board_Laser_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;
    ui->textBrowser->append("");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral(""),
        "D:/2021_9_18/calibrate_line",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));
        QList<QString>::Iterator it = fileName.begin();

        for (; it != fileName.end(); it++) {
            QListWidgetItem* imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(*it));
            imageItem->setText(*it);
            imageItem->setSizeHint(QSize(120, 100));
            ui->listWidget_Board_Laser->addItem(imageItem);
            //path_Plane_Laser.push_back((*it).toStdString());
            Plane_Laser.push_back(cv::imread((*it).toStdString(), CV_LOAD_IMAGE_GRAYSCALE));
        }

}


/// <summary>
/// 选择步长按钮
/// </summary>
void MainWindow::on_BN_Select_Step_Pic_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;
    ui->textBrowser->append("");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral(""),
        "D:/2021_9_18/calibrate_step",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));

        QList<QString>::Iterator it = fileName.begin();
        for (; it != fileName.end(); it++) {
            QListWidgetItem* imageItem = new QListWidgetItem;
            imageItem->setIcon(QIcon(*it));
            imageItem->setText(*it);
            imageItem->setSizeHint(QSize(120, 100));
            ui->listWidget_Step_Pic->addItem(imageItem);
            //path_Step_Calculate.push_back((*it).toStdString());
            Step_Calculate.push_back(cv::imread((*it).toStdString(), CV_LOAD_IMAGE_GRAYSCALE));
        }

}

/// <summary>
/// 激光图片
/// </summary>
void MainWindow::on_BN_Select_LaserLine_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::question(this, "Camera", "Use Camera to grasp image?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
    if (rb != QMessageBox::No)
        return;
    ui->textBrowser->append("");
    QStringList fileName = QFileDialog::getOpenFileNames(
        this,
        QStringLiteral(""),
        "D:/2021_9_18/line",
        tr("images(*.png *jpeg *bmp);;All files(*.*)"));

    QList<QString>::Iterator it = fileName.begin();
    for (; it != fileName.end(); it++) {
        QListWidgetItem* imageItem = new QListWidgetItem;
        imageItem->setIcon(QIcon(*it));
        imageItem->setText(*it);
        imageItem->setSizeHint(QSize(120, 100));
        ui->listWidget_LaserLine->addItem(imageItem);
        //path_Scan_Laser.push_back((*it).toStdString());
        Scan_Laser.push_back(cv::imread((*it).toStdString(),1));
    }
}

/// <summary>
/// 计算标定信息
/// </summary>
void MainWindow::on_pushButton_Caculate_clicked()
{
    if (ui->listWidget_BasePic->count()
        && ui->listWidget_Board_Laser->count()
        && ui->listWidget_Board_noLaser->count()
        && ui->listWidget_CalibPic->count()
        && ui->listWidget_Step_Pic->count()
        )
    {
        camera = new CalibrateCamera();
        ALaserPlane = new LaserPlane();
        ui->textBrowser->append("start....");
        ////相机标定
        camera->LoadCalibImage(Camera_Calib);
        CalibrateBoard* caliboard = new CalibrateBoard(Camera_Calib.size(), 7, 7, 7);
        camera->calibrate(caliboard);
        isCameraCalib = true;
        //输出内参数
        ui->textBrowser_2->append("CameraMatrix:");
        ui->textBrowser_2->append("fx = "+QString::number(camera->GetCameraMatrix().at<double>(0, 0)));
        ui->textBrowser_2->append("fy = " + QString::number(camera->GetCameraMatrix().at<double>(1, 1)));
        ui->textBrowser_2->append("cx = "+QString::number(camera->GetCameraMatrix().at<double>(0, 2)));
        ui->textBrowser_2->append("cy = "+QString::number(camera->GetCameraMatrix().at<double>(1, 2)));

        ui->textBrowser_2->append("Calibrate errors:");
        //输出标定误差
        for (int i = 0; i < camera->GetImageNum(); i++)	
            ui->textBrowser_2->append("No."+ QString::number(i) +": " + QString::number(*(camera->GetErr_ALL() + i)) + " Pixel");
        ui->textBrowser_2->append("Average: "+QString::number(camera->GetAverage_err())+" Pixel");
        ui->textBrowser->append("camera calibrate finished");
        //基准计算
        camera->BaseCaculate(Base, caliboard);
        isBaseCalib = true;
        ui->textBrowser->append("base caculate finished");
        //光平面
        CalibrateBoard* PlaneBoard = new CalibrateBoard(Plane_Board_noLaser.size(), 7, 7, 7);
        ALaserPlane->LoadBoard(Plane_Board_noLaser, camera, PlaneBoard);
        ALaserPlane->LoadLaser(Plane_Laser, camera);
        ALaserPlane->CaculateLaserPlane();
        isPlaneCalib = true;
        ui->textBrowser->append("light plane caculate finished");
        //拼接间隔计算
        CalibrateBoard* TrackBoard = new CalibrateBoard(2, 7, 7, 7);
        Astep = new step(TrackBoard, camera, ui->spinBox_6->value());
        Astep->LoadTrackImage(Step_Calculate);
        Astep->CaculateStep();
        isStepCalib = true;
        ui->textBrowser->append("step caculate finished");
        ui->textBrowser->append("============================finish calibrate============================");
        isCalibed = true;
        ui->label_flagCalibed->setText("Yes");
        //清空图片数组
        Camera_Calib.clear();
        Plane_Board_noLaser.clear();
        Plane_Laser.clear();
        Step_Calculate.clear();
        Scan_Laser.clear();
        //调试代码
        cv::Mat r = camera->GetBaseRvecMat();
        cv::Mat t = camera->GetBaseTvecMat();
        ui->textBrowser_2->append("R:");
        ui->textBrowser_2->append("R11=" + QString::number(r.at<double>(0, 0)));
        ui->textBrowser_2->append("R12=" + QString::number(r.at<double>(0, 1)));
        ui->textBrowser_2->append("R13=" + QString::number(r.at<double>(0, 2)));
        ui->textBrowser_2->append("R21=" + QString::number(r.at<double>(1, 0)));
        ui->textBrowser_2->append("R22=" + QString::number(r.at<double>(1, 1)));
        ui->textBrowser_2->append("R23=" + QString::number(r.at<double>(1, 2)));
        ui->textBrowser_2->append("R31=" + QString::number(r.at<double>(2, 0)));
        ui->textBrowser_2->append("R32=" + QString::number(r.at<double>(2, 1)));
        ui->textBrowser_2->append("R33=" + QString::number(r.at<double>(2, 2)));
        ui->textBrowser_2->append("t:");
        ui->textBrowser_2->append("t1=" + QString::number(t.at<double>(0, 0)));
        ui->textBrowser_2->append("t2=" + QString::number(t.at<double>(1, 0)));
        ui->textBrowser_2->append("t3=" + QString::number(t.at<double>(2, 0)));

        ui->textBrowser_2->append("t3=" + QString::number(ALaserPlane->Get_A()));
        ui->textBrowser_2->append("t3=" + QString::number(ALaserPlane->Get_B()));
        ui->textBrowser_2->append("t3=" + QString::number(ALaserPlane->Get_C()));
        ui->textBrowser_2->append("t3=" + QString::number(ALaserPlane->Get_D()));
        QMessageBox::information(this, "info", "Calibrate finished!", QMessageBox::Ok);
    }
    else
        QMessageBox::warning(this, "warning", "Please check the images for calibration!", QMessageBox::Ok);
}

/// <summary>
/// 重建按钮
/// </summary>
void MainWindow::on_pushButton_clicked()
{
    if (isCalibed && ui->listWidget_LaserLine->count())
    {
        ui->textBrowser->append("Start...");
        int k = 0;
        ProcessTool Tool;
        cv::Mat r = camera->GetBaseRvecMat();
        cv::Mat t = camera->GetBaseTvecMat();

        std::vector<cv::Point3f> Points3d_all;
        if (!cloud)
        {
            cloud.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
            (*cloud).points.resize(Points3d_all.size());
            
        }
        else
            cloud->clear();
        if (!cloud_filtered)
        {
            cloud_filtered.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
            (*cloud_filtered).points.resize(Points3d_all.size());
        }
        else
            cloud_filtered->clear();

        if (!cloud_after_StatisticalRemoval)
        {
            cloud_after_StatisticalRemoval.reset(new pcl::PointCloud<pcl::PointXYZRGB>);
            (*cloud_after_StatisticalRemoval).points.resize(Points3d_all.size());
        }
        else
            cloud_after_StatisticalRemoval->clear();

        vector<vector<pcl::PointXYZRGB>> Points3ds;
        clock_t start, end;
        double averagetime = 0;
        for (vector<cv::Mat>::iterator it = Scan_Laser.begin(); it != Scan_Laser.end(); it++, k++)
        {
            start = clock();
            vector<cv::Point2d> Points;
            vector<pcl::PointXYZRGB> Pt;
            switch (ui->comboBox_Methods->currentIndex())
            {
            case 0:
                Points = Tool.AverageLine(*it, cv::Point2d(0, 0), cv::Point2d(it->cols, it->rows));
                break;
            case 1:
                Points = Tool.StegerLine(
                    *it,
                    ui->spinBox_2->value(),
                    ui->spinBox_3->value(),
                    ui->spinBox_4->value(),
                    ui->spinBox_5->value(),
                    ui->spinBox->value(),
                    ui->doubleSpinBox->value(),
                    ui->checkBox_3->isChecked()
                );
                break;
            }
            end = clock();
            //调试代码，计算处理时间
            double endtime = (double)(end - start) / CLOCKS_PER_SEC;
            averagetime += endtime * 1000;
            ui->textBrowser->append("average time = " + QString::number(endtime *1000) + "ms");

            //调试代码
            cv::Point3f Points00 = camera->getWorldPoints(cv::Point2f(0, 0), r, t);
            cv::Point3f Points60 = camera->getWorldPoints(cv::Point2f(4, 0), r, t);
            cv::Point3f Points06 = camera->getWorldPoints(cv::Point2f(0, 4), r, t);
            ui->textBrowser_2->append("P00x = " + QString::number(Points00.x));
            ui->textBrowser_2->append("P00y = " + QString::number(Points00.y));
            ui->textBrowser_2->append("P00z = " + QString::number(Points00.z));
            ui->textBrowser_2->append("P60x = " + QString::number(Points60.x));
            ui->textBrowser_2->append("P60y = " + QString::number(Points60.y));
            ui->textBrowser_2->append("P60z = " + QString::number(Points60.z));
            ui->textBrowser_2->append("P06x = " + QString::number(Points06.x));
            ui->textBrowser_2->append("P06y = " + QString::number(Points06.y));
            ui->textBrowser_2->append("P06z = " + QString::number(Points06.z));

            
            for (int j = 0; j < Points.size(); j++)
            {
                //中心线提取函数返回的数组的坐标为(Points[2 * k + 0], Points[2 * k + 1])
                cv::Point3f Points3d = camera->getWorldPoints(cv::Point2f(Points[j].x, Points[j].y), r, t);
                
                Points3d.z = (ALaserPlane->Get_D() - ALaserPlane->Get_A() * Points3d.x - ALaserPlane->Get_B() * Points3d.y) / ALaserPlane->Get_C();
                //拼接     后续需要输入还是标定？
                //if(ui->radioButton_Y_add->isChecked())
                //    Points3d.y += k * Astep->GetStep().at<double>(1, 0);
                //else 
                //    Points3d.x += k * Astep->GetStep().at<double>(0, 0);
                Points3d.y += k * Astep->GetStep().at<double>(1, 0);
                Points3d.x += k * Astep->GetStep().at<double>(0, 0);
                Points3d.z += k * Astep->GetStep().at<double>(2, 0);
                //Pt.push_back(pcl::PointXYZRGB(Points3d.x, Points3d.y, Points3d.z, red, green, blue));
                cloud->points.push_back(pcl::PointXYZRGB(Points3d.x, Points3d.y, Points3d.z, red, green, blue));
            }

            //对每条线条进行处理
            //半径滤波
            pcl::RadiusOutlierRemoval<pcl::PointXYZRGB> outrem;
            outrem.setInputCloud(cloud);
            outrem.setRadiusSearch(ui->doubleSpinBox_2->value());
            outrem.setMinNeighborsInRadius(ui->spinBox_8->value());
            outrem.filter(*cloud_filtered);
            

            //简化线条，距离需要自行设定
            CloudProcessTool CloudTool;
            CloudTool.cutCloud(cloud_filtered, 1.5);
            
            
            //点云线条平滑处理
            //*********
            // //双边滤波器
            //pcl::PointCloud<pcl::PointXYZRGB>::Ptr outcloud(new pcl::PointCloud<pcl::PointXYZRGB>);
            //pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree1(new  pcl::search::KdTree<pcl::PointXYZRGB>);
            //tree1->setInputCloud(cloud);
            //pcl::BilateralFilter<pcl::PointXYZRGB> nf;
            //nf.setInputCloud(cloud);  //设置输入点云
            //nf.setSearchMethod(tree1); //设置搜索方法
            //nf.setHalfSize(1);      //高斯滤波器的一半窗口值
            //nf.setStdDev(0.01);           //标准差
            //nf.filter(*outcloud);


            //特征点提取，由于点云线条不够平滑，暂时无法使用
             
            //vector<double> k0;
            //vector<double> k1;
            //bool firstCase = true;
            //pcl::PointIndices::Ptr inliers(new pcl::PointIndices());
            //vector<int> T;
            //const double Pi = 3.14159265;
            //for (int i = 1; i < cloud_filtered->points.size(); i += 2)
            //{
            //    if (firstCase)
            //    {
            //        k0 = PointK(cloud_filtered->points[i - 1], cloud_filtered->points[i]);
            //        firstCase = false;
            //    }
            //    else
            //    {
            //        k1 = PointK(cloud_filtered->points[i - 1], cloud_filtered->points[i]);
            //        //判断当前和之前的角度
            //        //cout << dotMul(k0, k1) << endl;
            //        //cout << vNorm(k0) << " " << vNorm(k1) << endl;
            //        //cout << (dotMul(k0, k1) / (vNorm(k0) * vNorm(k1))) << endl;
            //        //cout << "Angle:";
            //        //计算向量之间的角度
            //        double Angle = (acos((dotMul(k0, k1) / (vNorm(k0) * vNorm(k1))))) / Pi * 180;
            //        //cout << Angle << endl;
            //        //大于一个角度阈值
            //        if (Angle > 7)
            //        {
            //            //inliers->indices.push_back(i);
            //            T.push_back(i);
            //        }
            //        //如果大于一个角度

            //        //将后一个替换为当前向量
            //        k0 = k1;
            //    }
            //}
            //
            // //根据阈值将点删去
            //for (int i = 0; i < T[2]; i++)
            //{
            //    inliers->indices.push_back(i);
            //}

            //for (int i = T[2]; i < cloud_filtered->points.size(); i++)
            //{
            //    inliers->indices.push_back(i);
            //}

            //cutCloud(cloud_filtered, inliers);

            //直接根据ROI来确定？？？？？？？
            //可以设置多个ROI？？？
            for (int i = 0; i < cloud_filtered->points.size(); i++)
                Pt.push_back(cloud_filtered->points[i]);
            Points3ds.push_back(Pt);
            Pt.clear();
            //if(Points3ds.size()==31)
            //    if (!cloud->empty())
            //        pcl::io::savePCDFileASCII("asd.pcd", *cloud_filtered);
            //    else
            //        QMessageBox::warning(NULL, "warning", "Empty!", QMessageBox::Ok);
                
            cloud_filtered->points.clear();
            cloud->clear();
        }

        //调试代码，计算处理平均时间
        averagetime /= Points3ds.size();
        ui->textBrowser->append("time=" + QString::number(averagetime) + "ms");

        ui->textBrowser_2->append("x"+QString::number(Astep->GetStep().at<double>(0, 0)));
        ui->textBrowser_2->append("y" + QString::number(Astep->GetStep().at<double>(1, 0)));
        ui->textBrowser_2->append("z" + QString::number(Astep->GetStep().at<double>(2, 0)));
        ui->textBrowser->append("deep caculate finished");
        ui->textBrowser->append("clearing scan laser images");
        Scan_Laser.clear();
        ui->listWidget_LaserLine->clear();
        ui->textBrowser->append("cleared");
        ui->textBrowser->append("showing cloud....");

        for (int i = 0; i < Points3ds.size(); i++)
            for (int j = 0; j < Points3ds[i].size(); j++)
                cloud->points.push_back(Points3ds[i][j]);


        //统计滤波，不好用
        //pcl::StatisticalOutlierRemoval<pcl::PointXYZRGB> Statistical;
        //Statistical.setInputCloud(cloud);
        //Statistical.setMeanK(20);
        //Statistical.setStddevMulThresh(0.7);
        //Statistical.filter(*cloud_after_StatisticalRemoval);
        // //保存点云
 /*       pcl::io::savePCDFile("hanfeng.pcd", *cloud);*/

        viewer->addPointCloud(cloud, "cloud");
        viewer->updatePointCloud(cloud, "cloud");

        viewer->resetCamera();
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, size, "cloud");
        ui->qvtkWidget->update();
        ui->textBrowser->append("================finish==================");
        cv::destroyWindow("GetLine");
        QMessageBox::information(NULL, "info", "Caculate finish!", QMessageBox::Ok);
    }
    else
        if(!isCalibed)
            QMessageBox::warning(NULL, "warning", "Please calibrate first!", QMessageBox::Ok);
        else
            QMessageBox::warning(NULL, "warning", "Please check the images for caculation!", QMessageBox::Ok);
}
/// <summary>
/// 需要重写
/// </summary>
void MainWindow::on_pushButton_2_clicked()
{
    viewer->resetCamera();
    ui->qvtkWidget->update();
}

/// <summary>
/// 清空标定信息
/// </summary>
void MainWindow::on_pushButton_clearClib_clicked()
{
    if (camera != NULL&&ALaserPlane != NULL&&Astep != NULL)
    {
        isCalibed = false;
        isCameraCalib = false;
        isPlaneCalib = false;
        isStepCalib = false;
        isBaseCalib = false;
        Camera_Calib.clear();
        Plane_Board_noLaser.clear();
        Plane_Laser.clear();
        Step_Calculate.clear();
        ui->listWidget_BasePic->clear();
        ui->listWidget_Board_Laser->clear();
        ui->listWidget_Board_noLaser->clear();
        ui->listWidget_CalibPic->clear();
        ui->listWidget_Step_Pic->clear();
        cloud->points.clear();
        ui->listWidget_LaserLine->clear();
        ui->textBrowser_2->append("======================abandoned=======================");
        ui->label_flagCalibed->setText("No");
        delete camera;
        delete ALaserPlane;
        delete Astep;
        QMessageBox::information(this, "info", "Cleared!");
    }
    else
        QMessageBox::warning(this,"warning","Have not Calibrated!");
}

/// <summary>
/// 点云颜色滑块操作
/// </summary>
void MainWindow::RGBsliderReleased()
{
    if (cloud !=NULL&&viewer!=NULL)
    {
        for (size_t i = 0; i < cloud->size(); i++)
        {
            cloud->points[i].r = red;
            cloud->points[i].g = green;
            cloud->points[i].b = blue;
        }
        viewer->updatePointCloud(cloud, "cloud");
        ui->qvtkWidget->update();
    }
}

/// <summary>
/// 点云清空
/// </summary>
void MainWindow::on_pushButton_cloud_clear_clicked()
{
    if (cloud != NULL)
    {
        cloud->points.clear();
        cloud->points.clear();
        viewer->updatePointCloud(cloud, "cloud");
        viewer->resetCamera();
        ui->qvtkWidget->update();
        QMessageBox::information(this, "info", "Points cloud has been cleared!");
    }
    else
        QMessageBox::information(this,"info","Points cloud has not initialed!");
}

/// <summary>
/// 刷新相机信息
/// </summary>
void MainWindow::on_pushButton_flashcamera_clicked()
{
    ui->comboBox_camera_select->clear();
    this->CameraName.clear();
    int num = this->listDevices(this->CameraName);
    if (num == 0)
        QMessageBox::warning(this,"warning","No Camera Connected!");
    else
    {
        for (int i = 0; i < num; i++)
            ui->comboBox_camera_select->addItem(QString::number(i) + ":" + QString::fromStdString(CameraName[i]));
        QMessageBox::information(this,"info","Success!");
    }
}

/// <summary>
/// 点云颜色滑块操作
/// </summary>
/// <param name="value"></param>
void MainWindow::pSliderValueChanged(int value)
{
    size = value;
    if (cloud != NULL && viewer != NULL)
    {
        viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, value, "cloud");
        ui->qvtkWidget->update();
    }
}

/// <summary>
/// 复位相机视角
/// </summary>
void MainWindow::on_pushButton_camerastart_clicked()
{
    if (!CameraDisp)
    {
        CameraDisp = new CameraDisplay(ui->comboBox_camera_select->currentIndex(), winName, this);
        CameraDisp->start();
    }
}

/// <summary>
/// 相机暂停
/// </summary>
void MainWindow::on_pushButton_camerapause_clicked()
{
    if(CameraDisp)
        CameraDisp->mutex.lock();
}

/// <summary>
/// 相机继续
/// </summary>
void MainWindow::on_pushButton_cameracontinue_clicked()
{
    if (CameraDisp)
        CameraDisp->mutex.unlock();
}

/// <summary>
/// 相机停止
/// </summary>
void MainWindow::on_pushButton_camerastop_clicked()
{
    if (CameraDisp)
    {
        CameraDisp->StopThread();
        CameraDisp->deleteLater();
        CameraDisp->wait();
        CameraDisp->destroyed();
        delete CameraDisp;
        CameraDisp = NULL;
        if(!CameraDisp)
            QMessageBox::information(this,"info","Stoped!");
    }
}

/// <summary>
/// 保存标定信息，未写好
/// </summary>
void MainWindow::on_pushButton_save_clicked()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this,
        tr("Save Config"), "Calibration", tr("Config Files (*.ifg)"));
    if (!fileName.isNull())
    {
        //fileName是文件名
        if (camera != NULL && ALaserPlane != NULL && Astep != NULL)
        {

            //序列化到文件
            ofstream osm(fileName.toStdString(), ios::out | ios::binary);
            //这个地址一定要转换成char*
            osm.write((char*)camera, sizeof(CalibrateCamera));
            osm.write((char*)ALaserPlane, sizeof(LaserPlane));
            osm.write((char*)Astep, sizeof(step));
            osm.close();
            QMessageBox::information(this, "info", "Success!", QMessageBox::Ok);
        }
        else
        {
            QMessageBox::warning(this, "warning", "Have not calibrated!", QMessageBox::Ok);
        }
    }

}

/// <summary>
/// 加载标定信息，未写好
/// </summary>
void MainWindow::on_pushButton_load_clicked()
{

    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open Config"), "Calibration", tr("Config Files (*.ifg)"));

    if (!fileName.isNull())
    {
        if (camera != NULL && ALaserPlane != NULL && Astep != NULL)
        {
            delete camera;
            delete ALaserPlane;
            delete Astep;
        }
        camera = (CalibrateCamera*)malloc(sizeof(CalibrateCamera));
        ALaserPlane = (LaserPlane*)malloc(sizeof(LaserPlane));
        Astep = (step*)malloc(sizeof(step));
        ifstream ism(fileName.toStdString(), ios::in | ios::binary);
        //不用写左值
        ism.read((char*)camera, sizeof(CalibrateCamera));
        ism.read((char*)ALaserPlane, sizeof(LaserPlane));
        ism.read((char*)Astep, sizeof(step));
        ism.close();
        //输出内参数，调试代码
        //ui->textBrowser_2->append("CameraMatrix:");
        //ui->textBrowser_2->append("fx = " + QString::number(camera->GetCameraMatrix().at<double>(0, 0)));
        //ui->textBrowser_2->append("fy = " + QString::number(camera->GetCameraMatrix().at<double>(1, 1)));
        //ui->textBrowser_2->append("cx = " + QString::number(camera->GetCameraMatrix().at<double>(0, 2)));
        //ui->textBrowser_2->append("cy = " + QString::number(camera->GetCameraMatrix().at<double>(1, 2)));

        //ui->textBrowser_2->append("Calibrate errors:");
        ////输出标定误差
        //for (int i = 0; i < camera->GetImageNum(); i++)
        //    ui->textBrowser_2->append("No." + QString::number(i) + ": " + QString::number(*(camera->GetErr_ALL() + i)) + " Pixel");
        //ui->textBrowser_2->append("Average: " + QString::number(camera->GetAverage_err()) + " Pixel");

        isCalibed = true;
        isCameraCalib = true;
        isPlaneCalib = true;
        isStepCalib = true;
        isBaseCalib = true;
        QMessageBox::information(this, "info", "Success!", QMessageBox::Ok);
    }
}

/// <summary>
/// 计时器，获得相机FPS
/// </summary>
void MainWindow::onTimeOut()
{
    if (CameraDisp)
        ui->label_2->setText(QString::number(CameraDisp->GetFPS())+"fps");
}

/// <summary>
/// 点云颜色滑块操作
/// </summary>
/// <param name="value"></param>
void MainWindow::redSliderValueChanged(int value)
{
    red = value;
}

void MainWindow::greenSliderValueChanged(int value)
{
    green = value;
}

void MainWindow::blueSliderValueChanged(int value)
{
    blue = value;
}
