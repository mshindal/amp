#include <iostream>
#include "mainwindow.h"

// how many "steps" the slider has; e.g. it ranges from 0 to this number
#define SLIDER_RESOLUTION 10000

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    treeView = new QTreeView;
    layout->addWidget(treeView);

    nowPlaying = new NowPlaying;
    layout->addWidget(nowPlaying);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, SLIDER_RESOLUTION);
    layout->addWidget(slider);

    model = new MusicModel(treeView);
    treeView->setModel(model);
    treeView->setColumnWidth(0, 350);

    try {
        player = new Player();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    connect(treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(playSong(QModelIndex)));
    connect(player, SIGNAL(endReached()), this, SLOT(playNext()));
    connect(player, SIGNAL(positionChanged(float)), this, SLOT(songPositionChanged(float)));
    connect(slider, SIGNAL(sliderMoved(int)), this, SLOT(sliderPositionChanged(int)));

    this->setMinimumHeight(600);
    this->setMinimumWidth(800);
}

MainWindow::~MainWindow() {
    delete player;
}

void MainWindow::playSong(QModelIndex index) {
    if (!index.isValid()) {
        currentIndex = QModelIndex();
        currentSong = nullptr;
        nowPlaying->setInfo(nullptr);
        return;
    }
    currentIndex = index;
    currentSong = model->qModelIndexToSong(index);
    try {
        player->openFile(currentSong->path);
        player->play();
        nowPlaying->setInfo(currentSong);
    } catch (std::exception& e) {
        std::cerr << currentSong->path.toStdString() << ": " << e.what() << std::endl;
    }
}

void MainWindow::songPositionChanged(float newPosition) {
    // don't change the position of the slider while the user is adjusting it
    if (!slider->isSliderDown()) {
        slider->setValue(newPosition * SLIDER_RESOLUTION);
    }
}

void MainWindow::sliderPositionChanged(int newPosition) {
    player->setPosition((float) newPosition / SLIDER_RESOLUTION);
}

void MainWindow::playNext() {
    QModelIndex nextIndex = model->index(currentIndex.row() + 1, 0);
    playSong(nextIndex);
}
