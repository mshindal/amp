#include "player.h"
#include <QFile>
#include <iostream>

Player::Player(QString path) {
    std::cout << "player created" << std::endl;
    GMainLoop *loop;
    GstElement *playbin;
    GstBus *bus;
    QString uri = "file:///" + path;

    playbin = gst_element_factory_make ("playbin", "playbin");
    g_object_set (G_OBJECT (playbin), "uri", uri.toStdString().data(), NULL);

    bus = gst_pipeline_get_bus(GST_PIPELINE(playbin));
    gst_bus_add_watch(bus, bus_cb, NULL);
    gst_object_unref(bus);

    gst_element_set_state (playbin, GST_STATE_PLAYING);

    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

}

gboolean Player::bus_cb(GstBus *bus, GstMessage *msg, gpointer data) {
    std::cout << "callback called" << std::endl;
    switch (GST_MESSAGE_TYPE(msg)) {
        case GST_MESSAGE_EOS:
            std::cout << "eos reached" << std::endl;
            break;
    }
}
