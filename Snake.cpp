#include "Snake.h"

Snake::Snake()
{
    this->length = 0;
    this->vector = 2;
    this->id = 0;
}

void Snake::setLength(int length)
{
    this->length = length;
}

void Snake::setStartPoint(QPoint *some)
{
    if(snakePoints.size() > 0)
        this->snakePoints[0] = some;
    else
        snakePoints.push_back(some);
}

void Snake::setStartPoint(int x, int y)
{
    QPoint *tempPoint = new QPoint(x,y);
    this->setStartPoint(tempPoint);
}

void Snake::setId(int id)
{
    this->id = id;
}

int Snake::getId()
{
    return this->id;
}

int Snake::getLength()
{
    return this->length;
}

int Snake::getVector()
{
    return this->vector;
}

QList<QPoint *> Snake::getSnakePoints()
{
    return this->snakePoints;
}

QPoint *Snake::moving()
{
    QPoint *temp = new QPoint();
    temp->setX(snakePoints[0]->x());
    temp->setY(snakePoints[0]->y());
    switch(vector)
    {
    case 0:
        temp->setX(temp->x() - 1);
        break;
    case 1:
        temp->setY(temp->y() - 1);
        break;
    case 2:
        temp->setX(temp->x() + 1);
        break;
    case 3:
        temp->setY(temp->y() + 1);
        break;
    default:
        return temp;
        break;
    }
    this->snakePoints.push_front(temp);
    QPoint *temp2 = new QPoint();
    temp2->setX(snakePoints[snakePoints.size() - 1]->x());
    temp2->setY(snakePoints[snakePoints.size() - 1]->y());
    this->snakePoints.pop_back();
    return temp2;
}

QPoint *Snake::getHead()
{
    return this->snakePoints[0];
}

void Snake::movingWithEating()
{
    QPoint *temp = new QPoint();
    temp->setX(snakePoints[0]->x());
    temp->setY(snakePoints[0]->y());
    switch(vector)
    {
    case 0:
        temp->setX(temp->x() - 1);
        break;
    case 1:
        temp->setY(temp->y() - 1);
        break;
    case 2:
        temp->setX(temp->x() + 1);
        break;
    case 3:
        temp->setY(temp->y() + 1);
        break;
    }

    this->snakePoints.push_front(temp);
    this->length++;
}

void Snake::setVector(int vector)
{
    this->vector = vector;
}
