#ifndef EXPORTING_H
#define EXPORTING_H

#include "soundprocessing.h"

class Exporting : public QObject
{
    Q_OBJECT
private:
     SoundProcessing* soundProc;

public:
     explicit Exporting(SoundProcessing* soundprocessing, QObject *parent = nullptr);

     void writeWavHeader( QFile * file );
     void closeWavHeader( QFile * file );

signals:
     void exportReady();

public slots:
     void exportFile(QString filename);

};

#endif // EXPORTING_H
