#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAudioFormat>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QAudioOutput>

#include <QFileDialog>

#include <QThread>

#include "fft.h"
#include <math.h>

namespace Ui {

class MainWindow;
}

class SoundProcessing : public QObject
{
    Q_OBJECT

public:
    void init();
    ~SoundProcessing();
    bool abort;

private:
    QAudioDecoder *decoder;
    QAudioOutput *audioOutput;
    QIODevice *audioDevice;

    QByteArray *channel1;
    QByteArray *channel2;

    bool soundReady;
    bool isPlayed;
    bool isWhiteNoise;

    double xmem1, xmem2, ymem1, ymem2;
    double b0, b1, b2, a0, a1, a2;
    double F0, BW, g;

public slots:
    void loadAudio(QString filename);
    void readBuffer();
    void finishDecoding();
    void play();
    void enableWhiteNoise();
    void disableWhiteNoise();

    void lowEQ(int value);
    void medEQ(int value);
    void highEQ(int value);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QThread th_soundProc;

public:
    explicit MainWindow(QWidget *parent = 0); 
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    SoundProcessing* soundProc;

signals:
    void loadAudio(QString filename);

public slots:
    void selectAudio();
};

#endif // MAINWINDOW_H
