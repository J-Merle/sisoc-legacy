#include "sinkwidget.h"
#include "sisoc.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <iostream>

SinkWidget::SinkWidget() {
  QHBoxLayout* layout = new QHBoxLayout();
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(200);
  sinkName = new QLabel();
  layout->addWidget(mainSlider);
  this->setLayout(layout);

  vlayout = new QVBoxLayout();
  layout->addLayout(vlayout);
  vlayout->addWidget(sinkName);

  sinkInputLayout = new QHBoxLayout();
  vlayout->addLayout(sinkInputLayout);

  connect(mainSlider, &QSlider::valueChanged, this, &SinkWidget::updateVolumeAction);
}
SinkWidget::~SinkWidget() {}

void SinkWidget::update(const pa_sink_info &info) {
  index = info.index;
  volume = info.volume;
  mainSlider->setMaximum(PA_VOLUME_NORM * 1.5);
  mainSlider->setValue(pa_cvolume_max(&(info.volume)));
  sinkName->setText(info.description);
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
