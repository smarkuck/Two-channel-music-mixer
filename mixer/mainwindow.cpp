#include "mainwindow.h"
#include "downloading.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
//===============================================
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->customPlot->moveToThread(&th_soundGraph);
    connect(&th_soundGraph, &QThread::finished,ui->customPlot , &QObject::deleteLater);
    th_soundGraph.start();


    setupSoundGraph(ui->customPlot);
    setupSoundGraph2(ui->customPlot_2);

    soundProc = new SoundProcessing;
    soundProc->moveToThread(&th_soundProc);

    Downloading* download = new Downloading(soundProc);

    connect(&th_soundProc, &QThread::finished, soundProc, &QObject::deleteLater);
    th_soundProc.start();

    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));

    connect(ui->pbAddMusic, SIGNAL(clicked(bool)), this, SLOT(selectAudio()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(selectAudio()));
    connect(this, SIGNAL(loadAudio(QString)), &soundProc->panel1, SLOT(loadAudio(QString)));
    connect(ui->pbYes, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(enableWhiteNoise()));
    connect(ui->pbNo, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(disableWhiteNoise()));
    connect(ui->pbSound, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playPause()));
    connect(ui->pbStop_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playStop()));
    connect(ui->pbSingleLoop_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoop()));
    connect(ui->pbLoopEnable_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingSet()));
    connect(ui->pbLoopStart_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingStart()));
    connect(ui->pbLoopEnd_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingEnd()));
    connect(ui->pbLoopReturn_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingReturn()));

    connect(ui->sLow, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(lowEQ(int)));
    connect(ui->sMedium, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(medEQ(int)));
    connect(ui->sHigh, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(highEQ(int)));

    //AKCJE
    //sygnaly do zmiany suwakow
    connect(soundProc, SIGNAL(lowEQChange(int)), this, SLOT(lowChange(int)));
    connect(soundProc, SIGNAL(medEQChange(int)), this, SLOT(medChange(int)));
    connect(soundProc, SIGNAL(highEQChange(int)), this, SLOT(highChange(int)));
    connect(soundProc, SIGNAL(lowEQChange2(int)), this, SLOT(lowChange2(int)));
    connect(soundProc, SIGNAL(medEQChange2(int)), this, SLOT(medChange2(int)));
    connect(soundProc, SIGNAL(highEQChange2(int)), this, SLOT(highChange2(int)));
    connect(soundProc, SIGNAL(crossChange(int)), this, SLOT(crossChanger(int)));

    connect(&soundProc->panel1, SIGNAL(timeChange(QString)), ui->lTime, SLOT(setText(QString)));
    connect(&soundProc->panel1, SIGNAL(fileReady()), this, SLOT(setText_audio1Ready()));

    connect(ui->pbAddMusic_2, SIGNAL(clicked(bool)), this, SLOT(selectAudio2()));
    connect(ui->action_Open2, SIGNAL(triggered(bool)), this, SLOT(selectAudio2()));
    connect(this, SIGNAL(loadAudio2(QString)), &soundProc->panel2, SLOT(loadAudio(QString)));
    connect(ui->pbYes_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(enableWhiteNoise()));
    connect(ui->pbNo_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(disableWhiteNoise()));
    connect(ui->pbSound_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playPause()));
    connect(ui->pbStop_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playStop()));
    connect(ui->pbSingleLoop_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoop()));
    connect(ui->pbLoopEnable_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingSet()));
    connect(ui->pbLoopStart_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingStart()));
    connect(ui->pbLoopEnd_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingEnd()));
    connect(ui->pbLoopReturn_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingReturn()));


    connect(ui->sLow_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(lowEQ(int)));
    connect(ui->sMedium_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(medEQ(int)));
    connect(ui->sHigh_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(highEQ(int)));

    connect(&soundProc->panel2, SIGNAL(timeChange(QString)), ui->lTime_2, SLOT(setText(QString)));
    connect(&soundProc->panel2, SIGNAL(fileReady()), this, SLOT(setText_audio2Ready()));

    connect(ui->sCrossfader, SIGNAL(valueChanged(int)), this, SLOT(crossFaderChange(int)));
    connect(ui->pbDownload, SIGNAL(clicked(bool)), this, SLOT(onDownload()));
    connect(this, SIGNAL(startDownload(QString)), download, SLOT(download(QString)));

    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
    connect(ui->customPlot_2, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked2(QCPAbstractPlottable*,int)));

    //AKCJE
    //sygnaly do zapisywania i wczytywania akcji
    connect(ui->pbActionSave, SIGNAL(clicked(bool)), this, SLOT(saveAction()));
    connect(this, SIGNAL(saveActionToFile(QString)), &soundProc->action, SLOT(saveActionToFile(QString)));

    connect(ui->pbActionLoad, SIGNAL(clicked(bool)), this, SLOT(loadAction()));
    connect(this, SIGNAL(loadActionFromFile(QString)), &soundProc->action, SLOT(loadActionFromFile(QString)));

    connect(&soundProc->panel1, SIGNAL(writeToFile(quint64,quint64,quint64)), &soundProc->action, SLOT(writePanel1(quint64,quint64,quint64)));
    connect(&soundProc->panel2, SIGNAL(writeToFile(quint64,quint64,quint64)), &soundProc->action, SLOT(writePanel2(quint64,quint64,quint64)));

    connect(download, SIGNAL(downloadReady()), this, SLOT(downloadTextChange()));
}
//------------------------------------------------------------
void MainWindow::setupSoundGraph(QCustomPlot *customPlot)
{

  //customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  QCPGraph *graph = customPlot->addGraph();
  customPlot->setBackground(QColor(QWidget::palette().color(QWidget::backgroundRole())));

  //stworzenie i ustawienie wskaznika do pokazywania aktualnego czasu utworu
  bars1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
  bars1->setWidth(0.025);
  bars1->setPen(QPen(QColor(Qt::green)));
  bars1->setBrush(QBrush(QBrush(QColor(Qt::green))));


    barLoopStart_1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    barLoopStart_1->setWidth(0.025);
    barLoopStart_1->setPen(QPen(QColor(Qt::red)));
    QColor color1 = QColor(Qt::red);
    color1.setAlpha(50);
    barLoopStart_1->setBrush(QBrush(QBrush(color1)));


    barLoopEnd_1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    barLoopEnd_1->setWidth(0.25);
    barLoopEnd_1->setPen(QPen(QColor(Qt::red)));
    barLoopStart_1->setBrush(QBrush(QBrush(color1)));
    //barLoopEnd_1->setBrush(QBrush(QBrush(QColor(Qt::red).setAlpha(50))));

    filled = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    filled->setWidth(0.25);
    filled->setPen(QPen(Qt::NoPen));
    filled->setBrush(QBrush(QBrush(color1)));

  customPlot->yAxis->setRange(-100000, 100000);
    customPlot->yAxis->setVisible(false);
    customPlot->yAxis2->setVisible(false);
    customPlot->xAxis2->setVisible(false);
    customPlot->xAxis->setVisible(false);

    //tworze po dwa elementy dla vectora odpowiadajacego za wskaznik pozycji utworu,
    //jeden el dla czesci dodatniej wskzanika, drugi dla ujemnej
    x1.push_back(0);
    x1.push_back(0);
    y2.push_back(100000);
    y2.push_back(-100000);
    yStart_1.push_back(100000);
    yStart_1.push_back(-100000);
    xStart_1.push_back(0);
    xStart_1.push_back(0);
    yEnd_1.push_back(100000);
    yEnd_1.push_back(-100000);
    xEnd_1.push_back(0);
    xEnd_1.push_back(0);
    yfill.push_back(100000);
    yfill.push_back(-100000);
    xfill.push_back(0);
    xfill.push_back(0);
  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));

  dataTimer.start(0); // ustawinie timera do odswiezania danych
}

