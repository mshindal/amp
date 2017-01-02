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
    libvlc_instance_t *vlcInstance = NULL;
    libvlc_media_player_t *vlcPlayer = NULL;
};


#endif //AMP_PLAYER_H
