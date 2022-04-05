#include "mainwindow.h"
#include <QApplication>

#include <QMainWindow>
#include "vtkoutputwindow.h"
#include <vtkAutoInit.h>
int main(int argc, char *argv[])
{
    VTK_MODULE_INIT(vtkRenderingOpenGL2);
    VTK_MODULE_INIT(vtkInteractionStyle);
    vtkOutputWindow::SetGlobalWarningDisplay(0);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
