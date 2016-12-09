#ifndef SONG_H
#define SONG_H

#include <QString>
#include <QVariant>

class Song {

public:
    Song();

    Song(QString path);

    QByteArray getHashCode();

    QString path;
    QVariant title;
    QVariant artist;
    QVariant album;
    QVariant trackNum;
    QVariant year;
};

Q_DECLARE_METATYPE(Song);

#endif // SONG_H
