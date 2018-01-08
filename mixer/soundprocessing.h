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
    bool abort;

    int crossFader;

    MixPanel panel1;
    MixPanel panel2;

    Action action;

    enum Actions { low=1, med, high, cross };
    void doActions(quint64 actPos1, quint64 actPos2);

    double buffer1[1024], buffer2[1024];

    QByteArray output1;
    QAudioFormat format;
private:
    QAudioOutput *audioOutput;
    QIODevice *audioDevice;

    QTimer* timer;

    double rate;

signals:
    void lowEQChange(int value);
    void medEQChange(int value);
    void highEQChange(int value);
    void lowEQChange2(int value);
    void medEQChange2(int value);
    void highEQChange2(int value);
    void crossChange(int value);
    void crossChange2(int value);


public slots:
    void play();

};

#endif // SOUNDPROCESSING_H

