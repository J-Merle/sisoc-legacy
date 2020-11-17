#include <pulse/glib-mainloop.h>

#include <QApplication>
#include <QPushButton>

#include <iostream>

#include "mainwindow.h"

#define VERSION "0.1"

static pa_context* context = nullptr;
static pa_mainloop_api* api = nullptr;

gboolean connect_to_pulse(gpointer userdata);

void show_error(const char *txt) {
    char buf[256];

    snprintf(buf, sizeof(buf), "%s: %s", txt, pa_strerror(pa_context_errno(context)));
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow* window = new MainWindow();
    pa_glib_mainloop *m = pa_glib_mainloop_new(g_main_context_default());
    g_assert(m);
    api = pa_glib_mainloop_get_api(m);
    connect_to_pulse(window);

    window->show();
    return app.exec();
}

void sink_cb(pa_context *, const pa_sink_info *i, int eol, void *userdata) {
    MainWindow *w = static_cast<MainWindow*>(userdata);

    if (eol < 0) {
        if (pa_context_errno(context) == PA_ERR_NOENTITY)
            return;

        show_error(QObject::tr("Sink callback failure").toUtf8().constData());
        return;
    }
        if (eol > 0) {
        return;
    }

    w->updateSink(*i);
}

void sink_input_cb(pa_context *, const pa_sink_input_info *i, int eol, void *userdata) {
    MainWindow *w = static_cast<MainWindow*>(userdata);

    if (eol < 0) {
        if (pa_context_errno(context) == PA_ERR_NOENTITY)
            return;

        show_error(QObject::tr("sink_input callback failure").toUtf8().constData());
        return;
    }
        if (eol > 0) {
        return;
    }

    w->updateSinkInput(*i);
}

void client_cb(pa_context *, const pa_client_info *i, int eol, void *userdata) {
    MainWindow *w = static_cast<MainWindow*>(userdata);

    if (eol < 0) {
        if (pa_context_errno(context) == PA_ERR_NOENTITY)
            return;

        show_error(QObject::tr("client callback failure").toUtf8().constData());
        return;
    }
        if (eol > 0) {
        return;
    }
    w->updateClient(*i);
}

void subscribe_cb(pa_context *c, pa_subscription_event_type_t t, uint32_t index, void *userdata) {
  MainWindow *w = static_cast<MainWindow*>(userdata);

  // Find out which kind of event occured
  switch (t & PA_SUBSCRIPTION_EVENT_FACILITY_MASK) {
    case PA_SUBSCRIPTION_EVENT_SINK :
      if ((t & PA_SUBSCRIPTION_EVENT_TYPE_MASK) == PA_SUBSCRIPTION_EVENT_REMOVE) {
        w->removeSink(index);
      } else {
        pa_operation *o;
        if (!(o = pa_context_get_sink_info_by_index(c, index, sink_cb, w))) {
          show_error(QObject::tr("pa_context_get_sink_info_by_index() failed").toUtf8().constData());
          return;
        }
        pa_operation_unref(o);
      }
      break;
    case PA_SUBSCRIPTION_EVENT_SINK_INPUT:
      if ((t & PA_SUBSCRIPTION_EVENT_TYPE_MASK) == PA_SUBSCRIPTION_EVENT_REMOVE) {
        w->removeSinkInput(index);
      }
      else {
        pa_operation *o;
        if (!(o = pa_context_get_sink_input_info(c, index, sink_input_cb, w))) {
          show_error(QObject::tr("pa_context_get_sink_info_by_index() failed").toUtf8().constData());
          return;
        }
        pa_operation_unref(o);
      }
      break;
    case PA_SUBSCRIPTION_EVENT_CLIENT :
      pa_operation *o;
      if (!(o = pa_context_get_client_info(c, index, client_cb, w))) {
        show_error(QObject::tr("pa_context_get_client_info() failed").toUtf8().constData());
        return;
      }
      pa_operation_unref(o);
      break;
  }
}

void context_state_callback(pa_context *c, void *userdata) {
    MainWindow *w = static_cast<MainWindow*>(userdata);

    g_assert(c);

    switch (pa_context_get_state(c)) {
        case PA_CONTEXT_UNCONNECTED:
        case PA_CONTEXT_CONNECTING:
        case PA_CONTEXT_AUTHORIZING:
        case PA_CONTEXT_SETTING_NAME:
            break;

        case PA_CONTEXT_READY: {
            pa_operation *o;

            // What to do each time an event we subscribed to is updated
            pa_context_set_subscribe_callback(c, subscribe_cb, w);

            if (!(o = pa_context_subscribe(c,
                                           (pa_subscription_mask_t)(PA_SUBSCRIPTION_MASK_SINK |
                                             PA_SUBSCRIPTION_MASK_SINK_INPUT |
                                             PA_SUBSCRIPTION_MASK_CLIENT
                                             ),
                                           nullptr,
                                           nullptr))) {
                show_error(QObject::tr("pa_context_subscribe() failed").toUtf8().constData());
                return;
            }
            pa_operation_unref(o);



            // Retrieve once the desired informations because cb are no triggered on connection
            if (!(o = pa_context_get_sink_info_list(c, sink_cb, w))) {
                show_error(QObject::tr("pa_context_get_sink_info_list() failed").toUtf8().constData());
                return;
            }
            pa_operation_unref(o);

            if (!(o = pa_context_get_sink_input_info_list(c, sink_input_cb, w))) {
                show_error(QObject::tr("pa_context_get_sink_input_info_list() failed").toUtf8().constData());
                return;
            }
            pa_operation_unref(o);

            if (!(o = pa_context_get_client_info_list(c, client_cb, w))) {
              show_error(QObject::tr("pa_context_client_info_list() failed").toUtf8().constData());
              return;
            }
            pa_operation_unref(o);
            break;
        }

        case PA_CONTEXT_FAILED:
            context = nullptr;
            return;

        case PA_CONTEXT_TERMINATED:
        default:
            qApp->quit();
            return;
    }
}

gboolean connect_to_pulse(gpointer userdata) {
    MainWindow *w = static_cast<MainWindow*>(userdata);

    if (context)
        return false;

    pa_proplist *proplist = pa_proplist_new();
    pa_proplist_sets(proplist, PA_PROP_APPLICATION_NAME, QObject::tr("Simple Sound Controller").toUtf8().constData());
    pa_proplist_sets(proplist, PA_PROP_APPLICATION_ID, "org.jmerle.sisoc");
    pa_proplist_sets(proplist, PA_PROP_APPLICATION_ICON_NAME, "audio-card");
    pa_proplist_sets(proplist, PA_PROP_APPLICATION_VERSION, VERSION);

    context = pa_context_new_with_proplist(api, nullptr, proplist);
    g_assert(context);

    pa_proplist_free(proplist);

    pa_context_set_state_callback(context, context_state_callback, w);

    if (pa_context_connect(context, nullptr, PA_CONTEXT_NOFAIL, nullptr) < 0) {
        if (pa_context_errno(context) == PA_ERR_INVALID) {
          // TODO display error
        }
    }

    return false;
}

pa_context* get_context(void) {
  return context;
}