void MainWindow::bracketDataSlot()
{
    //jezeli utwor zaladoany to rysuje wykres
  if(soundProc->panel1.audioReady && soundProc->panel1.plot == false){

      ui->customPlot->xAxis->setRange(0,(soundProc->panel1.channel1->size() )/ (48000 * 2) + 1);
      int n = soundProc->panel1.channel1->size();
      QVector<double> x, y;

      quint64 actPos = 0;

  for (int i=1; actPos<n/sizeof(qint16); i++)
    {
      //dziele przez czestotliwosc zeby zsynchronizowac osX z czasem
      x.push_back(actPos/48000.);
        //pobieram i dodaje probki z kanalu 1 i 2
      y.push_back(*(reinterpret_cast<qint16*>(soundProc->panel1.channel1->data())+actPos)
                         +*(reinterpret_cast<qint16*>(soundProc->panel1.channel2->data())+actPos));
      actPos += 3000;

      if(actPos % 96 == 0)
      {
        ui->customPlot->graph()->setData(x, y);
        ui->customPlot->replot();
      }
  }

    //ustawiam dane do rysowania i wskaznik pozycji utworu na 0
    x1[0] = 0;
    x1[1] = 0;
    bars1->setData(x1, y2);
    ui->customPlot->replot();
    soundProc->panel1.plot = true;

  }

  if(soundProc->panel1.isLoopStartSet){
      xStart_1[0]=soundProc->panel1.loopingStart/48000;
      xStart_1[1]=soundProc->panel1.loopingStart/48000;
      barLoopStart_1->setData(xStart_1, yStart_1);
  }

  if(soundProc->panel1.isLoopEndSet){
      xEnd_1[0]=soundProc->panel1.loopingEnd/48000;
      xEnd_1[1]=soundProc->panel1.loopingEnd/48000;
      barLoopEnd_1->setData(xEnd_1, yEnd_1);
  }


  if(soundProc->panel1.isLoopStartSet && soundProc->panel1.isLoopEndSet ){
      xfill[0] = (soundProc->panel1.loopingEnd/48000 - ((soundProc->panel1.loopingEnd/48000 - soundProc->panel1.loopingStart/48000) / 2));
      xfill[1] = (soundProc->panel1.loopingEnd/48000 - ((soundProc->panel1.loopingEnd/48000 - soundProc->panel1.loopingStart/48000) / 2));

      filled->setWidth((soundProc->panel1.loopingEnd/48000 - soundProc->panel1.loopingStart/48000));
      filled->setData(xfill,yfill);
      ui->customPlot->replot();
  }

  if(soundProc->panel1.isPlayed){

    //to odpowiada za przesuwanie sie wykresu podczas odtwarzania

    ui->customPlot->xAxis->setRange(0,(soundProc->panel1.channel1->size() )/ (48000 * 2) + 1);
    x1[0] = soundProc->panel1.actPos/48000;
    x1[1]=  soundProc->panel1.actPos/48000;
    bars1->setData(x1, y2);
    ui->customPlot->replot();
  }



}


