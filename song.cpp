#include "song.h"
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/tstring.h>
#include <QFile>
#include <QCryptographicHash>
#include <QByteArray>

Song::Song(const QString& path)
{
    this->path = path;
    readTags();
}

void Song::readTags()
{
#if defined(_WIN32) || defined(_WIN64)
    // http://stackoverflow.com/questions/5642251/taglib-how-to-handle-utf-8-encoded-file-paths
    TagLib::FileRef f(reinterpret_cast<const wchar_t*> (path.constData()));
#else
    QByteArray bytes = QFile::encodeName(path);
    TagLib::FileRef f(bytes.constData());
#endif
    TagLib::Tag *tag = f.tag();
    if (!f.isNull() && f.tag())
    {
        title = TStringToQString(tag->title());
        artist = TStringToQString(tag->artist());
        album = TStringToQString(tag->album());
        track = tag->track();
        year = tag->year();
    } else {
        throw std::exception();
    }
}

QByteArray Song::getHashCode()
{
    QCryptographicHash crypto(QCryptographicHash::Md5);
    crypto.addData(title.toByteArray());
    crypto.addData(artist.toByteArray());
    crypto.addData(album.toByteArray());
    crypto.addData(track.toByteArray());
    crypto.addData(year.toByteArray());
    return crypto.result();
}