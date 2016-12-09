#ifndef MUSICMODEL_H
#define MUSICMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QByteArray>
#include <QList>
#include "scanner.h"
#include "song.h"

class MusicModel : public QAbstractListModel {
Q_OBJECT
public:
    MusicModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    const Song *qModelIndexToSong(const QModelIndex &index);

private:
    QList<Song> songs;
    Scanner *scanner;
private slots:

    void addSong(Song s);
};

#endif // MUSICMODEL_H
