#ifndef mainwindow_h
#define mainwindow_h
#include <pulse/pulseaudio.h>
#endif

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
