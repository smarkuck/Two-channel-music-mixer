#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QThread>
#include <QTimer>
#include <disc.h>
#include "qcustomplot.h"
#include "soundprocessing.h"
#include "mixpanel.h"
#include "exporting.h"

namespace Ui {

class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0); 
    ~MainWindow();

    //initial settings of sound graphs
    void setupSoundGraph(QCustomPlot *customPlot);
    void setupSoundGraph2(QCustomPlot *customPlot);

private:
    Ui::MainWindow *ui;
    SoundProcessing* soundProc;
    QThread th_soundProc;
    Exporting* Export;
    QGraphicsPixmapItem* discImg[2];
    Disc* disc[2];
    //pointers of the current position of the song
    QCPBars *trackPointer;
    QCPBars *trackPointer2;
    //vectors containing sound amplitude data
    QVector<double> x1,y2;
    QVector<double> x2,y1;
    //looping flag pointers
    QCPBars *barLoopStart_1;
    QCPBars *barLoopEnd_1;
    QCPBars *barLoopStart_2;
    QCPBars *barLoopEnd_2;
    //vectors containing sound amplitude data for looping
    QVector<double> xStart_1,yStart_1;
    QVector<double> xEnd_1,yEnd_1;
    QVector<double> xStart_2,yStart_2;
    QVector<double> xEnd_2,yEnd_2;
    //vectors containing sound amplitude data for the filled looping area
    QVector<double> xfill,yfill;
    QVector<double> x2fill,y2fill;
    //return looping flag pointers
    QCPBars *returnBar[4];
    QCPBars *returnBar2[4];
    //vectors containing sound amplitude data for return looping flags
    QVector<double> xReturn,yReturn;
    QVector<double> xReturn2,yReturn2;
    //timers for refreshing data
    QTimer dataTimer;
    QTimer dataTimer2;


signals:
    //signals emitted after selecting the song for mixing
    void loadAudio(QString filename);
    void loadAudio2(QString filename);
    //signals emitted during saving / loading actions for re-execution to / from file
    void saveActionToFile(QString fileName);
    void loadActionFromFile(QString fileName);
    
    void startExport(QString filename);

public slots:
    //the function responsible for the changing data of the sound graph
    void bracketDataSlot();
    void bracketDataSlot2();
    //function that supports scrolling the song when clicking on the sound graph
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void graphClicked2(QCPAbstractPlottable *plottable, int dataIndex);
    
    //function that supports scrolling the song while dragging the sound graph with the mouse
    void mouseMove(QMouseEvent *event);
    void mouseMove2(QMouseEvent *event);

    void selectAudio();
    void selectAudio2();
    
    //slot that captures the change in the crossfader slider
    void crossFaderChange(int value);
    
    //save/load actions for re-execution
    void saveAction();
    void loadAction();
    
    //slots responsible for changing the value of eq sliders 
    void lowChange(int value);
    void medChange(int value);
    void highChange(int value);
    void lowChange2(int value);
    void medChange2(int value);
    void highChange2(int value);
    void crossChanger(int value);

    void rotate(float angle);
    void rotate2(float angle);
    
    //record of the mixed song
    void onExport();
};

#endif // MAINWINDOW_H
