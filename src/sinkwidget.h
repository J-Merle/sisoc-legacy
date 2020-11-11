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
    void removeSinkInput(uint32_t index);
    void updateVolumeAction(int value);

    pa_cvolume volume;
    uint32_t index;
    QSlider* mainSlider;
    QVBoxLayout* vlayout;
    QHBoxLayout* sinkInputLayout;
    QLabel* sinkName;
    std::map<uint32_t, SinkInputWidget*> sinkInputs;
};
#endif  // SRC_SINKWIDGET_H_
