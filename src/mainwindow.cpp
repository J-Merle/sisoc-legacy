#include "mainwindow.h"
#include <QSlider>
#include <QHBoxLayout>
#include <iostream>

MainWindow::MainWindow() {
  QHBoxLayout* layout = new QHBoxLayout();
  this->setLayout(layout);
}


MainWindow::~MainWindow() {}


void MainWindow::updateCard(const pa_card_info &info) {
  std::cout << info.name << std::endl;
}

void MainWindow::updateSink(const pa_sink_info &info) {
  std::cout << "name : " << info.name << std::endl;
  std::cout << "description : " << info.description << std::endl;
  std::cout << "base_volume : " << info.base_volume << std::endl;
  char cc[256];
  std::cout << pa_volume_snprint(cc, 256, pa_cvolume_max(&(info.volume))) << std::endl;
  std::cout << pa_cvolume_max(&(info.volume)) << std::endl;
  QSlider* slider;
  if (sinks.count(info.index)) {
    slider = sinks[info.index];
  } else {
    slider = new QSlider(Qt::Vertical);
    slider->setMaximum(PA_VOLUME_NORM * 1.5);
    this->layout()->addWidget(slider);
    sinks[info.index] = slider;
  }
  slider->setValue(pa_cvolume_max(&(info.volume)));
}
