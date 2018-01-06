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
    explicit Action(QObject *parent = nullptr);
    QVector<quint64> buffer;
    QVector<quint64> buffer2;
    QVector<quint64> loadBuffer;
signals:

public slots:
    void saveActionToFile(QString fileName);
    void writePanel1(quint64 type, quint64 position, quint64 value);
    void writePanel2(quint64 type, quint64 position, quint64 value);
    void loadActionFromFile(QString fileName);
};

#endif // ACTION_H
