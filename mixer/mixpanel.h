#ifndef MIXPANEL_H
#define MIXPANEL_H

#include <QObject>
#include <QAudioFormat>
#include <QAudioBuffer>
#include <QAudioDecoder>
#include "math.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include "qcustomplot.h"
#include "action.h"
#include <taglib/audioproperties.h>
#include <taglib/fileref.h>
#include "soundtouch/BPMDetect.h"

extern QReadWriteLock lock;

class MixPanel : public QObject
{
    Q_OBJECT

private:
    struct memEQ {
        double xmem1, xmem2, ymem1, ymem2;
        double b0, b1, b2, a0, a1, a2;
    };
    QAudioDecoder *decoder;
    bool isPlayed;
    bool isSingleLoop;
    bool isBPM;
    bool isDisc;
    double bpm;
    int  rewindConst;
    int  audioLengthInSec;
    int loopInterval;
    int loopStart;
    int actLoop;
    int discSamples;
    float prevDiscAngle;
    float discSpeed;
    double speed;
    qreal volume;
    memEQ lowMemEq[2];
    memEQ medMemEq[2];
    memEQ medMemEq2[2];
    memEQ highMemEq[2];
    double lowValue;
    double medValue;
    double highValue;

public:
    explicit MixPanel(QObject *parent = nullptr);
    ~MixPanel();

    bool plot;
    bool audioReady;
    bool isLoopStartSet;
    bool isLoopEndSet;
    bool isLoopingActive;
    bool isLoopingSet;
    bool flags[4];
    bool loadAudioInterruption;
    double rewindParam;
    double audioLength;

    qint64 loopingStart;
    qint64 loopingEnd;
    qint64 flagPos[4];
    qint64 duration;
    qint64 actPos;
    qreal realPosition;

    QByteArray *channel1;
    QByteArray *channel2;

    double processEQ(double sample, memEQ &eq);
    double processLowUp(double sample);
    double processLowDown(double sample);
    double processMediumUp(double sample);
    double processMediumDown(double sample);
    double processHighUp(double sample);
    double processHighDown(double sample);
    void process(double *buffer, int nFrames);
    void shelfFilter(double F0, double g, QString type, memEQ &eq);
    void detectBPM();
    void setLoop(int loop);
    void setFlag(int flag);
    void unsetFlag(int flag);

signals:
    void timeChange(QString time);
    void writeToFile(quint64 type, quint64 position, quint64 value);
    void fileReady();
    void pause();

public slots:
    void playPause();
    void playStop();
    void playLoop();
    void playLoopingSet();
    void playLoopingStart();
    void playLoopingEnd();

    void getDiscSpeed(float angle);
    void enableDisc();
    void disableDisc();

    void setFlag1();
    void setFlag2();
    void setFlag3();
    void setFlag4();

    void unsetFlag1();
    void unsetFlag2();
    void unsetFlag3();
    void unsetFlag4();

    void setLoop1_16();
    void setLoop1_8();
    void setLoop1_4();
    void setLoop1_2();
    void setLoop1();
    void setLoop2();

    void loadAudio(QString filename);
    void readBuffer();
    void finishDecoding();

    void lowEQ(int value);
    void medEQ(int value);
    void highEQ(int value);

    void speedChange(int value);
    void volumeChange(int value);
};

#endif // MIXPANEL_H
