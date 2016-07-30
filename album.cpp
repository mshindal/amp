#include "album.h"
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDir>

Album::Album(Song* s)
{
    QFileInfo fileInfo(s->path);
    this->path = fileInfo.absoluteDir().path();
    this->title = s->album;
    this->artist = s->artist;
    this->album = this->title;
    this->track = "N/A";
    this->year = s->year;
    addSong(s);
}

QByteArray Album::getHashCode()
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    crypto.addData(title.toByteArray());
    crypto.addData(artist.toByteArray());
    crypto.addData(year.toByteArray());
    return crypto.result();
}

void Album::addSong(Song *s)
{
    songs.insert(s->track.toInt(), s);\
    this->children.append(s);
    s->parent = this;
}
