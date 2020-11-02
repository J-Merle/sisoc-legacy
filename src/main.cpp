#include "mainwindow.h"
#include "pulse/pulseaudio.h"
#include <QApplication>
#include <QPushButton>
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
 
    MainWindow* window = new MainWindow();
    window->show();
 
    return app.exec();
}
