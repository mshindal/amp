#include "scanner.h"
#include <iostream>
#include <QStandardPaths>
#include <QDir>

Scanner::Scanner()
{

}

void Scanner::run() {
  /*
   * right now we just scan the default music folders on the user's OS.
   * in the future there should be a setting where the user can decide where
   * we scan for music.
  */
  QList<QString> musicFolders = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
  for (const QString& musicFolder : musicFolders) {
    std::cout << musicFolder.toStdString() << std::endl;
    searchFolderRecursively(musicFolder);
  }
}

void Scanner::searchFolderRecursively(QString absolutePath) {
  QDir dir(absolutePath);
  QList<QString> nameFilters;
  nameFilters << "*.mp3" << "*.flac" << "*.ogg" << "*.m4a"; // TODO: autodetect what codecs we can play
  dir.setNameFilters(nameFilters);
  dir.setFilter(QDir::Files | QDir::Readable | QDir::NoSymLinks);
  QList<QString> relativePaths = dir.entryList();
  for (const QString& relativePath : relativePaths) {
    QString absolutePath = dir.absoluteFilePath(relativePath);
    try {
      Song s(absolutePath);
      emit songFound(s);
    } catch (std::runtime_error& e) {
      std::cerr << absolutePath.toStdString() << ": " << e.what() << std::endl;
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
