#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAudioFormat>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QAudioOutput>

#include <QFileDialog>

#include <QThread>

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

public slots:
    void loadAudio(QString filename);
    void readBuffer();
    void finishDecoding();
    void play();
    void enableWhiteNoise();
    void disableWhiteNoise();
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
