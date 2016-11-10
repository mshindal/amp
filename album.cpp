#include "album.h"
#include <QCryptographicHash>

Album::Album(QVariant title, QVariant artist, QVariant year)
{
  this->title = title;
  this->artist = artist;
  this->year = year;
}

QByteArray Album::getHashCode()
{
  QCryptographicHash crypto(QCryptographicHash::Md5);
  crypto.addData(title.toByteArray());
  crypto.addData(artist.toByteArray());
  crypto.addData(year.toByteArray());
  return crypto.result();
}

