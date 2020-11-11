#ifndef SRC_SINKWIDGET_H_
#define SRC_SINKWIDGET_H_
#include <pulse/pulseaudio.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "sinkinputwidget.h"

class SinkWidget : public QWidget {
  public:
    SinkWidget();
    virtual ~SinkWidget();
    void update(const pa_sink_info &info);
    void updateSinkInput(const pa_sink_input_info &info);
    void updateVolumeAction(int value);
    void addSinkInput(SinkInputWidget* sinkInput);
    void removeSinkInput(SinkInputWidget* sinkInput);

    pa_cvolume volume;
    uint32_t index;
    QSlider* mainSlider;
    QVBoxLayout* vlayout;
    QHBoxLayout* sinkInputLayout;
    QLabel* sinkName;
};
#endif  // SRC_SINKWIDGET_H_