void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{

  double czas = plottable->interface1D()->dataMainKey(dataIndex);  //TO JEST OS X - sekundy
  //double amplituda = plottable->interface1D()->dataMainValue(dataIndex);  //TO JEST OS Y - amplituda dzwieku

  soundProc->panel1.actPos = czas*48000;
  x1[0] = czas;
  x1[1] = czas;
  bars1->setData(x1, y2);
  ui->customPlot->replot();

}
//-----------GRAPH 1--------------------------------------------------

void MainWindow::setupSoundGraph2(QCustomPlot *customPlot)
{

  //customPlot->setInteractions( QCP::iRangeZoom);
  QCPGraph *graph = customPlot->addGraph();

    customPlot->setBackground(QColor(QWidget::palette().color(QWidget::backgroundRole())));
  //stworzenie i ustawienie wskaznika do pokazywania aktualnego czasu utworu
  bars2 = new QCPBars(ui->customPlot_2->xAxis, ui->customPlot_2->yAxis);
  bars2->setWidth(0.025);
  bars2->setPen(QPen(QColor(Qt::green)));
  bars2->setBrush(QBrush(QBrush(QColor(Qt::green))));


  barLoopStart_2 = new QCPBars(ui->customPlot_2->xAxis, ui->customPlot_2->yAxis);
  barLoopStart_2->setWidth(0.025);
  barLoopStart_2->setPen(QPen(QColor(Qt::red)));
  barLoopStart_2->setBrush(QBrush(QBrush(QColor(Qt::red))));

  barLoopEnd_2 = new QCPBars(ui->customPlot_2->xAxis, ui->customPlot_2->yAxis);
  barLoopEnd_2->setWidth(0.025);
  barLoopEnd_2->setPen(QPen(QColor(Qt::red)));
  barLoopEnd_2->setBrush(QBrush(QBrush(QColor(Qt::red))));


  customPlot->yAxis->setRange(-100000, 100000);   //ustawienie zakresu osiY
    customPlot->yAxis->setVisible(false);
    customPlot->yAxis2->setVisible(false);
    customPlot->xAxis2->setVisible(false);
    customPlot->xAxis->setVisible(false);

    //tworze po dwa elementy dla vectora odpowiadajacego za wskaznik pozycji utworu,
    //jeden el dla czesci dodatniej wskzanika, drugi dla ujemnej
    x2.push_back(0);
    x2.push_back(0);
    y1.push_back(100000);
    y1.push_back(-100000);
    yStart_2.push_back(100000);
    yStart_2.push_back(-100000);
    xStart_2.push_back(0);
    xStart_2.push_back(0);
    yEnd_2.push_back(100000);
    yEnd_2.push_back(-100000);
    xEnd_2.push_back(0);
    xEnd_2.push_back(0);
  connect(&dataTimer2, SIGNAL(timeout()), this, SLOT(bracketDataSlot2()));

  dataTimer2.start(0); // ustawinie timera do odswiezania danych
}

