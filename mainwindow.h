#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QObject>
#include "musicmodel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QTreeView* treeView;
    MusicModel* model;
private slots:
    void playSong(QModelIndex index);
};

#endif // MAINWINDOW_H
