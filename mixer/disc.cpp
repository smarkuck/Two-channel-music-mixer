#include "disc.h"

Disc::Disc()
{
    actAngle = 0;
    prevAngle = 0;
}
//---------------------------------------------------
//compute actual angle of rotation
float Disc::getAngle(QPointF p) {
    p.setX(p.x() - width()/2);
    p.setY(p.y() - height()/2);

    float angle = atan2(p.y(), p.x());
    angle *= 180/3.14159265359;

    return angle;
}
//---------------------------------------------------
//rotate disk on mouse move when pressed
void Disc::mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent) {
    float angle = getAngle(mouseEvent->scenePos());

    angle -= actAngle;
    angle += prevAngle;

    if(angle < -180) angle += 360;
    else if(angle > 180) angle -= 360;

    emit rotate(angle);
}
//---------------------------------------------------
void Disc::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    actAngle = getAngle(mouseEvent->scenePos());
    emit start();
}
//---------------------------------------------------
void Disc::mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent) {
    float angle = getAngle(mouseEvent->scenePos());

    angle -= actAngle;
    angle += prevAngle;

    if(angle < -180) angle += 360;
    else if(angle > 180) angle -= 360;

    prevAngle = angle;

    emit stop();
}