void MainWindow::bracketDataSlot2()
{
    //jezeli utwor zaladoany to rysuje wykres
  if(soundProc->panel2.audioReady && soundProc->panel2.plot == false){

      ui->customPlot_2->xAxis->setRange(0,(soundProc->panel2.channel1->size() )/ (48000 * 2) + 1);
      int n = soundProc->panel2.channel1->size();
      QVector<double> x, y;
      quint64 actPos = 0;

  for (int i=1; i<n/sizeof(qint16); i+=3000)
    {
      x.push_back(i/48000.);  //dziele przez czestotliwosc zeby zsynchronizowac osX z czasem
      //pobieram i dodaje probki z kanalu 1 i 2, nie wiem czy to jest dobre ale nie bedziemy
      //chyba rysowac dwoch kanalow osobno xD
      y.push_back(*(reinterpret_cast<qint16*>(soundProc->panel2.channel1->data())+actPos)
              +*(reinterpret_cast<qint16*>(soundProc->panel2.channel2->data())+actPos));
      actPos += 3000;
      if(actPos % 96 == 0){
        ui->customPlot_2->graph()->setData(x, y);
        ui->customPlot_2->replot();
      }

  }

  //ustawiam dane do rysowania i wskaznik pozycji utworu na 0
  x2[0] = 0;
  x2[1] = 0;
  bars2->setData(x2, y1);
  xStart_2[0]=0;
  xStart_2[1]=0;
  barLoopStart_2->setData(xStart_2, yStart_2);
  xEnd_2[0]=0;
  xEnd_2[1]=0;
  barLoopEnd_2->setData(xEnd_2, yEnd_2);
  ui->customPlot_2->replot();
  soundProc->panel2.plot = true;
  }


  if(soundProc->panel2.isPlayed){

    //to odpowiada za przesuwanie sie wykresu podczas odtwarzania
      //pobieram aktualna pozycje utworu i dziele przez czestotliwosc zeby dostac sekundy
    //ui->customPlot_2->xAxis->setRange(soundProc->panel2.actPos/48000+2, 4, Qt::AlignRight);
    ui->customPlot->xAxis->setRange(0,(soundProc->panel1.channel1->size() )/ (48000 * 2) + 1);
    x2[0] = soundProc->panel2.actPos/48000;
    x2[1]=  soundProc->panel2.actPos/48000;
    bars2->setData(x2, y1);
    xStart_2[0]=soundProc->panel2.loopingStart/48000;
    xStart_2[1]=soundProc->panel2.loopingStart/48000;
    barLoopStart_2->setData(xStart_2, yStart_2);
    xEnd_2[0]=soundProc->panel2.loopingEnd/48000;
    xEnd_2[1]=soundProc->panel2.loopingEnd/48000;
    barLoopEnd_2->setData(xEnd_2, yEnd_2);
    ui->customPlot_2->replot();
  }

}


