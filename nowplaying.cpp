#include "nowplaying.h"

NowPlaying::NowPlaying(QWidget* parent) : QWidget(parent)
{
  layout = new QVBoxLayout(this);
  layout->setContentsMargins(0, 0, 0, 0);
  title = new QLabel;
  layout->addWidget(title);
  artistAlbum = new QLabel;
  layout->addWidget(artistAlbum);
  setInfo(nullptr);
}

NowPlaying::~NowPlaying()
{
}

void NowPlaying::setInfo(const Song* s)
{
  if (s == nullptr) {
    this->title->setText("Empty");
    this->artistAlbum->setText("");
  } else {
    this->title->setText(s->title.toString());
    this->artistAlbum->setText(s->artist.toString() + " - " + s->album.toString());
  }
}
