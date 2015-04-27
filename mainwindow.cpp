#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("SimpleTE - Simple Text Editor BETA");
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,
                                    Qt::AlignCenter,
                                    window()->size(),
                                    qApp->desktop()->availableGeometry()));
    fileName = "untitled";
    statFilename = new QLabel(fileName);
    ui->statusBar->addPermanentWidget(statFilename);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    fileName = "untitled";
    ui->textEdit->clear();
    statFilename->setText(fileName);
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileOpen = QFileDialog::getOpenFileName(this,
                                                    "Open File",
                                                    QString(),
                                                    "Text File (*.txt)");
    if(!fileOpen.isEmpty()){
        QFile file(fileOpen);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,
                                  "Error",
                                  "Couldn't open file");
            return;
        }
        fileName = fileOpen;
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
        statFilename->setText(fileName);
    }
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(fileName);
    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    out.flush();
    file.close();
}

void MainWindow::on_actionSave_as_triggered()
{
    QString fileSave = QFileDialog::getSaveFileName(this,
                                                    "Save as",
                                                    QString(),
                                                    "Text File (*txt)");
    if(!fileSave.isEmpty()){
        QFile file(fileSave + ".txt");
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this,
                                  "Error",
                                  "Permission denied / read-only directory");
        }
        on_actionSave_triggered();
        statFilename->setText(fileName);
    }
}

void MainWindow::on_actionQuit_triggered()
{
    QMessageBox::StandardButtons reply;
    reply = QMessageBox::question(this,
                          "Quit",
                          "Do you want to quit?<br>Make sure you have save your work.",
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
        qApp->quit();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
    ui->statusBar->showMessage("Undo",500);
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
    ui->statusBar->showMessage("Redo",500);
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
    ui->statusBar->showMessage("Cut",500);
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
    ui->statusBar->showMessage("Copy",500);
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
    ui->statusBar->showMessage("Paste",500);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *aboutDialog = new AboutDialog;
    aboutDialog->exec();
}
