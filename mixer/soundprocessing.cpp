#include "soundprocessing.h"
//============================================================
SoundProcessing::SoundProcessing(QObject *parent) : QObject(parent)
{
    abort = false;
    rate = 1;
    crossFader = 50;

    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleRate(48000);
    format.setSampleSize(16);

    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    audioOutput->setBufferSize(1024);
    audioDevice = audioOutput->start();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));
    timer->start(1);
    connect(this,SIGNAL(startDownload(QString)),this,SLOT(download(QString)));
}
//------------------------------------------------------------
void SoundProcessing::play() {

    if(abort) timer->stop();
    if(!timer->isActive()) return;

    QByteArray output;

    panel1.process(buffer1, 512);
    panel2.process(buffer2, 512);


    doActions(panel1.actPos, panel2.actPos);


    for(int i = 0; i < 1024; i++) {
        rate += 0.0000001;
        if(rate > 1) rate = 1;

        if(crossFader <= 50)
            buffer2[i] *= crossFader/50.;
        else
            buffer1[i] *= 1-(crossFader - 50)/50.;

        double y = buffer1[i] + buffer2[i];

        if(abs(y)*rate > 30000) {
            rate = abs(30000/y);
        }

        qint16 sample = y*rate;
        output.append(reinterpret_cast<char*>(&sample), sizeof(qint16));
    }

    //wpisuj do output1 dopiero gdy zacznie być odtwarzany jakis plik:
    int y = output.toHex().count('0');
    if(y != 1024 )
        output1.insert(output1.size(),output);

    qint64 written = 0;
    while((written += audioDevice->write(output.right(output.size()-written))) < output.size());

}
void SoundProcessing::download(QString filename){
    qDebug() << " Downloading started " ;
    QFile* file= new QFile(QStringLiteral("%1.wav").arg(filename));
    int i = 1;
    while(file->exists()){
        QString name = QStringLiteral("%1%2.wav").arg(filename).arg(i);
        file = new QFile(name);
        i++;
    }
    file->open(QIODevice::Append);
    //wpisanie headera formatu WAVE do pliku
    writeWavHeader(file);
    //wpisanie danych z dzwiekiem
    file->write(output1);
    file->close();

    emit downloadReady();
    qDebug() << "ready";

}


void SoundProcessing::writeWavHeader( QFile * file )
{


    QDataStream out(file);
    out.setByteOrder(QDataStream::LittleEndian);

    // RIFF chunk
    out.writeRawData("RIFF", 4);
    out << quint32(0); // Placeholder for the RIFF chunk size (filled by close())
    out.writeRawData("WAVE", 4);

    // Format description chunk
    out.writeRawData("fmt ", 4);
    out << quint32(16); // "fmt " chunk size (always 16 for PCM)
    out << quint16(1); // data format (1 => PCM)
    out << quint16(format.channelCount());
    out << quint32(format.sampleRate());
    out << quint32(format.sampleRate() * format.channelCount()
                   * format.sampleSize() / 8 ); // bytes per second
    out << quint16(format.channelCount() * format.sampleSize() / 8); // Block align
    out << quint16(format.sampleSize()); // Significant Bits Per Sample

    // Data chunk
    out.writeRawData("data", 4);
    out << quint32(0); // Placeholder for the data chunk size (filled by close())

}

void SoundProcessing::doActions(quint64 actPos1, quint64 actPos2)
{
    if(action.actionLoaded && action.isRunning){  //sprawdzam czy bufer jest gotowy
        if(action.loadBuffer[0] > 0) { //czy są akcje dla panelu 1
            if(action.p1 >= action.beg2) //czy wskaźnik nie przeskoczył swojego zakresu
                action.p1 = action.beg2-3; //jeśli tak to ustaw na ostatni element

            //ustawiam wskaźniki w odpowiednie miejsce
            while(action.p1 > action.beg1 && actPos1 < action.loadBuffer[action.p1+1]) {
                action.p1-=3;
            }

            while(action.p1 < action.beg2-3 && actPos1 >= action.loadBuffer[action.p1+4]) {
                action.p1+=3;
            }

            //wykonuję akcję z konkretnego zakresu
            while(action.p1 < action.beg2 && actPos1 >= action.loadBuffer[action.p1+1] && actPos1-512 < action.loadBuffer[action.p1+1])
            {
                int type = action.loadBuffer[action.p1];

                //switch od tego co ma sie zmieniac
                switch (type) {
                case WN_true:
                    panel1.isWhiteNoise = true;
                    action.p1 += 3; //przesuwam o 3 zeby dostac sie do kolejnego typu akcji
                    break;
                case WN_false:
                    panel1.isWhiteNoise = false;
                    action.p1 += 3;
                    break;
                case low:
                    emit lowEQChange(action.loadBuffer[action.p1+2]);
                    action.p1 += 3;
                    break;
                case med:
                    emit medEQChange(action.loadBuffer[action.p1+2]);
                    action.p1 += 3;
                    break;
                case high:
                    emit highEQChange(action.loadBuffer[action.p1+2]);
                    action.p1 += 3;
                    break;
                case cross:
                    crossFader = action.loadBuffer[action.p1+2];
                    emit crossChange(action.loadBuffer[action.p1+2]);
                    action.p1 += 3;
                    break;
                default:
                    break;
                }
            }
        }

        if(action.beg2 < action.loadBuffer.size()) { //czy są akcje dla panelu 2
            if(action.p2 >= action.loadBuffer.size()) //czy wskaźnik nie przeskoczył swojego zakresu
                action.p2 = action.loadBuffer.size()-3; //jeśli tak to ustaw na ostatni element

            //ustawiam wskaźniki w odpowiednie miejsce
            while(action.p2 > action.beg2 && actPos2 < action.loadBuffer[action.p2+1]) {
                action.p2-=3;
            }

            while(action.p2 < action.loadBuffer.size()-3 && actPos2 >= action.loadBuffer[action.p2+4]) {
                action.p2+=3;
            }

            //wykonuję akcję z konkretnego zakresu
            while(action.p2 < action.loadBuffer.size() && actPos2 >= action.loadBuffer[action.p2+1] && actPos2-512 < action.loadBuffer[action.p2+1])
            {
                int type = action.loadBuffer[action.p2];

                //switch od tego co ma sie zmieniac
                switch (type) {
                case WN_true:
                    panel2.isWhiteNoise = true;
                    action.p2 += 3; //przesuwam o 3 zeby dostac sie do kolejnego typu akcji
                    break;
                case WN_false:
                    panel2.isWhiteNoise = false;
                    action.p2 += 3;
                    break;
                case low:
                    emit lowEQChange2(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                case med:
                    emit medEQChange2(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                case high:
                    emit highEQChange2(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                case cross:
                    crossFader = action.loadBuffer[action.p2+2];
                    emit crossChange(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                default:
                    break;
                }
            }
        }
    }
}
