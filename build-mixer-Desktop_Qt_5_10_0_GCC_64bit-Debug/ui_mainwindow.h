/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Open2;
    QAction *actionQuit;
    QWidget *centralWidget;
    QPushButton *pbSound;
    QPushButton *pbYes;
    QPushButton *pbNo;
    QPushButton *pbAddMusic;
    QSlider *sLow;
    QSlider *sMedium;
    QSlider *sHigh;
    QLabel *label;
    QLabel *laudio;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pbNo_2;
    QLabel *laudio_2;
    QLabel *label_5;
    QSlider *sHigh_2;
    QSlider *sMedium_2;
    QLabel *label_6;
    QPushButton *pbYes_2;
    QPushButton *pbAddMusic_2;
    QSlider *sLow_2;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pbSound_2;
    QLabel *lTime;
    QLabel *lTime_2;
    QSlider *sCrossfader;
    QLabel *label_9;
    QCustomPlot *customPlot;
    QCustomPlot *customPlot_2;
    QPushButton *pbActionSave;
    QPushButton *pbActionLoad;
    QPushButton *pbDownload;
    QLabel *file1_ready;
    QLabel *file2_ready;
    QLabel *download_ready;
    QPushButton *pbStop_1;
    QPushButton *pbStop_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(690, 567);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("open.png");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        action_Open->setIcon(icon);
        action_Open2 = new QAction(MainWindow);
        action_Open2->setObjectName(QStringLiteral("action_Open2"));
        action_Open2->setIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pbSound = new QPushButton(centralWidget);
        pbSound->setObjectName(QStringLiteral("pbSound"));
        pbSound->setGeometry(QRect(30, 70, 41, 31));
        pbYes = new QPushButton(centralWidget);
        pbYes->setObjectName(QStringLiteral("pbYes"));
        pbYes->setGeometry(QRect(30, 140, 89, 25));
        pbNo = new QPushButton(centralWidget);
        pbNo->setObjectName(QStringLiteral("pbNo"));
        pbNo->setGeometry(QRect(30, 180, 89, 25));
        pbAddMusic = new QPushButton(centralWidget);
        pbAddMusic->setObjectName(QStringLiteral("pbAddMusic"));
        pbAddMusic->setGeometry(QRect(30, 10, 21, 25));
        sLow = new QSlider(centralWidget);
        sLow->setObjectName(QStringLiteral("sLow"));
        sLow->setGeometry(QRect(180, 40, 16, 160));
        sLow->setMaximum(100);
        sLow->setValue(50);
        sLow->setSliderPosition(50);
        sLow->setTracking(false);
        sLow->setOrientation(Qt::Vertical);
        sMedium = new QSlider(centralWidget);
        sMedium->setObjectName(QStringLiteral("sMedium"));
        sMedium->setGeometry(QRect(220, 40, 16, 160));
        sMedium->setMaximum(100);
        sMedium->setValue(50);
        sMedium->setSliderPosition(50);
        sMedium->setTracking(false);
        sMedium->setOrientation(Qt::Vertical);
        sHigh = new QSlider(centralWidget);
        sHigh->setObjectName(QStringLiteral("sHigh"));
        sHigh->setGeometry(QRect(260, 40, 16, 160));
        sHigh->setMaximum(100);
        sHigh->setValue(50);
        sHigh->setSliderPosition(50);
        sHigh->setTracking(false);
        sHigh->setOrientation(Qt::Vertical);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 110, 101, 20));
        laudio = new QLabel(centralWidget);
        laudio->setObjectName(QStringLiteral("laudio"));
        laudio->setGeometry(QRect(60, 10, 241, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 210, 31, 17));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 210, 31, 17));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(250, 210, 31, 17));
        pbNo_2 = new QPushButton(centralWidget);
        pbNo_2->setObjectName(QStringLiteral("pbNo_2"));
        pbNo_2->setGeometry(QRect(370, 180, 89, 25));
        laudio_2 = new QLabel(centralWidget);
        laudio_2->setObjectName(QStringLiteral("laudio_2"));
        laudio_2->setGeometry(QRect(400, 10, 241, 17));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(590, 210, 31, 17));
        sHigh_2 = new QSlider(centralWidget);
        sHigh_2->setObjectName(QStringLiteral("sHigh_2"));
        sHigh_2->setGeometry(QRect(600, 40, 16, 160));
        sHigh_2->setMaximum(100);
        sHigh_2->setValue(50);
        sHigh_2->setTracking(false);
        sHigh_2->setOrientation(Qt::Vertical);
        sMedium_2 = new QSlider(centralWidget);
        sMedium_2->setObjectName(QStringLiteral("sMedium_2"));
        sMedium_2->setGeometry(QRect(560, 40, 16, 160));
        sMedium_2->setMaximum(100);
        sMedium_2->setValue(50);
        sMedium_2->setTracking(false);
        sMedium_2->setOrientation(Qt::Vertical);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(370, 110, 101, 20));
        pbYes_2 = new QPushButton(centralWidget);
        pbYes_2->setObjectName(QStringLiteral("pbYes_2"));
        pbYes_2->setGeometry(QRect(370, 140, 89, 25));
        pbAddMusic_2 = new QPushButton(centralWidget);
        pbAddMusic_2->setObjectName(QStringLiteral("pbAddMusic_2"));
        pbAddMusic_2->setGeometry(QRect(370, 10, 21, 25));
        sLow_2 = new QSlider(centralWidget);
        sLow_2->setObjectName(QStringLiteral("sLow_2"));
        sLow_2->setGeometry(QRect(520, 40, 16, 160));
        sLow_2->setMaximum(100);
        sLow_2->setValue(50);
        sLow_2->setTracking(false);
        sLow_2->setOrientation(Qt::Vertical);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(550, 210, 31, 17));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(510, 210, 31, 17));
        pbSound_2 = new QPushButton(centralWidget);
        pbSound_2->setObjectName(QStringLiteral("pbSound_2"));
        pbSound_2->setGeometry(QRect(370, 70, 41, 31));
        lTime = new QLabel(centralWidget);
        lTime->setObjectName(QStringLiteral("lTime"));
        lTime->setGeometry(QRect(30, 40, 81, 17));
        lTime_2 = new QLabel(centralWidget);
        lTime_2->setObjectName(QStringLiteral("lTime_2"));
        lTime_2->setGeometry(QRect(370, 40, 81, 17));
        sCrossfader = new QSlider(centralWidget);
        sCrossfader->setObjectName(QStringLiteral("sCrossfader"));
        sCrossfader->setGeometry(QRect(250, 270, 160, 16));
        sCrossfader->setMaximum(100);
        sCrossfader->setValue(50);
        sCrossfader->setSliderPosition(50);
        sCrossfader->setTracking(false);
        sCrossfader->setOrientation(Qt::Horizontal);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(300, 250, 81, 17));
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setEnabled(true);
        customPlot->setGeometry(QRect(30, 289, 261, 91));
        customPlot_2 = new QCustomPlot(centralWidget);
        customPlot_2->setObjectName(QStringLiteral("customPlot_2"));
        customPlot_2->setEnabled(true);
        customPlot_2->setGeometry(QRect(390, 290, 261, 91));
        pbActionSave = new QPushButton(centralWidget);
        pbActionSave->setObjectName(QStringLiteral("pbActionSave"));
        pbActionSave->setGeometry(QRect(390, 410, 89, 25));
        pbActionLoad = new QPushButton(centralWidget);
        pbActionLoad->setObjectName(QStringLiteral("pbActionLoad"));
        pbActionLoad->setGeometry(QRect(200, 410, 89, 25));
        pbDownload = new QPushButton(centralWidget);
        pbDownload->setObjectName(QStringLiteral("pbDownload"));
        pbDownload->setGeometry(QRect(300, 480, 80, 22));
        file1_ready = new QLabel(centralWidget);
        file1_ready->setObjectName(QStringLiteral("file1_ready"));
        file1_ready->setGeometry(QRect(100, 40, 52, 14));
        file2_ready = new QLabel(centralWidget);
        file2_ready->setObjectName(QStringLiteral("file2_ready"));
        file2_ready->setGeometry(QRect(450, 40, 52, 14));
        download_ready = new QLabel(centralWidget);
        download_ready->setObjectName(QStringLiteral("download_ready"));
        download_ready->setGeometry(QRect(320, 510, 52, 14));
        pbStop_1 = new QPushButton(centralWidget);
        pbStop_1->setObjectName(QStringLiteral("pbStop_1"));
        pbStop_1->setGeometry(QRect(80, 70, 41, 31));
        pbStop_2 = new QPushButton(centralWidget);
        pbStop_2->setObjectName(QStringLiteral("pbStop_2"));
        pbStop_2->setGeometry(QRect(420, 70, 41, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 690, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Open2);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_Open->setText(QApplication::translate("MainWindow", "&Load Track 1", nullptr));
        action_Open2->setText(QApplication::translate("MainWindow", "&Load Track 2", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        pbSound->setText(QApplication::translate("MainWindow", "Play", nullptr));
        pbYes->setText(QApplication::translate("MainWindow", "Enable", nullptr));
        pbNo->setText(QApplication::translate("MainWindow", "Disable", nullptr));
        pbAddMusic->setText(QApplication::translate("MainWindow", "+", nullptr));
        label->setText(QApplication::translate("MainWindow", "white noise :)", nullptr));
        laudio->setText(QApplication::translate("MainWindow", "audio 1", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Low", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Med", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "High", nullptr));
        pbNo_2->setText(QApplication::translate("MainWindow", "Disable", nullptr));
        laudio_2->setText(QApplication::translate("MainWindow", "audio 2", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "High", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "white noise :)", nullptr));
        pbYes_2->setText(QApplication::translate("MainWindow", "Enable", nullptr));
        pbAddMusic_2->setText(QApplication::translate("MainWindow", "+", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "Med", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "Low", nullptr));
        pbSound_2->setText(QApplication::translate("MainWindow", "Play", nullptr));
        lTime->setText(QApplication::translate("MainWindow", "0:00/0:00", nullptr));
        lTime_2->setText(QApplication::translate("MainWindow", "0:00/0:00", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "Crossfader", nullptr));
        pbActionSave->setText(QApplication::translate("MainWindow", "Save Action", nullptr));
        pbActionLoad->setText(QApplication::translate("MainWindow", "Load Action", nullptr));
        pbDownload->setText(QApplication::translate("MainWindow", "Download", nullptr));
        file1_ready->setText(QString());
        file2_ready->setText(QString());
        download_ready->setText(QString());
        pbStop_1->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        pbStop_2->setText(QApplication::translate("MainWindow", "Stop", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
