#include "soundprocessing.h"
//============================================================
SoundProcessing::SoundProcessing(QObject *parent) : QObject(parent)
{
    isRecording = false;

    rate = 1;
    crossFader = 50;

    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleType(QAudioFormat::SignedInt);
    format.setSampleRate(48000);
    format.setSampleSize(16);

    audioOutput = new QAudioOutput(QAudioDeviceInfo::defaultOutputDevice(), format);
    audioOutput->setBufferSize(960);
    audioDevice = audioOutput->start();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(play()));
    timer->setInterval(10);
    timer->start();
}
//------------------------------------------------------------
void SoundProcessing::play() {

    QByteArray output;

    panel1.process(buffer1, 480);
    panel2.process(buffer2, 480);

    launchActions(panel1.actPos, panel2.actPos);


    for(int i = 0; i < 960; i++) {
        rate += 0.000001;
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
    if(isRecording)
        output1.insert(output1.size(),output);

    qint64 written = 0;
    while((written += audioDevice->write(output.right(output.size()-written))) < output.size());
}

void SoundProcessing::record() {
    if(!isRecording)
        output1.clear();

    isRecording = !isRecording;
}

void SoundProcessing::launchActions(quint64 actPos1, quint64 actPos2)
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
                case volume:
                    emit volumeChange(action.loadBuffer[action.p1+2]);
                    action.p1 += 3;
                    break;
                case tempo:
                    emit tempoChange(action.loadBuffer[action.p1+2]);
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
                case volume:
                    emit volumeChange2(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                case tempo:
                    emit tempoChange2(action.loadBuffer[action.p2+2]);
                    action.p2 += 3;
                    break;
                default:
                    break;
                }
            }
        }
    }
}
