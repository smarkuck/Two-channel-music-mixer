#include "mixpanel.h"
#include "mainwindow.h"

MixPanel::MixPanel(QObject *parent) : QObject(parent)
{
    actPos = 0;
    realPosition = 0;
    duration = 0;
    loopingStart = 0;
    isSingleLoop = false;
    isLoopingSet = false;
    isLoopStartSet = false;
    audioReady = false;
    isPlayed = false;
    plot = false;
    speed = 1.0;
    volume = 0.5;

    channel1 = new QByteArray();
    channel2 = new QByteArray();

    QAudioFormat format;
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleRate(48000);
    format.setSampleSize(16);

    decoder = new QAudioDecoder;
    decoder->setAudioFormat(format);

    connect(decoder, SIGNAL(bufferReady()), this, SLOT(readBuffer()));
    connect(decoder, SIGNAL(finished()), this, SLOT(finishDecoding()));

    for(int i = 0; i < 2; i++) {
        memset(&lowMemEq[i], 0, sizeof(memEQ));
        memset(&medMemEq[i], 0, sizeof(memEQ));
        memset(&medMemEq2[i], 0, sizeof(memEQ));
        memset(&highMemEq[i], 0, sizeof(memEQ));
    }

    lowEQ(50);
    medEQ(50);
    highEQ(50);

    shelfFilter(500, -10, "low", lowMemEq[0]);
    shelfFilter(500, 10, "low", lowMemEq[1]);

    shelfFilter(15000, -10, "low", medMemEq[0]);
    shelfFilter(500, 10, "low", medMemEq2[0]);
    shelfFilter(15000, 10, "low", medMemEq[1]);
    shelfFilter(500, -10, "low", medMemEq2[1]);

    shelfFilter(15000, -10, "high", highMemEq[0]);
    shelfFilter(15000, 10, "high", highMemEq[1]);
}

void MixPanel::playPause() {
    //if(audioReady)
    //{
        isPlayed = !isPlayed;

    //}
}

void MixPanel::playLoopingSet() {
    //if(audioReady)
    //{
        if(isLoopStartSet && isLoopEndSet && !isLoopingSet){
            isLoopStartSet = false;
            //loopingStart = loopingEnd = 0;
        }
        isLoopingSet = !isLoopingSet;

        qDebug() << isLoopingSet;

    //}
}
void MixPanel::playLoopingStart() {
    //if(audioReady)
    //{
        loopingStart = actPos;
        isLoopStartSet = true;

    //}
}
void MixPanel::playLoopingEnd() {
    //if(audioReady)
    //{
        loopingEnd = actPos;
        actPos = loopingStart;
        realPosition = loopingStart;
        isLoopEndSet = true;
    //}
}
void MixPanel::playLoopingReturn() {
    //if(audioReady)
    //{
        if(isLoopStartSet)
        {
            isLoopingSet = true;
            actPos = loopingStart;
            realPosition = loopingStart;
        }
    //}
}
void MixPanel::playLoop() {
    //if(audioReady)
    //{
        isSingleLoop = !isSingleLoop;
    //}
}

void MixPanel::playStop() {

    isPlayed = false;
    audioReady = true;
    actPos = 0;
    realPosition = 0;
    int minutes = duration/1000000./60.;
    int seconds = (duration - minutes*1000000*60)/1000000.;
    QString time  = "0:00/" + QString::number(minutes) + ":" + QString::number(seconds);
    emit timeChange(time);



}

void MixPanel::process(double *buffer, int nFrames) {

    //if(!audioReady || !isPlayed) {
    if( !isPlayed) {
        memset(buffer, 0, sizeof(double)*nFrames*2);
        return;
    }


    for(int i = 0; i < nFrames; i++) {

        if(actPos >= channel1->size()/sizeof(qint16)) {
            buffer[i*2] = 0;
            buffer[i*2+1] = 0;
            continue;
        }

        qint16 value = *(reinterpret_cast<qint16*>(channel1->data())+actPos)*volume;
        qint16 value2 = *(reinterpret_cast<qint16*>(channel2->data())+actPos)*volume;

        double y;
        double y2;

        if(lowValue>=0) {
            y = processLowUp(value)*lowValue*10+value*(1-lowValue);
            y2 = processLowUp(value2)*lowValue*10+value2*(1-lowValue);
        }
        else {
            y = processLowDown(value)*(-lowValue)*10+value*(1+lowValue);
            y2 = processLowDown(value2)*(-lowValue)*10+value2*(1+lowValue);
        }

        if(medValue>=0) {
            y += processMediumUp(value)*medValue*10+value*(1-medValue);
            y2 += processMediumUp(value2)*medValue*10+value2*(1-medValue);
        }
        else {
            y += processMediumDown(value)*(-medValue)*10+value*(1+medValue);
            y2 += processMediumDown(value2)*(-medValue)*10+value2*(1+medValue);
        }

        if(highValue>=0) {
            y += processHighUp(value)*highValue*10+value*(1-highValue);
            y2 += processHighUp(value2)*highValue*10+value2*(1-highValue);
        }
        else {
            y += processHighDown(value)*(-highValue)*10+value*(1+highValue);
            y2 += processHighDown(value2)*(-highValue)*10+value2*(1+highValue);
        }

        float dividor = abs(lowValue)*10+1+abs(medValue)*10+1+abs(highValue)*10+1;

        buffer[i*2] = y/dividor;
        buffer[i*2+1] = y2/dividor;

        realPosition += speed;
        actPos = (int)realPosition;

    }
    if((loopingEnd > loopingStart) && isLoopingSet){
        if((actPos > loopingEnd)){
            actPos = loopingStart;
            realPosition = loopingStart;
        }
    }
    else if ((loopingEnd < loopingStart) && isLoopingSet){
        if((actPos > loopingEnd) && (actPos < loopingStart)){
            actPos = loopingStart;
            realPosition = loopingStart;
        }
    }

    if(actPos >= channel1->size()/sizeof(qint16)) {
        actPos = 0;
        realPosition = 0;
        if(isSingleLoop || isLoopingSet) isPlayed = true;
        else isPlayed = false;
    }

    int seconds = actPos/48000.;
    int minutes = seconds/60.;
    seconds -= minutes*60;

    QString sSeconds = QString::number(seconds);
    if(sSeconds.size() == 1)
        sSeconds.insert(0, '0');

    QString time = QString::number(minutes) + ":" + sSeconds;

    minutes = duration/1000000./60.;
    seconds = (duration - minutes*1000000*60)/1000000.;

    sSeconds = QString::number(seconds);
    if(sSeconds.size() == 1)
        sSeconds.insert(0, '0');

    time  += "/" + QString::number(minutes) + ":" + QString::number(seconds);

    emit timeChange(time);
}

