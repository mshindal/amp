//
// Created by matt on 1/1/17.
//

#include <stdexcept>
#include "player.h"

Player::Player() {
    vlcInstance = libvlc_new(0, NULL);
    if (vlcInstance == NULL) {
        throw std::runtime_error("Could not initialize libVLC");
    }
}

Player::~Player() {
    if (vlcInstance) {
        libvlc_release(vlcInstance);
    }
}

void Player::openFile(QString path) {
    if (vlcPlayer && libvlc_media_player_is_playing(vlcPlayer)) {
        stop();
    }

    // TODO: might want to convert the path to a C-string in a different way
    libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance, path.toUtf8().constData());

    if (!vlcMedia) {
        throw std::runtime_error("libVLC could not open media");
    }

    vlcPlayer = libvlc_media_player_new_from_media(vlcMedia);
    libvlc_media_release(vlcMedia);
}

void Player::play() {
    if (!vlcPlayer) {
        return;
    }

    libvlc_media_player_play(vlcPlayer);
}

void Player::stop() {
    if (vlcPlayer) {
        libvlc_media_player_stop(vlcPlayer);
        libvlc_media_player_release(vlcPlayer);
        vlcPlayer = NULL;
    }
}
