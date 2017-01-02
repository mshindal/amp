#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QObject>
#include <QMediaPlayer>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>
#include "musicmodel.h"
#include "nowplaying.h"
#include "player.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QWidget *centralWidget;
    QTreeView *treeView;
    MusicModel *model;
    Player* player;
    QSlider *slider;
    QVBoxLayout *layout;
    NowPlaying *nowPlaying;
    const Song *currentSong;
    QModelIndex currentIndex;
private slots:
    void playSong(QModelIndex index);
    void playNext();
    void songPositionChanged(qint64 position);
    void sliderPositionChanged(int newValue);
    void playerStateChanged(QMediaPlayer::State state);
};

#endif // MAINWINDOW_H
