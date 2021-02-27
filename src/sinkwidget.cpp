#include "sinkwidget.h"
#include "sisoc.h"
#include <iostream>

SinkWidget::SinkWidget() {
  mainLayout = new QVBoxLayout();
  
  header = new QHBoxLayout();
  sinkName = new QLabel();
  header->addWidget(sinkName);
  mainLayout->addLayout(header);

  separator = new QFrame();
  separator->setObjectName(QString::fromUtf8("line"));
  separator->setGeometry(QRect(0, 0, 2, 100));
  separator->setFrameShape(QFrame::VLine);

  content = new QHBoxLayout();
  content->setAlignment(Qt::AlignLeft);
  content->setSpacing(20);
  content->setSizeConstraint(QLayout::SetMaximumSize);
  mainSlider = new QSlider();
  mainSlider->setMinimumHeight(200);
  sinkInputLayout = new QHBoxLayout();
  sinkInputLayout->setSpacing(10);
  content->addWidget(mainSlider);
  content->addWidget(separator);
  //mainLayout->addWidget(sinkName, 0, 1, 1, 1);
  content->addLayout(sinkInputLayout);
  mainLayout->addLayout(content);
  this->setLayout(mainLayout);

  setAcceptDrops(true);

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

void SinkWidget::dropEvent(QDropEvent *event) {
  SinkInputWidget *w = static_cast<SinkInputWidget*>(event->source());
  if (!w)
    return;
  pa_operation* o;
  if (!(o = pa_context_move_sink_input_by_index(get_context(), w->index, index, nullptr, nullptr))) {
    // TODO handle error properly
  }
  pa_operation_unref(o);
}

void SinkWidget::dragEnterEvent(QDragEnterEvent *event) {
  event->acceptProposedAction();
}
