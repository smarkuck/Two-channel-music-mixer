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

    F0 = 12000;
    BW = 1;
    g = 0;
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
            rate += 0.00001;
            if(rate > 1) rate = 1;
            qint16 value = *(reinterpret_cast<qint16*>(channel1->data())+i+j);

            double y = b0*value + b1*xmem1 + b2*xmem2 - a1*ymem1 - a2*ymem2;

            xmem2 = xmem1;
            xmem1 = value;
            ymem2 = ymem1;
            ymem1 = y;
            if(y*rate > 30000 || y*rate < -30000) {
                rate = abs(30000/y);
            }
            value = y*rate;

            sample.append(reinterpret_cast<const char*>(&value), sizeof(qint16));

            value = *(reinterpret_cast<qint16*>(channel2->data())+i+j);

            y = b0*value + b1*xmem1 + b2*xmem2 - a1*ymem1 - a2*ymem2;

            xmem2 = xmem1;
            xmem1 = value;
            ymem2 = ymem1;
            ymem1 = y;
            if(y*rate > 30000 || y*rate < -30000) {
                rate = abs(30000/y);
            }

            value = y*rate;

            sample.append(reinterpret_cast<const char*>(&value), sizeof(qint16));
        }


        if(isWhiteNoise) {
            qint16 *data = reinterpret_cast<qint16*>(sample.data());

        }

        qint64 written = 0;
        while((written += audioDevice->write(sample.right(sample.size()-written))) < sample.size()) {
            QThread::msleep(1);
        }

        QCoreApplication::processEvents();
    }
    isPlayed = false;
}

void SoundProcessing::lowEQ(int value) {

    double Fs = 48000;
    F0 = value*24000/100.;

    double A = pow(10, g/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double c = cos(w0);
    double s = sin(w0);
    double alpha = s/2. * sqrt( (A + 1/A)*(1/BW - 1) + 2 );

    b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}

void SoundProcessing::medEQ(int value) {
    double Fs = 48000;
    BW = 1;

    double A = pow(10, g/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double c = cos(w0);
    double s = sin(w0);
    double alpha = s/2. * sqrt( (A + 1/A)*(1/BW - 1) + 2 );

    b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
}

void SoundProcessing::highEQ(int value) {
    double Fs = 48000;
    g = (value-50)/50.*10;

    double A = pow(10, g/40.);
    double w0 = 2*3.14159265359*F0/Fs;
    double c = cos(w0);
    double s = sin(w0);
    double alpha = s/2. * sqrt( (A + 1/A)*(1/BW - 1) + 2 );

    b0 =    A*( (A+1) - (A-1)*cos(w0) + 2*sqrt(A)*alpha );
    b1 =  2*A*( (A-1) - (A+1)*cos(w0)                   );
    b2 =    A*( (A+1) - (A-1)*cos(w0) - 2*sqrt(A)*alpha );
    a0 =        (A+1) + (A-1)*cos(w0) + 2*sqrt(A)*alpha;
    a1 =   -2*( (A-1) + (A+1)*cos(w0)                   );
    a2 =        (A+1) + (A-1)*cos(w0) - 2*sqrt(A)*alpha;

    b0 /= a0;
    b1 /= a0;
    b2 /= a0;
    a1 /= a0;
    a2 /= a0;
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
