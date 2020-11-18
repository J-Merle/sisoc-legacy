#include "sinkinputwidget.h"
#include "sisoc.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QDrag>
#include <QMimeData>
#include <iostream>

SinkInputWidget::SinkInputWidget() {
  QVBoxLayout* layout = new QVBoxLayout();
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(150);
  sinkInputName = new QLabel();
  layout->addWidget(mainSlider);
  layout->addWidget(sinkInputName);
  mainSlider->setMaximum(PA_VOLUME_NORM);
  this->setLayout(layout);
  connect(mainSlider, &QSlider::valueChanged, this, &SinkInputWidget::updateVolumeAction);
}
SinkInputWidget::~SinkInputWidget() {}

void SinkInputWidget::update(const pa_sink_input_info &info) {
  index = info.index;
  client = info.client;
  sink = info.sink;
  volume = info.volume;
  int sliderValue = pa_cvolume_max(&volume);
  if (sliderValue != mainSlider->value()) {
    mainSlider->setValue(sliderValue);
  }
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

void SinkInputWidget::setTitle(const char* title) {
  sinkInputName->setText(title);
}

void SinkInputWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton
      && sinkInputName->geometry().contains(event->pos())) {
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

    mimeData->setText(sinkInputName->text());
    drag->setMimeData(mimeData);

    drag->exec();
  }
}

