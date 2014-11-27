#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFtp>

#include "ui_main.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  
  public:
    MainWindow(QMainWindow *parent = 0);
    
    QFtp *ftp;
    
  private:
    Ui::MainWindow ui;
    
  private slots:
    void closeEvent(QCloseEvent *event);
    void appendRemoteDirectoryList(const QUrlInfo &i);
    void remoteCommandStarted(int id);
    void remoteCommandFinished(int id, bool error);
    void remoteTreeItemDblClick(const QModelIndex &index);
    void downloadFile();
    
    void on_action_Connect_triggered();
};

#endif // MAINWINDOW_H
