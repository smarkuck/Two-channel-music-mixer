#include "action.h"

Action::Action(QObject *parent) : QObject(parent)
{
    aCounter = 1;
}


void Action::saveActionToFile(QString fileName)
{
    //zapsywanie akcji
    QString name = fileName + ".acn";
    QFile file(name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    out << buffer.size() << "\n";
    for(int i=0; i < buffer.size() ; i++){
        out << buffer[i] << "\n";
    }
    for(int i=0; i < buffer2.size() ; i++){
        out << buffer2[i] << "\n";
    }
    file.close();
    qDebug() << "actions saved";
}

void Action::writePanel2(quint64 type, quint64 position, quint64 value)
{
    buffer2.push_back(type+6);
    buffer2.push_back(position);
    buffer2.push_back(value);
}

void Action::writePanel1(quint64 type,quint64 position, quint64 value)
{
    //Sposob zapisu akcji:
    //loadBuffer[i] - typ akcji
    //loadBuffer[i+1] - pozycja utworu w ktorej ma sie wykonac akcja
    //loadBuffer[i+2] - wartosc zmiany
    buffer.push_back(type);
    buffer.push_back(position);
    buffer.push_back(value);
}

void Action::loadActionFromFile(QString fileName)
{
    loadBuffer.clear();
    int k = 0;
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    while(!file.atEnd()){
        QString line = file.readLine();
        loadBuffer.push_back(line.toInt());
        qDebug() << "read " << loadBuffer[k++];
    }
}

