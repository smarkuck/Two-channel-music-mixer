#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>

#include "soundprocessing.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); 
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    SoundProcessing* soundProc;
    QThread th_soundProc;

signals:
    void loadAudio(QString filename);
    void loadAudio2(QString filename);

public slots:
    void selectAudio();
    void selectAudio2();
    void crossFaderChange(int value);
};

#endif // MAINWINDOW_H
