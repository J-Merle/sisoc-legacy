
#ifndef SRC_SINKINPUTWIDGET_H_
#define SRC_SINKINPUTWIDGET_H_
#include <pulse/pulseaudio.h>
#include <QWidget>
#include <QSlider>
#include <QLabel>

class SinkInputWidget : public QWidget {
  public:
    SinkInputWidget();
    virtual ~SinkInputWidget();
    void update(const pa_sink_input_info &info);
    void updateVolumeAction(int value);

    pa_cvolume volume;
    uint32_t index;
    uint32_t sink;
    QSlider* mainSlider;
    QLabel* sinkInputName;
};
#endif  // SRC_SINKINPUTWIDGET_H_
