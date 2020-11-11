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

void MainWindow::updateSinkInput(const pa_sink_input_info &info) {
  SinkInputWidget* sinkInput;
  if (sinkInputs.count(info.index)) {
    sinkInput = sinkInputs[info.index];

    if (sinkInput->sink == info.sink) {
      sinkInput->update(info);
    } else {
      sinks[sinkInput->sink]->removeSinkInput(sinkInput);
      sinkInput->update(info);
      sinks[sinkInput->sink]->addSinkInput(sinkInput);

    }

  } else {
    sinkInput = new SinkInputWidget();
    sinkInput->update(info);
    sinkInput->setTitle(clients[info.client]);
    sinkInputs[info.index] = sinkInput;
    sinks[sinkInput->sink]->addSinkInput(sinkInput);
    for(auto & client : clients) {
      std::cout << client.first << " " << client.second << std::endl;
    }
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
  std::cout << "Client : " << info.name << std::endl;
  clients[info.index] = info.name;
  for (auto & sinkInputWidget : sinkInputs) {
    SinkInputWidget *w = sinkInputWidget.second;
    if (w->client == info.index) {
      w->setTitle(info.name);
    }
  }
}
