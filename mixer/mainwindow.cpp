#include "mainwindow.h"
#include "exporting.h"
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

    setFixedSize(size());

    QString path = QDir::currentPath();
    path.append("/../mixer/stylesheet.qss");
    QFile File(path);
    File.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&File);

    QString stylesheet = in.readAll();

    setStyleSheet(stylesheet);

    setupSoundGraph(ui->customPlot);
    setupSoundGraph2(ui->customPlot_2);

    soundProc = new SoundProcessing;
    soundProc->moveToThread(&th_soundProc);
    soundProc->timer->moveToThread(&th_soundProc);

    Exporting* Export = new Exporting(soundProc);

    connect(&th_soundProc, &QThread::finished, soundProc, &QObject::deleteLater);
    th_soundProc.start();

    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));

    connect(ui->pbAddMusic, SIGNAL(clicked(bool)), this, SLOT(selectAudio()));
    connect(ui->action_Open, SIGNAL(triggered(bool)), this, SLOT(selectAudio()));
    connect(this, SIGNAL(loadAudio(QString)), &soundProc->panel1, SLOT(loadAudio(QString)));
    connect(ui->pbSound, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playPause()));
    connect(&soundProc->panel1, SIGNAL(pause()), ui->pbSound, SLOT(click()));
    connect(ui->pbStop_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playStop()));
    connect(ui->pbSingleLoop_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoop()));
    connect(ui->pbLoopEnable_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingSet()));
    connect(ui->pbLoopStart_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingStart()));
    connect(ui->pbLoopEnd_1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(playLoopingEnd()));
    connect(ui->pbFlag1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setFlag1()));
    connect(ui->pbFlag2, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setFlag2()));
    connect(ui->pbFlag3, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setFlag3()));
    connect(ui->pbFlag4, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setFlag4()));
    connect(ui->pbUnflag1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(unsetFlag1()));
    connect(ui->pbUnflag2, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(unsetFlag2()));
    connect(ui->pbUnflag3, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(unsetFlag3()));
    connect(ui->pbUnflag4, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(unsetFlag4()));

    connect(ui->pbLoop1_16, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop1_16()));
    connect(ui->pbLoop1_8, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop1_8()));
    connect(ui->pbLoop1_4, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop1_4()));
    connect(ui->pbLoop1_2, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop1_2()));
    connect(ui->pbLoop1, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop1()));
    connect(ui->pbLoop2, SIGNAL(clicked(bool)), &soundProc->panel1, SLOT(setLoop2()));

    connect(ui->sLow, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(lowEQ(int)));
    connect(ui->sMedium, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(medEQ(int)));
    connect(ui->sHigh, SIGNAL(valueChanged(int)), &soundProc->panel1, SLOT(highEQ(int)));
    connect(ui->sSpeed1,SIGNAL(valueChanged(int)),&soundProc->panel1,SLOT(speedChange(int)));
    connect(ui->sVolume1,SIGNAL(valueChanged(int)),&soundProc->panel1,SLOT(volumeChange(int)));

    //AKCJE
    //sygnaly do zmiany suwakow
    connect(soundProc, SIGNAL(lowEQChange(int)), this, SLOT(lowChange(int)));
    connect(soundProc, SIGNAL(medEQChange(int)), this, SLOT(medChange(int)));
    connect(soundProc, SIGNAL(highEQChange(int)), this, SLOT(highChange(int)));
    connect(soundProc, SIGNAL(volumeChange(int)), ui->sVolume1, SLOT(setValue(int)));
    connect(soundProc, SIGNAL(volumeChange2(int)), ui->sVolume2, SLOT(setValue(int)));
    connect(soundProc, SIGNAL(tempoChange(int)), ui->sSpeed1, SLOT(setValue(int)));
    connect(soundProc, SIGNAL(tempoChange2(int)), ui->sSpeed2, SLOT(setValue(int)));
    connect(soundProc, SIGNAL(lowEQChange2(int)), this, SLOT(lowChange2(int)));
    connect(soundProc, SIGNAL(medEQChange2(int)), this, SLOT(medChange2(int)));
    connect(soundProc, SIGNAL(highEQChange2(int)), this, SLOT(highChange2(int)));
    connect(soundProc, SIGNAL(crossChange(int)), this, SLOT(crossChanger(int)));

    connect(&soundProc->panel1, SIGNAL(timeChange(QString)), ui->lTime, SLOT(setText(QString)));

    connect(ui->pbAddMusic_2, SIGNAL(clicked(bool)), this, SLOT(selectAudio2()));
    connect(ui->action_Open2, SIGNAL(triggered(bool)), this, SLOT(selectAudio2()));
    connect(this, SIGNAL(loadAudio2(QString)), &soundProc->panel2, SLOT(loadAudio(QString)));
    connect(ui->pbSound_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playPause()));
    connect(&soundProc->panel2, SIGNAL(pause()), ui->pbSound_2, SLOT(click()));
    connect(ui->pbStop_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playStop()));
    connect(ui->pbSingleLoop_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoop()));
    connect(ui->pbLoopEnable_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingSet()));
    connect(ui->pbLoopStart_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingStart()));
    connect(ui->pbLoopEnd_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(playLoopingEnd()));

    connect(ui->pbFlag1_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setFlag1()));
    connect(ui->pbFlag2_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setFlag2()));
    connect(ui->pbFlag3_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setFlag3()));
    connect(ui->pbFlag4_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setFlag4()));
    connect(ui->pbUnflag1_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(unsetFlag1()));
    connect(ui->pbUnflag2_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(unsetFlag2()));
    connect(ui->pbUnflag3_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(unsetFlag3()));
    connect(ui->pbUnflag4_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(unsetFlag4()));

    connect(ui->pbLoop1_16_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop1_16()));
    connect(ui->pbLoop1_8_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop1_8()));
    connect(ui->pbLoop1_4_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop1_4()));
    connect(ui->pbLoop1_2_2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop1_2()));
    connect(ui->pbLoop1__2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop1()));
    connect(ui->pbLoop2__2, SIGNAL(clicked(bool)), &soundProc->panel2, SLOT(setLoop2()));

    connect(ui->sLow_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(lowEQ(int)));
    connect(ui->sMedium_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(medEQ(int)));
    connect(ui->sHigh_2, SIGNAL(valueChanged(int)), &soundProc->panel2, SLOT(highEQ(int)));
    connect(ui->sSpeed2,SIGNAL(valueChanged(int)),&soundProc->panel2,SLOT(speedChange(int)));
    connect(ui->sVolume2,SIGNAL(valueChanged(int)),&soundProc->panel2,SLOT(volumeChange(int)));

    connect(&soundProc->panel2, SIGNAL(timeChange(QString)), ui->lTime_2, SLOT(setText(QString)));

    connect(ui->sCrossfader, SIGNAL(valueChanged(int)), this, SLOT(crossFaderChange(int)));

    connect(ui->pbRec, SIGNAL(clicked(bool)), soundProc, SLOT(record()));
    connect(ui->action_Export, SIGNAL(triggered(bool)), this, SLOT(onExport()));
    connect(this, SIGNAL(startExport(QString)), Export, SLOT(exportFile(QString)));

    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*,int)));
    connect(ui->customPlot_2, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)), this, SLOT(graphClicked2(QCPAbstractPlottable*,int)));

    //AKCJE
    //sygnaly do zapisywania i wczytywania akcji
    connect(ui->pbActionSave, SIGNAL(clicked(bool)), this, SLOT(saveAction()));
    connect(this, SIGNAL(saveActionToFile(QString)), &soundProc->action, SLOT(saveActionToFile(QString)));

    connect(ui->pbActionLoad, SIGNAL(clicked(bool)), this, SLOT(loadAction()));
    connect(this, SIGNAL(loadActionFromFile(QString)), &soundProc->action, SLOT(loadActionFromFile(QString)));

    connect(ui->pbRecord, SIGNAL(clicked(bool)), &soundProc->action, SLOT(record()));
    connect(ui->pbRun, SIGNAL(clicked(bool)), &soundProc->action, SLOT(run()));

    connect(&soundProc->panel1, SIGNAL(writeToFile(quint64,quint64,quint64)), &soundProc->action, SLOT(writePanel1(quint64,quint64,quint64)));
    connect(&soundProc->panel2, SIGNAL(writeToFile(quint64,quint64,quint64)), &soundProc->action, SLOT(writePanel2(quint64,quint64,quint64)));
}
//------------------------------------------------------------
void MainWindow::setupSoundGraph(QCustomPlot *customPlot)
{

  customPlot->addGraph();
  customPlot->addGraph();
  customPlot->addGraph();
  customPlot->graph(0)->setPen(QPen(QColor(255, 120, 5)));
  //customPlot->setBackground(QColor(QWidget::palette().color(QWidget::backgroundRole())));
  customPlot->setBackground(QColor(54, 54, 54));

  //stworzenie i ustawienie wskaznika do pokazywania aktualnego czasu utworu
    trackPointer = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    trackPointer->setWidth(0.025);
    trackPointer->setPen(QPen(QColor(Qt::white)));
    trackPointer->setBrush(QBrush(QBrush(QColor(Qt::white))));

    QColor color1 = QColor(Qt::red);
    color1.setAlpha(50);
    QColor color2 = QColor(Qt::white);
    color2.setAlpha(20);
    barLoopStart_1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    barLoopStart_1->setWidth(0.025);
    barLoopStart_1->setPen(QPen(QColor(color2)));
    barLoopStart_1->setBrush(QBrush(QBrush(color2)));

    barLoopEnd_1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    barLoopEnd_1->setWidth(0.025);
    barLoopEnd_1->setPen(QPen(QColor(color2)));
    barLoopEnd_1->setBrush(QBrush(QBrush(color2)));

    color2 = QColor(Qt::green);
    color2.setAlpha(50);

    QColor colors[4];
    colors[0] = QColor(Qt::red);
    colors[1] = QColor(Qt::green);
    colors[2] = QColor(Qt::blue);
    colors[3] = QColor(Qt::yellow);
    for(int i = 0; i < 4; i++) {
        returnBar[i] = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
        returnBar[i]->setWidth(0.025);
        colors[i].setAlpha(150);
        returnBar[i]->setPen(QPen(QColor(colors[i])));
        returnBar[i]->setBrush(QBrush(QBrush(colors[i])));
        returnBar[i]->setVisible(false);
    }

    customPlot->graph(1)->setPen(QPen(Qt::NoPen));
    customPlot->graph(1)->setBrush(QBrush(QBrush(color1)));
    customPlot->graph(2)->setPen(QPen(Qt::NoPen));
    customPlot->graph(2)->setBrush(QBrush(QBrush(color1)));

    customPlot->yAxis->setRange(-100000, 100000);
    customPlot->yAxis->setVisible(false);
    customPlot->yAxis2->setVisible(false);
    customPlot->xAxis2->setVisible(false);
    customPlot->xAxis->setVisible(false);

    //tworze po dwa elementy dla vectora odpowiadajacego za wskaznik pozycji utworu,
    //jeden el dla czesci dodatniej wskzanika, drugi dla ujemnej
    x1.push_back(0);   x1.push_back(0);
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
    yReturn.push_back(100000);
    yReturn.push_back(-100000);
    xReturn.push_back(0);
    xReturn.push_back(0);

    ui->customPlot->graph(1)->setVisible(false);
    ui->customPlot->graph(2)->setVisible(false);

  connect(&dataTimer, SIGNAL(timeout()), this, SLOT(bracketDataSlot()));
  dataTimer.start(100); // ustawinie timera do odswiezania danych
}

