#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QList>
#include "song.h"
#include "album.h"
#include "artist.h"

class MusicModel : public QAbstractListModel
{
    Q_OBJECT
public:
    MusicModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void scan();
    Song* qModelIndexToSong(const QModelIndex &index);
private:
    void searchFolderRecursively(const QString& absolutePath);
    QList <Song*> songsList;
    QHash <QByteArray, Song*> songs;
    QHash <QByteArray, Album*> albums;
};

#endif // MUSICMODEL_H
