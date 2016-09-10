#include "mainwindow.h"
#include "song.h"
#include <iostream>

// how many "steps" the slider has; e.g. it ranges from 0 to this number
#define SLIDER_RESOLUTION 10000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    layout = new QVBoxLayout(this);
    treeView = new QTreeView(this);
    layout->addWidget(treeView);
    slider = new QSlider(Qt::Horizontal, this);
    slider->setDisabled(true);
    slider->setRange(0, SLIDER_RESOLUTION);
    layout->addWidget(slider);

    centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

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
    // no need to call `delete` on the treeView or the model, since Qt's Object Hierarchy takes care of it
}

void MainWindow::playSong(QModelIndex index)
{
    Song* s = model->qModelIndexToSong(index);
    if (player->PlayingState == QMediaPlayer::PlayingState) {
        player->stop();
    }
    player->setMedia(QUrl::fromLocalFile(s->path));
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
      break;
    case QMediaPlayer::PlayingState:
    case QMediaPlayer::PausedState:
    default:
      slider->setDisabled(false);
  }
}
