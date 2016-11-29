#ifndef ALBUM_H
#define ALBUM_H

#include <QMultiMap>
#include <QByteArray>
#include <QVariant>
#include "song.h"

class Album
{
  public:
    Album(QVariant title, QVariant artist, QVariant year);
    QByteArray getHashCode();
    QVariant title;
    QVariant artist;
    QVariant year;
    QMultiMap <int, Song*> songs;
};

#endif // ALBUM_H
