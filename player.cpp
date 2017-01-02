//
// Created by matt on 1/1/17.
//

#include <stdexcept>
#include <QtCore/QDir>
#include <iostream>
#include "player.h"

Player::Player() {
    vlcInstance = libvlc_new(0, nullptr);
    if (vlcInstance == nullptr) {
        throw std::runtime_error("Could not initialize libVLC");
    }

    vlcPlayer = libvlc_media_player_new(vlcInstance);
    if (vlcPlayer == nullptr) {
        throw std::runtime_error("Could not initialize libVLC media player");
    }

    eventMananager = libvlc_media_player_event_manager(vlcPlayer);
    libvlc_event_attach(eventMananager, libvlc_MediaPlayerEndReached, end_reached_cb, this);
}

Player::~Player() {
    libvlc_media_player_release(vlcPlayer);
    libvlc_release(vlcInstance);
}

void Player::openFile(QString path) {
    if (isPlaying()) {
        stop();
    }

    QString nativePath = QDir::toNativeSeparators(path);
    libvlc_media_t *vlcMedia = libvlc_media_new_path(vlcInstance, nativePath.toUtf8().constData());
    if (vlcMedia == nullptr) {
        throw std::runtime_error("libVLC could not open media");
    }

    libvlc_media_player_set_media(vlcPlayer, vlcMedia);

    libvlc_media_release(vlcMedia);
}

bool Player::isPlaying() {
    return libvlc_media_player_is_playing(vlcPlayer) == 1;
}

void Player::play() {
    libvlc_media_player_play(vlcPlayer);
}

void Player::stop() {
    libvlc_media_player_stop(vlcPlayer);
}

void Player::end_reached_cb(const struct libvlc_event_t *t, void *data) {
    Player *player = (Player *) data;
    player->endReached();
}
