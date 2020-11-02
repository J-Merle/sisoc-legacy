#include "mainwindow.h"
#include <QSlider>
#include <QHBoxLayout>

MainWindow::MainWindow() {
  QSlider* slider = new QSlider(Qt::Vertical);
  QHBoxLayout* layout = new QHBoxLayout();
  layout->addWidget(slider);
  this->setLayout(layout);

}


MainWindow::~MainWindow() {};
