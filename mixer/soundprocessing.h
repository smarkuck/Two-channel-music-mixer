#ifndef SOUNDPROCESSING_H
#define SOUNDPROCESSING_H

#include <QObject>
#include <QThread>
#include <QCoreApplication>

#include <QTimer>

#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioOutput>
#include <mixpanel.h>
#include <action.h>

class SoundProcessing : public QObject
{
    Q_OBJECT
    Q_ENUMS(Actions)

public:
    explicit SoundProcessing(QObject *parent = nullptr); 
    enum Actions { low=1, med, high, cross, volume, tempo };
    MixPanel panel1;
    MixPanel panel2;
    Action action;
    QByteArray output1;
    QAudioFormat format;
    QTimer* timer;
    int crossFader;

    void launchActions(quint64 actPos1, quint64 actPos2);

private:
    QAudioOutput *audioOutput;
    QIODevice *audioDevice;
    bool isRecording;
    double rate;
    double buffer1[960], buffer2[960];

signals:
    void lowEQChange(int value);
    void medEQChange(int value);
    void highEQChange(int value);
    void lowEQChange2(int value);
    void medEQChange2(int value);
    void highEQChange2(int value);
    void crossChange(int value);
    void crossChange2(int value);
    void volumeChange(int value);
    void volumeChange2(int value);
    void tempoChange(int value);
    void tempoChange2(int value);

public slots:
    void play();
    void record();

};

#endif // SOUNDPROCESSING_H

