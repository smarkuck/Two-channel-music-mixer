#ifndef DISC_H
#define DISC_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <math.h>

class Disc : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Disc();
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

private:
    float actAngle;
    float prevAngle;
    float getAngle(QPointF p);

signals:
    void start();
    void stop();
    void rotate(float angle);

public slots:
};

#endif // DISC_H
