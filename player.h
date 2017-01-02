//
// Created by matt on 1/1/17.
//

#ifndef AMP_PLAYER_H
#define AMP_PLAYER_H

#include <vlc/vlc.h>
#include <QObject>

class Player : public QObject {
    Q_OBJECT
public:
    Player();
    ~Player();
public slots:
    void openFile(QString path);
    void play();
    void stop();
private:
    libvlc_instance_t *vlcInstance = nullptr;
    libvlc_media_player_t *vlcPlayer = nullptr;
    libvlc_event_manager_t *eventMananager;
    static void end_reached_cb(const struct libvlc_event_t *t, void *data);
    bool isPlaying();
signals:
    void endReached();
};


#endif //AMP_PLAYER_H
