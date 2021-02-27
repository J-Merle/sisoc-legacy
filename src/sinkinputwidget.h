
#ifndef SRC_SINKINPUTWIDGET_H_
#define SRC_SINKINPUTWIDGET_H_
#include <pulse/pulseaudio.h>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QSlider>
#include <QWidget>
#include <QIcon>

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
    QPushButton* muteButton;

  private:
    QLabel* sinkInputName;
    int muted;

    void toggleMute();

  protected:
    void mousePressEvent(QMouseEvent* event);
};
#endif  // SRC_SINKINPUTWIDGET_H_