void MainWindow::graphClicked2(QCPAbstractPlottable *plottable, int dataIndex)
{
  double czas = plottable->interface1D()->dataMainKey(dataIndex);  //TO JEST OS X - sekundy
  //double amplituda = plottable->interface1D()->dataMainValue(dataIndex);  //TO JEST OS Y - amplituda dzwieku

  soundProc->panel2.actPos = czas*48000;
  x2[0] = czas;
  x2[1] = czas;
  bars2->setData(x2, y1);
  ui->customPlot_2->replot();

}
//----------PLOTING------------------------------------------------------



void MainWindow::selectAudio() {
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "/home/", tr("Music Files (*.mp3)"));

    if(filename == "") return;

    ui->laudio->setText(filename.split('/').last());
    ui->file1_ready->setText("Wait...");
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
    ui->file2_ready->setText("Wait...");
    emit loadAudio2(filename);
}
//------------------------------------------------------------
void MainWindow::crossFaderChange(int value) {
    soundProc->crossFader = value;
    if(soundProc->panel1.audioReady)
        emit soundProc->panel1.writeToFile(6, soundProc->panel1.actPos,value);
    else if(soundProc->panel2.audioReady)
        emit soundProc->panel2.writeToFile(6, soundProc->panel2.actPos,value);
}

void MainWindow::saveAction()
{
     QString fileName = QFileDialog::getSaveFileName(this,
         tr("Save action"), "/home", tr("save(*.acn)"));

     if(fileName == "") return;

     emit saveActionToFile(fileName);

}

void MainWindow::loadAction()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open action"), "/home", tr("Action Files (*.acn)"));

    if(fileName == "") return;

    emit loadActionFromFile(fileName);
}

void MainWindow::lowChange(int value)
{
    ui->sLow->setSliderPosition(value);
    ui->sLow->setValue(value);
}

void MainWindow::medChange(int value)
{
    ui->sMedium->setSliderPosition(value);
    ui->sMedium->setValue(value);
}

void MainWindow::highChange(int value)
{
    ui->sHigh->setSliderPosition(value);
    ui->sHigh->setValue(value);
}

void MainWindow::lowChange2(int value)
{
    ui->sLow_2->setSliderPosition(value);
    ui->sLow_2->setValue(value);
}

void MainWindow::medChange2(int value)
{
    ui->sMedium_2->setSliderPosition(value);
    ui->sMedium_2->setValue(value);
}

void MainWindow::highChange2(int value)
{
    ui->sHigh_2->setSliderPosition(value);
    ui->sHigh_2->setValue(value);
}

void MainWindow::crossChanger(int value)
{
    ui->sCrossfader->setSliderPosition(value);
    ui->sCrossfader->setValue(value);
}
//------------------------------------------------------------

void MainWindow::onDownload() {


    //wybor lokalizacji zapisywanego pliku audio
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Download"), "/home", tr("audio(*.wav);;audio(*.mp3)"),&selectedFilter);

    if(filename.count() != 0){
        ui->download_ready->setText("Wait...");
        if (selectedFilter.endsWith(".wav)"))
            filename += ".wav";
        else
            filename += ".mp3";

        emit startDownload(filename);
    }

}
//------------------------------------------------------------

MainWindow::~MainWindow()
{
    th_soundProc.quit();
    th_soundProc.wait();
    delete ui;
}

//------------------------------------------------

void MainWindow::downloadTextChange(){
    ui->download_ready->setText("Done");
}


void MainWindow::setText_audio1Ready(){
     ui->file1_ready->setText("");
}

void MainWindow::setText_audio2Ready(){
     ui->file2_ready->setText("");
}
