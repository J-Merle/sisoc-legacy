#ifndef SRC_MAINWINDOW_H_
#define SRC_MAINWINDOW_H_
#include <pulse/pulseaudio.h>
#endif  // SRC_MAINWINDOW_H_

#include <map>
#include <QWidget>
#include <QSlider>

class MainWindow : public QWidget {
  public:
    MainWindow();
    virtual ~MainWindow();
    void updateCard(const pa_card_info &info);
    void updateSink(const pa_sink_info &info);

    std::map<uint32_t, QSlider*> sinks;
};
