#include <QtGui>

#include "mainwindow.h"

/**
 * Constructor.
 */
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
  ui.setupUi(this);
}

/**
 * Handles quit event from menu.
 *
 * @param $f - Array with the following keys:\n
 *  - The item 0.\n
 *  - The item 1.
 */
void MainWindow::on_ActionQuit_triggered() {
  int ret = QMessageBox::warning(this, "MainWindow", tr("Are you sure you wish to quit?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
  if (ret == QMessageBox::Yes) {
    close();
  }
}
