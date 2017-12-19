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
    connect(this, SIGNAL(loadAudio(QString)), soundProc, SLOT(loadAudio(QString)));
    connect(ui->pbYes, SIGNAL(clicked(bool)), soundProc, SLOT(enableWhiteNoise()));
    connect(ui->pbNo, SIGNAL(clicked(bool)), soundProc, SLOT(disableWhiteNoise()));
    connect(ui->pbSound, SIGNAL(clicked(bool)), soundProc, SLOT(play()));

    connect(ui->sLow, SIGNAL(sliderMoved(int)), soundProc, SLOT(lowEQ(int)));
    connect(ui->sMedium, SIGNAL(sliderMoved(int)), soundProc, SLOT(medEQ(int)));
    connect(ui->sHigh, SIGNAL(sliderMoved(int)), soundProc, SLOT(highEQ(int)));
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
MainWindow::~MainWindow()
{
    th_soundProc.quit();
    th_soundProc.wait();
    delete ui;
}
