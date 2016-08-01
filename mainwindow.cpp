#include "mainwindow.h"
#include "song.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    treeView = new QTreeView(this);
    model = new MusicModel(treeView);
    player = new QMediaPlayer(this);
    treeView->setModel(model);
    setCentralWidget(treeView);
    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playSong(QModelIndex)));
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
