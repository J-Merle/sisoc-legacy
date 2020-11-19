#include "sinkinputwidget.h"
#include "sisoc.h"
#include <QVBoxLayout>
#include <QSlider>
#include <QDrag>
#include <QMimeData>
#include <iostream>

SinkInputWidget::SinkInputWidget() {
  QVBoxLayout* layout = new QVBoxLayout();
  mainSlider = new QSlider(this);
  mainSlider->setMinimumHeight(150);
  mainSlider->setMaximum(PA_VOLUME_NORM);
  sinkInputName = new QLabel(this);
  muteButton = new QPushButton(this);

  layout->addWidget(muteButton);
  layout->addWidget(mainSlider);
  layout->addWidget(sinkInputName);
  layout->setAlignment(mainSlider, Qt::AlignCenter);
  layout->setAlignment(muteButton, Qt::AlignCenter);
  layout->setAlignment(sinkInputName, Qt::AlignCenter);
  this->setLayout(layout);

  this->setMaximumWidth(75);

  connect(mainSlider, &QSlider::valueChanged, this, &SinkInputWidget::updateVolumeAction);
  connect(muteButton, &QPushButton::clicked, this, &SinkInputWidget::toggleMute);
}
SinkInputWidget::~SinkInputWidget() {}

void SinkInputWidget::update(const pa_sink_input_info &info) {
  index = info.index;
  client = info.client;
  sink = info.sink;
  volume = info.volume;
  muted = info.mute;

  if (muted) {
    muteButton->setText("Unmute");
    this->setStyleSheet("background-color: grey");
  } else {
    muteButton->setText("Mute");
    this->setStyleSheet("");
  }

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

void SinkInputWidget::toggleMute() {
  pa_operation* o;
  if (!(o = pa_context_set_sink_input_mute(get_context(), index, !muted, nullptr, nullptr))) {
    return;
  }

  pa_operation_unref(o);
}
