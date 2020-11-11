#include "sinkinputwidget.h"
#include "sisoc.h"
#include <QVBoxLayout>
#include <QSlider>
#include <iostream>

SinkInputWidget::SinkInputWidget() {
  QVBoxLayout* layout = new QVBoxLayout();
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(150);
  sinkInputName = new QLabel();
  layout->addWidget(mainSlider);
  layout->addWidget(sinkInputName);
  this->setLayout(layout);
  connect(mainSlider, &QSlider::valueChanged, this, &SinkInputWidget::updateVolumeAction);
}
SinkInputWidget::~SinkInputWidget() {}

void SinkInputWidget::update(const pa_sink_input_info &info) {
  index = info.index;
  sink = info.sink;
  volume = info.volume;
  mainSlider->setMaximum(PA_VOLUME_NORM);
  mainSlider->setValue(pa_cvolume_max(&(info.volume)));
  sinkInputName->setText(info.name);
}

void SinkInputWidget::updateVolumeAction(int value) {
  for (int i = 0; i < volume.channels; i++) {
    volume.values[i] = value;
  }
  pa_operation* o;
  if (!(o = pa_context_set_sink_input_volume(get_context(), index, &volume, nullptr, nullptr))) {
    return;
  }

  pa_operation_unref(o);
}
