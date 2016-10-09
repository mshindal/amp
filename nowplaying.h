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
    void setInfo(Song* s);
};
