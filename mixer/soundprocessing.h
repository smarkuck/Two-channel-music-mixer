#ifndef SOUNDPROCESSING_H
#define SOUNDPROCESSING_H

#include <QThread>
#include <QCoreApplication>

#include <QAudioFormat>
#include <QAudioDecoder>
#include <QAudioBuffer>
#include <QAudioOutput>

#include <math.h>

class SoundProcessing : public QObject
{
    Q_OBJECT

private:
    struct memEQ {
        double xmem1, xmem2, ymem1, ymem2;
        double b0, b1, b2, a0, a1, a2;
    };

public:
    explicit SoundProcessing(QObject *parent = nullptr);
    ~SoundProcessing();
    bool abort;

    double processEQ(double sample, memEQ &eq);
    double processLow(double sample);
    double processMedium(double sample);
    double processHigh(double sample);

    void shelfFilter(double F0, double g, QString type, memEQ &eq);

private:
    QAudioDecoder *decoder;
    QAudioOutput *audioOutput;
    QIODevice *audioDevice;

    QByteArray *channel1;
    QByteArray *channel2;

    bool soundReady;
    bool isPlayed;
    bool isWhiteNoise;

    memEQ lowMemEq;
    memEQ medMemEq;
    memEQ medMemEq2;
    memEQ highMemEq;

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

#endif // SOUNDPROCESSING_H

