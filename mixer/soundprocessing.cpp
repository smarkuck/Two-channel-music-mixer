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
    if(!action.loadBuffer.empty()){  //sprawdzam czy jest pusty bufor z wczytanymi akcjami

        if(actPos1 < action.loadBuffer[2])    //jezeli przesune utwor na poczatek to ustawiam ponowne wykonywanie sie akcji
            action.aCounter = 1;

        if(action.aCounter < action.loadBuffer.size())
        {
            int type = action.loadBuffer[action.aCounter];

            //switch od tego co ma sie zmieniac
            switch (type) {
            case WN_true:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    panel1.isWhiteNoise = true;
                    action.aCounter += 3; //przesuwam o 3 zeby dostac sie do kolejnego typu akcji
                }
                break;
            case WN_false:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    panel1.isWhiteNoise = false;
                    action.aCounter += 3;
                }
                break;
            case low:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    emit lowEQChange(action.loadBuffer[action.aCounter+2]);
                    action.aCounter += 3;
                }
                break;
            case med:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    emit medEQChange(action.loadBuffer[action.aCounter+2]);
                    action.aCounter += 3;
                }
                break;
            case high:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    emit highEQChange(action.loadBuffer[action.aCounter+2]);
                    action.aCounter += 3;
                }
                break;
            case cross:
                if(actPos1 == action.loadBuffer[action.aCounter+1]  ){
                    crossFader = action.loadBuffer[action.aCounter+2];
                    emit crossChange(action.loadBuffer[action.aCounter+2]);
                    action.aCounter += 3;
                }
                break;
            default:
                break;
            }
        }

        //SWITCH PANEL 2
        if(action.loadBuffer.size() > action.loadBuffer[0] )
        {
            static int j=action.loadBuffer[0] + 1;
            //if(actPos2 < action.loadBuffer[action.loadBuffer[0] + 2])    //jezeli przesune utwor na poczatek to ustawiam ponowne wykonywanie sie akcji
             //j = action.loadBuffer[0] + 1;

            if(j < action.loadBuffer.size())
            {
                int type2 = action.loadBuffer[j];
                switch (type2) {
                case WN2_true:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        panel2.isWhiteNoise = true;
                        j += 3;
                    }
                    break;
                case WN2_false:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        panel2.isWhiteNoise = false;
                        j += 3;
                    }
                    break;
                case low2:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        emit lowEQChange2(action.loadBuffer[j+2]);
                        j += 3;
                    }
                    break;
                case med2:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        emit medEQChange2(action.loadBuffer[j+2]);
                        j += 3;
                    }
                    break;
                case high2:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        emit highEQChange2(action.loadBuffer[j+2]);
                        j += 3;
                    }
                    break;
                case cross2:
                    if(actPos2 == action.loadBuffer[j+1]  ){
                        crossFader = action.loadBuffer[j+2];
                        emit crossChange(action.loadBuffer[j+2]);
                        j += 3;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
