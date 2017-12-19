#include "mainwindow.h"
#include "ui_mainwindow.h"
//===============================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    soundProc = new SoundProcessing;
    soundProc->moveToThread(&th_soundProc);

    connect(&th_soundProc, &QThread::finished, soundProc, &QObject::deleteLater);
    th_soundProc.start();

    connect(ui->pbAddMusic, SIGNAL(clicked(bool)), this, SLOT(selectAudio()));
    connect(this, SIGNAL(loadAudio(QString)), &soundProc->panel1, SLOT(loadAudio(QString)));
    connect(ui->pbYes, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(enableWhiteNoise()));
    connect(ui->pbNo, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(disableWhiteNoise()));
    connect(ui->pbSound, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playPause()));

    connect(ui->sLow, SIGNAL(sliderMoved(int)), &soundProc->panel1, SLOT(lowEQ(int)));
    connect(ui->sMedium, SIGNAL(sliderMoved(int)), &soundProc->panel1, SLOT(medEQ(int)));
    connect(ui->sHigh, SIGNAL(sliderMoved(int)), &soundProc->panel1, SLOT(highEQ(int)));

    connect(&soundProc->panel1, SIGNAL(timeChange(QString)), ui->lTime, SLOT(setText(QString)));

    connect(ui->pbAddMusic_2, SIGNAL(clicked(bool)), this, SLOT(selectAudio2()));
    connect(this, SIGNAL(loadAudio2(QString)), &soundProc->panel2, SLOT(loadAudio(QString)));
    connect(ui->pbYes_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(enableWhiteNoise()));
    connect(ui->pbNo_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(disableWhiteNoise()));
    connect(ui->pbSound_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playPause()));

    connect(ui->sLow_2, SIGNAL(sliderMoved(int)), &soundProc->panel2, SLOT(lowEQ(int)));
    connect(ui->sMedium_2, SIGNAL(sliderMoved(int)), &soundProc->panel2, SLOT(medEQ(int)));
    connect(ui->sHigh_2, SIGNAL(sliderMoved(int)), &soundProc->panel2, SLOT(highEQ(int)));

    connect(&soundProc->panel2, SIGNAL(timeChange(QString)), ui->lTime_2, SLOT(setText(QString)));

    connect(ui->sCrossfader, SIGNAL(sliderMoved(int)), this, SLOT(crossFaderChange(int)));
}
//------------------------------------------------------------
void MainWindow::selectAudio() {
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "/home/", tr("Music Files (*.mp3)"));

    if(filename == "") return;

    ui->laudio->setText(filename.split('/').last());
    emit loadAudio(filename);
}

void MainWindow::closeEvent(QCloseEvent * /* unused */) {
    soundProc->abort = true;
}
//------------------------------------------------------------
void MainWindow::selectAudio2() {
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "/home/", tr("Music Files (*.mp3)"));

    if(filename == "") return;

    ui->laudio_2->setText(filename.split('/').last());
    emit loadAudio2(filename);
}
//------------------------------------------------------------
void MainWindow::crossFaderChange(int value) {
    soundProc->crossFader = value;
}
//------------------------------------------------------------
MainWindow::~MainWindow()
{
    th_soundProc.quit();
    th_soundProc.wait();
    delete ui;
}
