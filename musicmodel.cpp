#include "musicmodel.h"
#include <QDir>
#include <QStandardPaths>
#include <iostream>

MusicModel::MusicModel(QObject* parent) : QAbstractListModel(parent)
{
  scanner = new Scanner();
  connect(scanner, SIGNAL(songFound(Song)), this, SLOT(addSong(Song)));
  scanner->start();
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
  return songs.count();
}

int MusicModel::columnCount(const QModelIndex &parent) const
{
  return 5;
}

QVariant MusicModel::data(const QModelIndex &index, int role) const
{
  if (role == Qt::DisplayRole) {
    switch (index.column()) {
    case 0:
      return songs.at(index.row()).title;
    case 1:
      return songs.at(index.row()).artist;
    case 2:
      return songs.at(index.row()).album;
    case 3:
      return songs.at(index.row()).year;
    case 4:
      return songs.at(index.row()).trackNum;
    }
  }

  return QVariant();
}

QVariant MusicModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role == Qt::DisplayRole)
  {
    if (orientation == Qt::Horizontal) {
      switch (section) {
      case 0:
        return "Title";
      case 1:
        return "Artist";
      case 2:
        return "Album";
      case 3:
        return "Year";
      case 4:
        return "Track No";
      }
    }
  }

  return QVariant();
}

const Song* MusicModel::qModelIndexToSong(const QModelIndex &index)
{
  return &songs.at(index.row());
}

void MusicModel::addSong(Song s)
{
  beginInsertRows(QModelIndex(), songs.count(), songs.count());
  songs.append(s);
  endInsertRows();
}
