#include "sinkwidget.h"
#include "sisoc.h"
#include <iostream>

SinkWidget::SinkWidget() {
  mainLayout = new QGridLayout();
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(200);
  sinkName = new QLabel();
  sinkInputLayout = new QHBoxLayout();
  mainLayout->addWidget(mainSlider, 0, 0, 2, 1);
  mainLayout->addWidget(sinkName, 0, 1, 1, 1);
  mainLayout->addLayout(sinkInputLayout, 1, 1, 1, 1);
  this->setLayout(mainLayout);


  connect(mainSlider, &QSlider::valueChanged, this, &SinkWidget::updateVolumeAction);
}
SinkWidget::~SinkWidget() {}

void SinkWidget::update(const pa_sink_info &info) {
  index = info.index;
  volume = info.volume;
  muted = info.mute;
  mainSlider->setMaximum(PA_VOLUME_NORM * 1.5);
  mainSlider->setValue(pa_cvolume_max(&(info.volume)));
  sinkName->setText(info.description);
  if (muted) {
    this->setStyleSheet("background-color: grey");
  } else {
    this->setStyleSheet("");
  }
}

void SinkWidget::addSinkInput(SinkInputWidget* sinkInput) {
    sinkInputLayout->addWidget(sinkInput);
}

void SinkWidget::removeSinkInput(SinkInputWidget* sinkInput) {
    sinkInputLayout->removeWidget(sinkInput);
}

void SinkWidget::updateVolumeAction(int value) {
  for (int i = 0; i < volume.channels; i++) {
    volume.values[i] = value;
  }
  pa_operation* o;
  if (!(o = pa_context_set_sink_volume_by_index(get_context(), index, &volume, nullptr, nullptr))) {
    return;
  }

  pa_operation_unref(o);
}
