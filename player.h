//
// Created by Matt on 12/28/2016.
//

#ifndef AMP_PLAYER_H
#define AMP_PLAYER_H

#include <QString>
#include <gst/gst.h>

class Player {
public:
    Player(QString path);
private:
    static gboolean bus_cb(GstBus *bus, GstMessage *msg, gpointer data);
};


#endif //AMP_PLAYER_H
