#ifndef SRC_SINKWIDGET_H_
#define SRC_SINKWIDGET_H_
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include <QLayout>
#include <QFrame>
#include <pulse/pulseaudio.h>
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

  private:
    QVBoxLayout* mainLayout;
    QHBoxLayout* header;
    QHBoxLayout* content;
    QFrame *separator;
    QHBoxLayout* sinkInputLayout;
    QLabel* sinkName;
    QSlider* mainSlider;
    pa_cvolume volume;
    int muted;
    uint32_t index;

  protected:
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
};
#endif  // SRC_SINKWIDGET_H_
