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

    for(int i= 0; i < channel1->size()/sizeof(qint16) && !abort && isPlayed; i+=1000) {

        QByteArray sample;
        for(int j = 0; j < 1000; j++) {
            sample.append(channel1->mid((i+j)*sizeof(qint16), sizeof(qint16)));
            sample.append(channel2->mid((i+j)*sizeof(qint16), sizeof(qint16)));
        }

        if(isWhiteNoise) {
            qint16 *data = reinterpret_cast<qint16*>(sample.data());
            for(unsigned int j = 0; j < sample.size()/sizeof(qint16); j++) {
                data[j] *= 100;
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