void MainWindow::bracketDataSlot()
{
    //jezeli utwor zaladoany to rysuje wykres
    if(soundProc->panel1.audioReady){

        ui->customPlot->xAxis->setRange(0, soundProc->panel1.audioLength);
        int n = soundProc->panel1.audioLength * (48000 * 2) + 1;
        static QVector<double> x, y;

      static int prevI = 0;
      quint64 actPos = prevI * 3000;
    for (int i=1; actPos<n/sizeof(qint16) && i < 50; i++, prevI++)
      {
        if(actPos > soundProc->panel1.channel1->size()/sizeof(qint16))
            break;
        //dziele przez czestotliwosc zeby zsynchronizowac osX z czasem
        x.push_back(actPos/48000.);
          //pobieram i dodaje probki z kanalu 1 i 2
        y.push_back(*(reinterpret_cast<qint16*>(soundProc->panel1.channel1->data())+actPos)
                           +*(reinterpret_cast<qint16*>(soundProc->panel1.channel2->data())+actPos));
        actPos += 3000;

        if(actPos % 96 == 0) //96
        {
          ui->customPlot->graph(0)->setData(x, y);
          ui->customPlot->replot();
       }
    }

      ui->customPlot->replot();

      if(actPos>=n/sizeof(qint16)){
          soundProc->panel1.plot = true;
          soundProc->panel1.audioReady = false;
          prevI = 0;
          x.clear();
          y.clear();
      }
    }

    for(int i = 0; i < 4; i++) {
        if(soundProc->panel1.flags[i]) {
            xReturn[0] = xReturn[1] = soundProc->panel1.flagPos[i]/48000;
            returnBar[i]->setData(xReturn, yReturn);
            returnBar[i]->setVisible(true);
            ui->customPlot->replot();
        }
        else {
            returnBar[i]->setVisible(false);
        }
    }

//  if(soundProc->panel1.isFlagSet)
//  {
//    xReturn[0] = soundProc->panel1.returnFlag/48000;
//    xReturn[1] = soundProc->panel1.returnFlag/48000;
//    returnBar->setData(xReturn, yReturn);
//    returnBar->setVisible(true);
//    ui->customPlot->replot();
//  }

  if(soundProc->panel1.isLoopStartSet){
      xStart_1[0]=soundProc->panel1.loopingStart/48000;
      xStart_1[1]=soundProc->panel1.loopingStart/48000;
      barLoopStart_1->setData(xStart_1, yStart_1);
      barLoopStart_1->setVisible(true);
      ui->customPlot->replot();
  }

  if(soundProc->panel1.isLoopEndSet){
      xEnd_1[0]=soundProc->panel1.loopingEnd/48000;
      xEnd_1[1]=soundProc->panel1.loopingEnd/48000;
      barLoopEnd_1->setData(xEnd_1, yEnd_1);
  }

  if(soundProc->panel1.isLoopingSet)
  {
      QColor color1;

      if(soundProc->panel1.isLoopingActive)
      {
          color1 = QColor(Qt::red);
          color1.setAlpha(50);
      }
      else
      {
          color1 = QColor(Qt::white);
          color1.setAlpha(50);

      }
      barLoopStart_1->setPen(QPen(QColor(color1)));
      barLoopEnd_1->setPen(QPen(QColor(color1)));
      ui->customPlot->graph(1)->setBrush(QBrush(QBrush(color1)));
      ui->customPlot->graph(2)->setBrush(QBrush(QBrush(color1)));
      barLoopStart_1->setVisible(false);
      barLoopEnd_1->setVisible(false);
      double start =  xStart_1[0]=soundProc->panel1.loopingStart/48000;
      double end =  xEnd_1[0]=soundProc->panel1.loopingEnd/48000;
        xfill[0] = (start);
        yfill[0] = (100000);
        xfill[1]=(end);
        yfill[1] = (100000);
        ui->customPlot->graph(1)->setData(xfill,yfill);

        xfill[0] = start;
        yfill[0] = -100000;
        xfill[1] = end;
        yfill[1] = -100000;
        ui->customPlot->graph(2)->setData(xfill,yfill);

        ui->customPlot->graph(1)->setVisible(true);
        ui->customPlot->graph(2)->setVisible(true);
        ui->customPlot->replot();
  }
  else
  {
      ui->customPlot->graph(1)->setVisible(false);
      ui->customPlot->graph(2)->setVisible(false);
      barLoopEnd_1->setVisible(false);
      ui->customPlot->replot();
  }


  if(soundProc->panel1.isPlayed)
  {

    //to odpowiada za przesuwanie sie wykresu podczas odtwarzania
    x1[0] = soundProc->panel1.actPos/48000;
    x1[1]=  soundProc->panel1.actPos/48000;
    trackPointer->setData(x1, y2);
    ui->customPlot->replot();
  }

}


