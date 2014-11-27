#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_main.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
  
  public:
    MainWindow(QMainWindow *parent = 0);
    
  private:
    Ui::MainWindow ui;
    
  private slots:
    void on_ActionQuit_triggered();
};

#endif // MAINWINDOW_H
