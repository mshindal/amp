#include "mainwindow.h"
#include "song.h"
#include <iostream>

// how many "steps" the slider has; e.g. it ranges from 0 to this number
#define SLIDER_RESOLUTION 10000

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  layout = new QVBoxLayout(centralWidget);

  treeView = new QTreeView;
  layout->addWidget(treeView);

  nowPlaying = new NowPlaying;
  layout->addWidget(nowPlaying);

  slider = new QSlider(Qt::Horizontal);
  slider->setDisabled(true);
  slider->setRange(0, SLIDER_RESOLUTION);
  layout->addWidget(slider);

  model = new MusicModel(treeView);
  treeView->setModel(model);

  player = new QMediaPlayer(this);
  // a lower interval uses more CPU, but makes the slider smoother. 
  player->setNotifyInterval(10);

  connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playSong(QModelIndex)));
  connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(songPositionChanged(qint64)));
  connect(player, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(playerStateChanged(QMediaPlayer::State)));
  connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderPositionChanged(int)));

  this->setMinimumHeight(600);
  this->setMinimumWidth(800);
}

MainWindow::~MainWindow()
{
}

void MainWindow::playSong(QModelIndex index)
{
  player->stop();
  currentSong = model->qModelIndexToSong(index);
  player->setMedia(QUrl::fromLocalFile(currentSong->path));
  player->play();
}

void MainWindow::songPositionChanged(qint64 position)
{
  // don't change the position of the slider while the user is adjusting it
  if (!slider->isSliderDown()) {
    float relativePosition = ((float) position / (float) player->duration()) * SLIDER_RESOLUTION;
    slider->setValue(relativePosition);
  }
}

void MainWindow::sliderPositionChanged(int newValue)
{
  qint64 relativePosition = ((float) newValue / SLIDER_RESOLUTION) * (float) player->duration();
  player->setPosition(relativePosition);
}

void MainWindow::playerStateChanged(QMediaPlayer::State state)
{
  switch (state) {
    case QMediaPlayer::StoppedState:
      slider->setDisabled(true);
      currentSong = nullptr;
      nowPlaying->setInfo(nullptr);
      break;
    case QMediaPlayer::PlayingState:
      slider->setDisabled(false);
      nowPlaying->setInfo(currentSong);
      break;
    case QMediaPlayer::PausedState:
      break;
    default:
      break;
  }
}
