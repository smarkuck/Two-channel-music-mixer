#ifndef DISC_H
#define DISC_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <math.h>

//class to control disc rotation
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
    //get actual angle while rotating
    float getAngle(QPointF p);

signals:
    //rotation start
    void start();
    //rotation stop
    void stop();
    void rotate(float angle);

public slots:
};

#endif // DISC_H
