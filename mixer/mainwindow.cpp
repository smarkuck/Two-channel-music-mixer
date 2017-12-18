#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    soundProc = new SoundProcessing;
    soundProc->moveToThread(&th_soundProc);

    connect(&th_soundProc, &QThread::finished, soundProc, &QObject::deleteLater);
    soundProc->init();
    th_soundProc.start();

    connect(ui->pbAddMusic, SIGNAL(clicked(bool)), this, SLOT(selectAudio()));
    connect(this, SIGNAL(loadAudio(QString)), soundProc, SLOT(loadAudio(QString)));
    connect(ui->pbYes, SIGNAL(clicked(bool)), soundProc, SLOT(enableWhiteNoise()));
    connect(ui->pbNo, SIGNAL(clicked(bool)), soundProc, SLOT(disableWhiteNoise()));
    connect(ui->pbSound, SIGNAL(clicked(bool)), soundProc, SLOT(play()));

    connect(ui->sLow, SIGNAL(sliderMoved(int)), soundProc, SLOT(lowEQ(int)));
    connect(ui->sMedium, SIGNAL(sliderMoved(int)), soundProc, SLOT(medEQ(int)));
    connect(ui->sHigh, SIGNAL(sliderMoved(int)), soundProc, SLOT(highEQ(int)));
}

void MainWindow::selectAudio() {
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "/home/", tr("Music Files (*.mp3)"));
    emit loadAudio(filename);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    soundProc->abort = true;
}

MainWindow::~MainWindow()
{
    th_soundProc.quit();
    th_soundProc.wait();
    delete ui;
}

void SoundProcessing::init() {

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

    lg = 0;
    mg = 0;
    hg = 0;

    lowEQ(50);
    medEQ(50);
    highEQ(50);
}

void SoundProcessing::loadAudio(QString filename) {

    isPlayed = false;
    soundReady = false;

    channel1->clear();
    channel2->clear();

    decoder->stop();
    decoder->setSourceFilename(filename);
    decoder->start();
}

void SoundProcessing::play() {

    if(!soundReady || isPlayed) return;

    isPlayed = true;
    double rate = 1;

    for(int i= 0; i < channel1->size()/sizeof(qint16) && !abort && isPlayed; i+=16) {
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

            for(int j = 0; j < sample.size()/sizeof(qint16); j++) {
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

double SoundProcessing::processLow(double sample) {
    double y = lb0*sample + lb1*lxmem1 + lb2*lxmem2 - la1*lymem1 - la2*lymem2;

    lxmem2 = lxmem1;
    lxmem1 = sample;
    lymem2 = lymem1;
    lymem1 = y;

    return y;
}

double SoundProcessing::processMedium(double sample) {
    double y = mb0*sample + mb1*mxmem1 + mb2*mxmem2 - ma1*mymem1 - ma2*mymem2;

    mxmem2 = mxmem1;
    mxmem1 = sample;
    mymem2 = mymem1;
    mymem1 = y;

//    return y;
    double y2 = m2b0*y + m2b1*m2xmem1 + m2b2*m2xmem2 - m2a1*m2ymem1 - m2a2*m2ymem2;

    m2xmem2 = m2xmem1;
    m2xmem1 = y;
    m2ymem2 = m2ymem1;
    m2ymem1 = y2;

    return y2;
}

double SoundProcessing::processHigh(double sample) {
    double y = hb0*sample + hb1*hxmem1 + hb2*hxmem2 - ha1*hymem1 - ha2*hymem2;

    hxmem2 = hxmem1;
    hxmem1 = sample;
    hymem2 = hymem1;
    hymem1 = y;

    return y;
}

void SoundProcessing::lowEQ(int value) {

    double Fs = 48000;
    double F0 = 500;
    double S = 1;
    lg = (value-50)/50.*10;

    double A = pow(10, lg/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double alpha = sin(w0)/2. * sqrt( (A + 1/A)*(1/S - 1) + 2 );

    lb0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    lb1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    lb2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    la0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    la1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    la2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    lb0 /= la0;
    lb1 /= la0;
    lb2 /= la0;
    la1 /= la0;
    la2 /= la0;
}

void SoundProcessing::medEQ(int value) {
    double Fs = 48000;
    double F0 = 15000;
    double S = 1;
    mg = (value-50)/50.*10;

    double A = pow(10, mg/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double alpha = sin(w0)/2. * sqrt( (A + 1/A)*(1/S - 1) + 2 );

    mb0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    mb1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    mb2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    ma0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    ma1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    ma2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    mb0 /= ma0;
    mb1 /= ma0;
    mb2 /= ma0;
    ma1 /= ma0;
    ma2 /= ma0;

    F0 = 500;
    w0 = 2*3.14159265359*F0/Fs;
    A = pow(10, -mg/40.);
    alpha = sin(w0)/2. * sqrt( (A + 1/A)*(1/S - 1) + 2 );

    m2b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    m2b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    m2b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    m2a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    m2a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    m2a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    m2b0 /= m2a0;
    m2b1 /= m2a0;
    m2b2 /= m2a0;
    m2a1 /= m2a0;
    m2a2 /= m2a0;
}

void SoundProcessing::highEQ(int value) {
    double Fs = 48000;
    double F0 = 15000;
    double S = 1;
    hg = (value-50)/50.*10;

    double A = pow(10, hg/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double alpha = sin(w0)/2. * sqrt( (A + 1/A)*(1/S - 1) + 2 );

    hb0 =    A*( (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    hb1 = -2*A*( (A-1) + (A+1)*cos(w0)                   );
    hb2 =    A*( (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    ha0 =        (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    ha1 =    2*( (A-1) - (A+1)*cos(w0)                   );
    ha2 =        (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    hb0 /= ha0;
    hb1 /= ha0;
    hb2 /= ha0;
    ha1 /= ha0;
    ha2 /= ha0;
}

void SoundProcessing::finishDecoding() {

    qDebug() << "ready";
    soundReady = true;
}

void SoundProcessing::readBuffer() {

    QAudioBuffer buffer = decoder->read();
    const qint16 *data = buffer.constData<qint16>();

    for(int i = 0; i < buffer.sampleCount()/2; i++) {
        channel1->append(reinterpret_cast<const char*>(data+i*2), sizeof(qint16));
        channel2->append(reinterpret_cast<const char*>(data+1+i*2), sizeof(qint16));
    }
}

void SoundProcessing::enableWhiteNoise() {
    isWhiteNoise = true;
}

void SoundProcessing::disableWhiteNoise() {
    isWhiteNoise = false;
}

SoundProcessing::~SoundProcessing() {

    delete decoder;

    delete channel1;
    delete channel2;
}