double MixPanel::processEQ(double sample, memEQ &eq) {

    double y = eq.b0*sample + eq.b1*eq.xmem1 + eq.b2*eq.xmem2 - eq.a1*eq.ymem1 - eq.a2*eq.ymem2;

    eq.xmem2 = eq.xmem1;
    eq.xmem1 = sample;
    eq.ymem2 = eq.ymem1;
    eq.ymem1 = y;

    return y;
}

double MixPanel::processLowUp(double sample) {
    return processEQ(sample, lowMemEq[1]);
}

double MixPanel::processLowDown(double sample) {
    return processEQ(sample, lowMemEq[0]);
}

double MixPanel::processMediumUp(double sample) {
    return processEQ(processEQ(sample, medMemEq[1]), medMemEq2[1]);
}

double MixPanel::processMediumDown(double sample) {
    return processEQ(processEQ(sample, medMemEq[0]), medMemEq2[0]);
}

double MixPanel::processHighUp(double sample) {
    return processEQ(sample, highMemEq[1]);
}

double MixPanel::processHighDown(double sample) {
    return processEQ(sample, highMemEq[0]);
}

void MixPanel::shelfFilter(double F0, double g, QString type, memEQ &eq) {

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

void MixPanel::lowEQ(int value) {
    //shelfFilter(500, (value-50)/50.*10, "low", lowMemEq);
    lowValue = (value-50)/50.;
    emit writeToFile(1, actPos,value);  //emisja sygnalu do zapisania akcji
}

void MixPanel::medEQ(int value) {
    //double g = (value-50)/50.*10;
    //shelfFilter(15000, g, "low", medMemEq);
    //shelfFilter(500, -g, "low", medMemEq2);
    medValue = (value-50)/50.;
    emit writeToFile(2, actPos,value);
}

void MixPanel::highEQ(int value) {
    //shelfFilter(15000, (value-50)/50.*10, "high", highMemEq);
    highValue = (value-50)/50.;
    emit writeToFile(3, actPos,value);
}

void MixPanel::loadAudio(QString filename) {
    isPlayed = false;
    audioReady = true;

    duration = 0;
    actPos = 0;
    realPosition = 0;

    channel1->clear();
    channel2->clear();

    decoder->stop();
    decoder->setSourceFilename(filename);
    decoder->start();
}

void MixPanel::readBuffer() {
    QAudioBuffer buffer = decoder->read();
    duration += buffer.duration();

    const qint16 *data = buffer.constData<qint16>();

    for(int i = 0; i < buffer.sampleCount()/2; i++) {
        channel1->append(reinterpret_cast<const char*>(data+i*2), sizeof(qint16));
        channel2->append(reinterpret_cast<const char*>(data+1+i*2), sizeof(qint16));
    }
    int minutes = duration/1000000./60.;
    int seconds = (duration - minutes*1000000*60)/1000000.;

    QString sSeconds = QString::number(seconds);
    if(sSeconds.size() == 1)
        sSeconds.insert(0, '0');

    QString time  = "0:00/" + QString::number(minutes) + ":" + QString::number(seconds);

    emit timeChange(time);
    if(minutes == 1)

    audioReady = true;

}

void MixPanel::finishDecoding() {
    qDebug() << "ready";
    plot = false;

    emit fileReady();

}

void MixPanel::speedChange(int value){
    speed = value/50.0;
}
void MixPanel::volumeChange(int value){
    volume = value/100.0;
}

MixPanel::~MixPanel() {
    delete decoder;

    delete channel1;
    delete channel2;
}






