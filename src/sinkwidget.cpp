#include "sinkwidget.h"
#include <QVBoxLayout>
#include <QSlider>

SinkWidget::SinkWidget() {
  QVBoxLayout* layout = new QVBoxLayout();
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(200);
  sinkName = new QLabel();
  layout->addWidget(mainSlider);
  layout->addWidget(sinkName);
  this->setLayout(layout);
}
SinkWidget::~SinkWidget() {}

void SinkWidget::update(const pa_sink_info &info) {
  mainSlider->setMaximum(PA_VOLUME_NORM * 1.5);
  mainSlider->setValue(pa_cvolume_max(&(info.volume)));
  sinkName->setText(info.description);
}
