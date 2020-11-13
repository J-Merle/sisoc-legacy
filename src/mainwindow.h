#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_
#include <pulse/pulseaudio.h>
#endif  // SRC_MAINWINDOW_H_

#include <map>
#include <QWidget>
#include <QHBoxLayout>
#include <QSlider>
#include "sinkwidget.h"

class MainWindow : public QWidget {
  public:
    MainWindow();
    virtual ~MainWindow();
    void updateCard(const pa_card_info &info);
    void updateSink(const pa_sink_info &info);
    void removeSink(uint32_t index);
    void updateSinkInput(const pa_sink_input_info &info);
    void removeSinkInput(uint32_t index);
    void updateClient(const pa_client_info &info);

    std::map<uint32_t, SinkWidget*> sinks;
    std::map<uint32_t, SinkInputWidget*> sinkInputs;
    std::map<uint32_t, const char*> clients;

    QHBoxLayout* sinkLayout;
};