void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{

  double czas = plottable->interface1D()->dataMainKey(dataIndex);  //TO JEST OS X - sekundy

    //klikniecie poza obszar loopingu zawsze ustawia looping na false
  if(czas*48000 < soundProc->panel1.loopingStart || czas*48000 > soundProc->panel1.loopingEnd)
      soundProc->panel1.isLoopingActive = false;
  soundProc->panel1.actPos = czas*48000;
  soundProc->panel1.realPosition = czas*48000;
  x1[0] = czas;
  x1[1] = czas;
  trackPointer->setData(x1, y2);
  ui->customPlot->replot();

}
//-----------GRAPH 1--------------------------------------------------

void MainWindow::setupSoundGraph2(QCustomPlot *customPlot)
{

  QCPGraph *graph = customPlot->addGraph();
  graph->setPen(QPen(QColor(66, 134 ,244)));
  customPlot->setBackground(QColor(54, 54, 54));
  //stworzenie i ustawienie wskaznika do pokazywania aktualnego czasu utworu
  bars2 = new QCPBars(ui->customPlot_2->xAxis, ui->customPlot_2->yAxis);
  bars2->setWidth(0.025);
  bars2->setPen(QPen(QColor(Qt::white)));
  bars2->setBrush(QBrush(QBrush(QColor(Qt::white))));


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

  dataTimer2.start(100); // ustawinie timera do odswiezania danych
}

