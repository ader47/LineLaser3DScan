#ifndef THREADS_H
#define THREADS_H
#include <QThread>
#include <QMutex>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

class CameraDisplay:public QThread
{
	Q_OBJECT
public:
    QMutex mutex;
    void StopThread();
    explicit CameraDisplay(int CameraID, std::string winName, QObject* parent = 0);
    ~CameraDisplay();
    cv::Mat GetFrame();
    double GetFPS();
protected:
    void run();
private:
    cv::VideoCapture* videocapture;
    cv::Mat matFrame;
    cv::Mat res;
    bool isStart;
    double fpsInv;
    std::string winName;
};
#endif