#include "mainwindow.h"
#include "sinkwidget.h"
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
  SinkWidget* slider;
  if (sinks.count(info.index)) {
    slider = sinks[info.index];
  } else {
    slider = new SinkWidget();
    this->layout()->addWidget(slider);
    sinks[info.index] = slider;
  }
  slider->update(info);
}
