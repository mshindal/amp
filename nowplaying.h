#ifndef NOWPLAYING_H
#define NOWPLAYING_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include "song.h"

class NowPlaying : public QWidget
{
  Q_OBJECT

  public:
    NowPlaying(QWidget* parent = nullptr);
    ~NowPlaying();
  private:
    QLabel* title;
    QLabel* artistAlbum;
    QVBoxLayout* layout;
  public slots:
    void setInfo(const Song* s);
};

#endif // NOWPLAYING_H
