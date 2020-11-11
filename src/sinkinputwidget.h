
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
    void setTitle(const char* title);

    pa_cvolume volume;
    uint32_t index;
    uint32_t sink;
    uint32_t client;
    QSlider* mainSlider;
  private:
    QLabel* sinkInputName;
};
#endif  // SRC_SINKINPUTWIDGET_H_
