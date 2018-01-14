#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include "qcustomplot.h"
#include "soundprocessing.h"
#include "mixpanel.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); 
    QTimer dataTimer;
    QTimer dataTimer2;

    void setupSoundGraph(QCustomPlot *customPlot);
    void setupSoundGraph2(QCustomPlot *customPlot);

    QCPBars *trackPointer;
    QVector<double> x1,y2;
    QCPBars *bars2;
    QVector<double> x2,y1;
    QCPBars *barLoopStart_1;
    QVector<double> xStart_1,yStart_1;
    QCPBars *barLoopEnd_1;
    QVector<double> xEnd_1,yEnd_1;
    QCPBars *barLoopStart_2;
    QVector<double> xStart_2,yStart_2;
    QCPBars *barLoopEnd_2;
    QVector<double> xEnd_2,yEnd_2;
    QVector<double> xfill,yfill;
    QCPBars *returnBar;
    QVector<double> xReturn,yReturn;
    double speed;
    double volume;
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SoundProcessing* soundProc;
    QThread th_soundProc;
    QThread th_soundGraph;

signals:
    void loadAudio(QString filename);
    void loadAudio2(QString filename);
    void saveActionToFile(QString fileName);
    void loadActionFromFile(QString fileName);
    void startExport(QString filename);


public slots:
    //----PLOTING------------
     void bracketDataSlot();
     void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
     void bracketDataSlot2();
     void graphClicked2(QCPAbstractPlottable *plottable, int dataIndex);
    //--------------------
    void selectAudio();
    void selectAudio2();
    void crossFaderChange(int value);
    void saveAction();
    void loadAction();

    void lowChange(int value);
    void medChange(int value);
    void highChange(int value);
    void lowChange2(int value);
    void medChange2(int value);
    void highChange2(int value);
    void crossChanger(int value);

    void onExport();
};

#endif // MAINWINDOW_H
