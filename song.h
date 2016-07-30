#ifndef SONG_H
#define SONG_H
#include "treenode.h"

class Song : public TreeNode
{
public:
    Song(const QString& path);
    QByteArray getHashCode();
private:
    void readTags();
};

#endif // SONG_H
