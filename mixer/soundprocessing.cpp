#include "soundprocessing.h"
//============================================================
SoundProcessing::SoundProcessing(QObject *parent) : QObject(parent)
{
    abort = false;

    isWhiteNoise = false;
    soundReady = false;
    isPlayed = false;

    channel1 = new QByteArray();
    channel2 = new QByteArray();

    QAudioFormat desiredFormat;
    desiredFormat.setChannelCount(2);
    desiredFormat.setCodec("audio/pcm");
    desiredFormat.setSampleType(QAudioFormat::SignedInt);
    desiredFormat.setSampleRate(48000);
    desiredFormat.setSampleSize(16);

    decoder = new QAudioDecoder;
    decoder->setAudioFormat(desiredFormat);

    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    connect(decoder, SIGNAL(finished()), this, SLOT(finishDecoding()));

    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), desiredFormat);
    audioDevice = audioOutput->start();

    memset(&lowMemEq, 0, sizeof(memEQ));
    memset(&medMemEq, 0, sizeof(memEQ));
    memset(&medMemEq2, 0, sizeof(memEQ));
    memset(&highMemEq, 0, sizeof(memEQ));

    lowEQ(50);
    medEQ(50);
    highEQ(50);
}
//------------------------------------------------------------
void SoundProcessing::play() {

    if(!soundReady || isPlayed) return;

    isPlayed = true;
    double rate = 1;

    for(unsigned int i= 0; i < channel1->size()/sizeof(qint16) && !abort && isPlayed; i+=16) {
        QByteArray sample;

        for(int j = 0; j < 16; j++) {
            rate += 0.0000001;
            if(rate > 1) rate = 1;
            qint16 value = *(reinterpret_cast<qint16*>(channel1->data())+i+j);

            double y = processLow(value);
            y = processMedium(y);
            y = processHigh(y);

            if(y*rate > 30000 || y*rate < -30000) {
                rate = abs(30000/y);
            }
            value = y*rate;

            sample.append(reinterpret_cast<const char*>(&value), sizeof(qint16));

            value = *(reinterpret_cast<qint16*>(channel2->data())+i+j);

            y = processLow(value);
            y = processMedium(y);
            y = processHigh(y);

            if(y*rate > 30000 || y*rate < -30000) {
                rate = abs(30000/y);
            }

            value = y*rate;

            sample.append(reinterpret_cast<const char*>(&value), sizeof(qint16));
        }


        if(isWhiteNoise) {
            qint16 *data = reinterpret_cast<qint16*>(sample.data());

            for(unsigned int j = 0; j < sample.size()/sizeof(qint16); j++) {
                data[j] = rand();
            }
        }

        qint64 written = 0;
        while((written += audioDevice->write(sample.right(sample.size()-written))) < sample.size()) {
            QThread::msleep(1);
        }

        QCoreApplication::processEvents();
    }
    isPlayed = false;
}
//------------------------------------------------------------
double SoundProcessing::processEQ(double sample, memEQ &eq) {

    double y = eq.b0*sample + eq.b1*eq.xmem1 + eq.b2*eq.xmem2 - eq.a1*eq.ymem1 - eq.a2*eq.ymem2;

    eq.xmem2 = eq.xmem1;
    eq.xmem1 = sample;
    eq.ymem2 = eq.ymem1;
    eq.ymem1 = y;

    return y;
}
//------------------------------------------------------------
double SoundProcessing::processLow(double sample) {

    return processEQ(sample, lowMemEq);
}
//------------------------------------------------------------
double SoundProcessing::processMedium(double sample) {

    return processEQ(processEQ(sample, medMemEq), medMemEq2);
}
//------------------------------------------------------------
double SoundProcessing::processHigh(double sample) {

    return processEQ(sample, highMemEq);
}
//------------------------------------------------------------
void SoundProcessing::shelfFilter(double F0, double g, QString type, memEQ &eq) {

    if(type != "low" && type != "high") {
        qDebug() << "Wrong shelf filter type!";
        return;
    }

    double Fs = 48000;
    double S = 1;

    double A = pow(10, g/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double alpha = sin(w0)/2. * sqrt( (A + 1/A)*(1/S - 1) + 2 );

    int coef = type=="low"?1:-1;

    eq.b0 =        A*( (A+1) - coef*(A-1)*cos(w0) + 2*sqrt(A)*alpha );
    eq.b1 = 2*coef*A*( (A-1) - coef*(A+1)*cos(w0)                   );
    eq.b2 =        A*( (A+1) - coef*(A-1)*cos(w0) - 2*sqrt(A)*alpha );
    eq.a0 =            (A+1) + coef*(A-1)*cos(w0) + 2*sqrt(A)*alpha;
    eq.a1 =  -2*coef*( (A-1) + coef*(A+1)*cos(w0)                   );
    eq.a2 =            (A+1) + coef*(A-1)*cos(w0) - 2*sqrt(A)*alpha;

    eq.b0 /= eq.a0;
    eq.b1 /= eq.a0;
    eq.b2 /= eq.a0;
    eq.a1 /= eq.a0;
    eq.a2 /= eq.a0;
}
//------------------------------------------------------------
void SoundProcessing::lowEQ(int value) {

    shelfFilter(500, (value-50)/50.*10, "low", lowMemEq);
}
//------------------------------------------------------------
void SoundProcessing::medEQ(int value) {

    double g = (value-50)/50.*10;
    shelfFilter(15000, g, "low", medMemEq);
    shelfFilter(500, -g, "low", medMemEq2);
}
//------------------------------------------------------------
void SoundProcessing::highEQ(int value) {

    shelfFilter(15000, (value-50)/50.*10, "high", highMemEq);
}
//------------------------------------------------------------
void SoundProcessing::loadAudio(QString filename) {

    isPlayed = false;
    soundReady = false;

    channel1->clear();
    channel2->clear();

    decoder->stop();
    decoder->setSourceFilename(filename);
    decoder->start();
}
//------------------------------------------------------------
void SoundProcessing::readBuffer() {

    QAudioBuffer buffer = decoder->read();
    const qint16 *data = buffer.constData<qint16>();

    for(int i = 0; i < buffer.sampleCount()/2; i++) {
        channel1->append(reinterpret_cast<const char*>(data+i*2), sizeof(qint16));
        channel2->append(reinterpret_cast<const char*>(data+1+i*2), sizeof(qint16));
    }
}
//------------------------------------------------------------
void SoundProcessing::finishDecoding() {

    qDebug() << "ready";
    soundReady = true;
}
//------------------------------------------------------------
void SoundProcessing::enableWhiteNoise() {
    isWhiteNoise = true;
}
//------------------------------------------------------------
void SoundProcessing::disableWhiteNoise() {
    isWhiteNoise = false;
}
//------------------------------------------------------------
SoundProcessing::~SoundProcessing() {

    delete decoder;

    delete channel1;
    delete channel2;
}
