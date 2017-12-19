#include "soundprocessing.h"
//============================================================
SoundProcessing::SoundProcessing(QObject *parent) : QObject(parent)
{
    abort = false;
    rate = 1;
    written = 64*sizeof(qint16)*2;
    crossFader = 50;

    QAudioFormat format;
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleRate(48000);
    format.setSampleSize(16);

    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    audioDevice = audioOutput->start();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));
    timer->start(1);
}
//------------------------------------------------------------
void SoundProcessing::play() {

    if(abort) timer->stop();
    if(!timer->isActive()) return;

//    int space = written/sizeof(qint16)/2;

//    for(int i = 64-space; i < 64; i++) {
//        if(i-space<0) continue;
//        buffer1[i*2-space*2] = buffer1[i*2];
//        buffer1[i*2+1-space*2] = buffer1[i*2+1];
//        buffer2[i*2-space*2] = buffer2[i*2];
//        buffer2[i*2+1-space*2] = buffer2[i*2+1];
//    }

    QByteArray output;

    //panel1.process(buffer1+(64-space)*2, space);
    //panel2.process(buffer2+(64-space)*2, space);

    panel1.process(buffer1, 64);
    panel2.process(buffer2, 64);

    for(int i = 0; i < 128; i++) {
        rate += 0.0000001;
        if(rate > 1) rate = 1;

        if(crossFader <= 50)
            buffer2[i] *= crossFader/50.;
        else
            buffer1[i] *= 1-(crossFader - 50)/50.;

        double y = buffer1[i] + buffer2[i];

        if(abs(y)*rate > 30000) {
            rate = abs(30000/y);
        }

        qint16 sample = y*rate;
        output.append(reinterpret_cast<char*>(&sample), sizeof(qint16));
    }

    //written = audioDevice->write(output);
    written = 0;
    while((written += audioDevice->write(output.right(output.size()-written))) < output.size());
}
