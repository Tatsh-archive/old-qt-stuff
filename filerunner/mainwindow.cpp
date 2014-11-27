#include <QtGui>

#include "mainwindow.h"

/**
 * Constructor.
 */
MainWindow::MainWindow(QMainWindow *parent) : QMainWindow(parent) {
  ui.setupUi(this);
  QStringList headers = QStringList() << tr("Name") << tr("Size") << tr("Type") << tr("Date");
  ui.hostTree->setHeaderLabels(headers);
  ui.hostTree->setRootIsDecorated(false);
  ui.remoteTree->setHeaderLabels(headers);
  ui.remoteTree->setRootIsDecorated(false);
  
  ftp = new QFtp();
  
  connect(ftp, SIGNAL(listInfo(QUrlInfo)), this, SLOT(appendRemoteDirectoryList(QUrlInfo)));
  connect(ftp, SIGNAL(commandStarted(int)), this, SLOT(remoteCommandStarted(int)));
  connect(ftp, SIGNAL(commandFinished(int, bool)), this, SLOT(remoteCommandFinished(int, bool)));
  connect(ftp, SIGNAL(readyRead()), this, SLOT(downloadFile()));
  
  connect(ui.remoteTree, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(remoteTreeItemDblClick(const QModelIndex)));
}

/**
 * Handles close event.
 */
void MainWindow::closeEvent(QCloseEvent *event) {
  QMainWindow::closeEvent(event);
}

/**
 * Handles connect event from menu.
 */
void MainWindow::on_action_Connect_triggered() {
  ui.remotePath->setEditable(false);
  
  QString username = "asim";
  QString password = "finalsunday4";
  ftp->connectToHost("dedi152.xirvik.com");
  ftp->login(username, password);
  ftp->list();
  
  ui.remotePath->setEditText("/");
  ui.remotePath->setEditable(true);
}

void MainWindow::appendRemoteDirectoryList(const QUrlInfo &i) {
  QTreeWidgetItem *item = new QTreeWidgetItem;
  item->setText(0, i.name());
  item->setText(1, QString::number(i.size()));
  item->setText(2, "file type");
  item->setText(3, i.lastModified().toString("yyyy-mm-dd hh:mm"));
  
  ui.remoteTree->addTopLevelItem(item);
  
  if (!ui.remoteTree->currentItem()) {
    ui.remoteTree->setCurrentItem(ui.remoteTree->topLevelItem(0));
    ui.remoteTree->setEnabled(true);
  }
}

void MainWindow::remoteCommandStarted(int id) {
  switch (id) {
    case QFtp::ConnectToHost:
      ui.remoteStatus->appendPlainText(tr("Connecting..."));
      break;
    
    case QFtp::Login:
      ui.remoteStatus->appendPlainText(tr("Logging in..."));
      break;
      
    case QFtp::List:
      ui.remoteStatus->appendPlainText(tr("Listing directory ..."));
      break;
      
    case QFtp::Get:
      ui.remoteStatus->appendPlainText(tr("get() executing ..."));
      break;
      
    default:
      break;
  }
}

void MainWindow::remoteCommandFinished(int id, bool error) {
  if (error) {
    ui.remoteStatus->appendPlainText(tr("Error!"));
    switch (id) {
      case QFtp::HostNotFound:
        ui.remoteStatus->appendPlainText(tr("Host not found."));
        break;
        
      case QFtp::ConnectionRefused:
        ui.remoteStatus->appendPlainText(tr("Connection was refused."));
        break;
        
      case QFtp::NotConnected:
        ui.remoteStatus->appendPlainText(tr("Not connected to a server."));
        break;
        
      case QFtp::UnknownError:
      default:
        ui.remoteStatus->appendPlainText(tr("Unknown error: %1. %2").arg(error).arg(ftp->errorString());
        break;
    }
    
    return;
  }
  
  switch (id) {
    case QFtp::ConnectToHost:
      ui.remoteStatus->appendPlainText(tr("Connection successful."));
      break;
      
    case QFtp::Login:
      ui.remoteStatus->appendPlainText(tr("Login successful."));
      break;
      
    case QFtp::List:
      ui.remoteStatus->appendPlainText(tr("List successful."));
      break;
      
    case QFtp::Get:
      ui.remoteStatus->appendPlainText(tr("Get successful."));
      break;

    case QFtp::None:
    default:
      break;
  }
}

void MainWindow::remoteTreeItemDblClick(const QModelIndex &index) {
  QString filename = ui.remoteTree->currentItem()->text(0);
  QFile *file = new QFile(filename);
  
  if (!file->open(QIODevice::WriteOnly)) {
    ui.remoteStatus->appendPlainText(tr("Unable to save file %1.").arg(filename));
    return;
  }
  
  ftp->get(filename, file);
}