void MainWindow::bracketDataSlot2()
{

  if(soundProc->panel2.audioReady){

      ui->customPlot_2->xAxis->setRange(0, soundProc->panel2.audioLength);
      int n = soundProc->panel2.audioLength * (48000 * 2) + 1;

      //ui->customPlot_2->xAxis->setRange(0,(soundProc->panel2.channel1->size() )/ (48000 * 2) + 1);
      //int n = soundProc->panel2.channel1->size();
      static QVector<double> xII, yII;
      static int prevI = 0;
      quint64 actPos = prevI * 3000;

  for (int i=1; actPos<n/sizeof(qint16) && i < 50; i++, prevI++)
    {
      if(actPos > soundProc->panel2.channel1->size()/sizeof(qint16))
          break;
      xII.push_back(actPos/48000.);  //dziele przez czestotliwosc zeby zsynchronizowac osX z czasem
      //pobieram i dodaje probki z kanalu 1 i 2, nie wiem czy to jest dobre ale nie bedziemy
      //chyba rysowac dwoch kanalow osobno xD
      yII.push_back(*(reinterpret_cast<qint16*>(soundProc->panel2.channel1->data())+actPos)
              +*(reinterpret_cast<qint16*>(soundProc->panel2.channel2->data())+actPos));
      actPos += 3000;
      if(actPos % 96 == 0){
        ui->customPlot_2->graph()->setData(xII, yII);
        ui->customPlot_2->replot();
      }

  }

   ui->customPlot_2->replot();

  //ustawiam dane do rysowania i wskaznik pozycji utworu na 0
  //x2[0] = 0;
  //x2[1] = 0;
  //bars2->setData(x2, y1);
  //xStart_2[0]=0;
  //xStart_2[1]=0;
  //barLoopStart_2->setData(xStart_2, yStart_2);
  //xEnd_2[0]=0;
  //xEnd_2[1]=0;
  //barLoopEnd_2->setData(xEnd_2, yEnd_2);
  //ui->customPlot_2->replot();
  //soundProc->panel2.plot = true;
  if(actPos>=n/sizeof(qint16)){
      //soundProc->panel2.plot = true;
      soundProc->panel2.audioReady = false;
      prevI = 0;
      xII.clear();
      yII.clear();
  }
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
  soundProc->panel2.realPosition = czas*48000;
  x2[0] = czas;
  x2[1] = czas;
  bars2->setData(x2, y1);
  ui->customPlot_2->replot();

}
//----------PLOTING------------------------------------------------------



void MainWindow::selectAudio() {
    QString filename = QFileDialog::getOpenFileName(this,
        tr("Open file"), "/home/", tr("Music Files (*.mp3 *.wav)"));

    if(filename == "") return;

    ui->laudio->setText(filename.split('/').last());
    emit loadAudio(filename);
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
    if(soundProc->panel1.audioReady)
        emit soundProc->panel1.writeToFile(soundProc->Actions::cross, soundProc->panel1.actPos,value);
    else if(soundProc->panel2.audioReady)
        emit soundProc->panel2.writeToFile(soundProc->Actions::cross, soundProc->panel2.actPos,value);
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

void MainWindow::onExport() {

    //wybor lokalizacji zapisywanego pliku audio
    QString selectedFilter;
    QString filename = QFileDialog::getSaveFileName(this,
        tr("Export"), "/home", tr("audio(*.wav)"),&selectedFilter);

    if(filename.count() != 0){
        filename += ".wav";

        emit startExport(filename);
    }

}
//------------------------------------------------------------

MainWindow::~MainWindow()
{
    th_soundProc.quit();
    th_soundProc.wait();
    delete ui;
}
