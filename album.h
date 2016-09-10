#ifndef ALBUM_H
#define ALBUM_H

#include "treenode.h"
#include <QMap>
#include <QByteArray>
#include "song.h"

class Album : public TreeNode
{
  public:
    Album(Song* s);
    void addSong(Song* s);
    QByteArray getHashCode();
    QMap <int, Song*> songs;
};

#endif // ALBUM_H
