#include "musicmodel.h"
#include <QDir>
#include <QStandardPaths>
#include <iostream>

MusicModel::MusicModel(QObject* parent) : QAbstractListModel(parent)
{
    /* right now we scan for music before completely starting the app,
     * but really we should do it incrementally in another thread */
    scan();
    QHash<QByteArray, Album*>::const_iterator i = albums.constBegin();
    while (i != albums.constEnd()) {
        std::cout << i.value()->title.toString().toStdString() << std::endl;
        for (const Song* s : i.value()->songs) {
            std::cout << "\t" << s->title.toString().toStdString() << std::endl;
        }
        ++i;
    }
}

int MusicModel::rowCount(const QModelIndex &parent) const
{
    return songsList.count();
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
                return songsList.at(index.row())->title;
            case 1:
                return songsList.at(index.row())->artist;
            case 2:
                return songsList.at(index.row())->album;
            case 3:
                return songsList.at(index.row())->year;
            case 4:
                return songsList.at(index.row())->track;
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


void MusicModel::scan()
{
    /*
     * right now we just scan the default music folders on the user's OS.
     * in the future there should be a setting where the user can decide where
     * we scan for music.
     */
    QList<QString> musicFolders = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    for (const QString& musicFolder : musicFolders) {
        searchFolderRecursively(musicFolder);
    }
}

void MusicModel::searchFolderRecursively(const QString& absolutePath)
{
    QDir dir(absolutePath);
    QList<QString> nameFilters;
    nameFilters << "*.mp3" << "*.flac" << "*.ogg" << "*.m4a"; // TODO: autodetect what codecs we can play
    dir.setNameFilters(nameFilters);
    dir.setFilter(QDir::Files | QDir::Readable | QDir::NoSymLinks);
    QList<QString> relativePaths = dir.entryList();
    for (const QString& relativePath : relativePaths) {
        QString absolutePath = dir.absoluteFilePath(relativePath);
        std::cout << absolutePath.toStdString() << std::endl;

        try {
            Song* s = new Song(absolutePath);

            QByteArray songHash = s->getHashCode();

            if (!songs.contains(songHash)) {
                songs.insert(songHash, s);
                songsList.append(s);
            } else {
                delete s;
                s = songs.value(songHash);
            }

            Album* a = new Album(s);
            QByteArray albumHash = a->getHashCode();

            if (!albums.contains(albumHash)) {
                albums.insert(albumHash, a);
            } else {
                delete a;
                a = albums.value(albumHash);
            }

            a->addSong(s);
        } catch (const std::exception& e) {
            std::cerr << "Failed to read file " << absolutePath.toStdString() << std::endl;
            continue;
        }
    }

    // recursive search

    nameFilters.clear();
    dir.setNameFilters(nameFilters);
    dir.setFilter(QDir::Dirs | QDir::Readable | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QList<QString> subDirs = dir.entryList();
    for (const QString& subDir : subDirs) {
        searchFolderRecursively(dir.absoluteFilePath(subDir));
    }


}

Song* MusicModel::qModelIndexToSong(const QModelIndex &index)
{
    return songsList.at(index.row());
}
