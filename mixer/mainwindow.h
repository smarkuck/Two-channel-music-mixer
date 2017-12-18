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

    double processLow(double sample);
    double processMedium(double sample);
    double processHigh(double sample);

private:
    QAudioDecoder *decoder;
    QAudioOutput *audioOutput;
    QIODevice *audioDevice;

    QByteArray *channel1;
    QByteArray *channel2;

    bool soundReady;
    bool isPlayed;
    bool isWhiteNoise;

    double lxmem1, lxmem2, lymem1, lymem2;
    double mxmem1, mxmem2, mymem1, mymem2;
    double m2xmem1, m2xmem2, m2ymem1, m2ymem2;
    double hxmem1, hxmem2, hymem1, hymem2;

    double lb0, lb1, lb2, la0, la1, la2;
    double mb0, mb1, mb2, ma0, ma1, ma2;
    double m2b0, m2b1, m2b2, m2a0, m2a1, m2a2;
    double hb0, hb1, hb2, ha0, ha1, ha2;

    double lg, mg, hg;

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
