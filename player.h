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
    void setPosition(float position);
private:
    libvlc_instance_t *vlcInstance = nullptr;
    libvlc_media_player_t *vlcPlayer = nullptr;
    libvlc_event_manager_t *eventMananager;
    static void callback(const struct libvlc_event_t *event, void *data);
    bool isPlaying();
signals:
    void endReached();
    void positionChanged(float newPosition);
};


#endif //AMP_PLAYER_H
