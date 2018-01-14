#ifndef EXPORTING_H
#define EXPORTING_H

#include "soundprocessing.h"

class Exporting : public QObject
{
    Q_OBJECT
public:
     explicit Exporting(SoundProcessing* soundprocessing, QObject *parent = nullptr);
     SoundProcessing* soundProc;
     void writeWavHeader( QFile * file );
     void closeWavHeader( QFile * file );
signals:
     void exportReady();
public slots:
     void exportFile(QString filename);
};

#endif // EXPORTING_H
