#include "mainwindow.h"
#include "sinkwidget.h"
#include <QSlider>
#include <QHBoxLayout>
#include <iostream>

MainWindow::MainWindow() {
  sinkLayout = new QHBoxLayout();
  sinkLayout->setSpacing(20);
  this->setLayout(sinkLayout);
}


MainWindow::~MainWindow() {}

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

void MainWindow::removeSink(uint32_t index) {
  if(sinks.count(index)) {
    SinkWidget* sink = sinks[index];
    sinkLayout->removeWidget(sink);
    sinks.erase(index);
    delete sink;
  }
}

void MainWindow::updateSinkInput(const pa_sink_input_info &info) {
  SinkInputWidget* sinkInput;
  if (sinkInputs.count(info.index)) {
    sinkInput = sinkInputs[info.index];

    if (sinkInput->sink == info.sink) {
      sinkInput->update(info);
    } else {
      // The sink input does not belong to the same sink
      // If the sink still exist then the input should be removed
      if (sinks.count(sinkInput->sink)) {
        sinks[sinkInput->sink]->removeSinkInput(sinkInput);
      } else {
        // If the old sink has been removed we must init a new SinkInputWidget
        sinkInputs[info.index] = new SinkInputWidget();
        sinkInput = sinkInputs[info.index];
      }
      sinkInput->setTitle(clients[info.client]);
      sinks[info.sink]->addSinkInput(sinkInput);
      sinkInput->update(info);
    }

  } else {
    sinkInput = new SinkInputWidget();
    sinkInput->update(info);
    sinkInput->setTitle(clients[info.client]);
    sinkInputs[info.index] = sinkInput;
    sinks[info.sink]->addSinkInput(sinkInput);
  }
}

void MainWindow::removeSinkInput(uint32_t index) {
  if (sinkInputs.count(index)) {
    SinkInputWidget* sinkInput = sinkInputs[index];
    sinks[sinkInput->sink]->removeSinkInput(sinkInput);
    sinkInputs.erase(index);
    delete sinkInput;
  }
}

void MainWindow::updateClient(const pa_client_info &info) {
  clients[info.index] = qstrdup(info.name);
  for (auto & sinkInputWidget : sinkInputs) {
    SinkInputWidget *w = sinkInputWidget.second;
    if (w->client == info.index) {
      w->setTitle(info.name);
    }
  }
}
