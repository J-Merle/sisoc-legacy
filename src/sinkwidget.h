#ifndef SRC_SINKWIDGET_H_
#define SRC_SINKWIDGET_H_
#include <pulse/pulseaudio.h>
#include <QWidget>
#include <QSlider>
#include <QLabel>

class SinkWidget : public QWidget {
  public:
    SinkWidget();
    virtual ~SinkWidget();
    void update(const pa_sink_info &info);
    void updateVolumeAction(int value);

    pa_cvolume volume;
    uint32_t index;
    QSlider* mainSlider;
    QLabel* sinkName;
};
#endif  // SRC_SINKWIDGET_H_
