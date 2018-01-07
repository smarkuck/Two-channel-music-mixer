#ifndef DOWNLOADING_H
#define DOWNLOADING_H

#include "soundprocessing.h"

class Downloading : public QObject
{
    Q_OBJECT
public:
     explicit Downloading(SoundProcessing* soundprocessing, QObject *parent = nullptr);
     SoundProcessing* soundProc;
     void writeWavHeader( QFile * file );
     void writeMp3Header(QString wavFilename);
signals:
     void downloadReady();
public slots:
     void download(QString filename);
};

#endif // DOWNLOADING_H
