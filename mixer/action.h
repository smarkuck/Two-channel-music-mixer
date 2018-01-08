#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QDebug>

class Action : public QObject
{
    Q_OBJECT
public:
    Action();
    QVector<quint64> buffer;
    QVector<quint64> buffer2;
    QVector<quint64> loadBuffer;
    int p1, p2, beg1, beg2;
    bool actionLoaded;
    bool isRunning;
    bool isRecording;
signals:

public slots:
    void saveActionToFile(QString fileName);
    void writePanel1(quint64 type, quint64 position, quint64 value);
    void writePanel2(quint64 type, quint64 position, quint64 value);
    void loadActionFromFile(QString fileName);
    void record();
    void run();
};

#endif // ACTION_H
