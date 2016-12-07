#ifndef FIELD_H
#define FIELD_H

#include <QList>
#include <QTime>

#include "Snake.h"

enum{nothing, wall, snakePart, foodPart, snake2Part};

class Field
{
private:
    int width;//Ширина поля
    int height;//Висота поля
    QPoint *food;//точка знаходження їжі
    QList<QList<int> > cells;//матриця
    QList<QPoint *> recentlychanged;//список останніх змін в матриці
public:
    Snake snake;//змія
    Snake snake2;//друга змія

    Field();
    Field(int width, int height, int head_x, int head_y);
    Field(int width, int height);
    ~Field(){}

    void setWidth(int width);//задаємо ширину поля
    void setHeight(int height);//задаємо висоту поля
    void setSize(int width, int height);//задаємо розміри поля
    int getWidth();//повертає ширину поля
    int getHeight();//повертає висоту поля
    int getCell(int x, int y);//повертає значення клітинки
    QList<QPoint *> getRecentlyChanged();//повертає останні зміни
    QList<QList<int> > getCells();//повертає всю матрицю

    bool moveSnake();//рухає змію
    bool moveSnake2();//рухає другу змію
    void placeFood();//розміщає їжу випадковим чином
    int canMove(int x, int y);//перевіряє сусідню клітинку
    void clear();
};

#endif // FIELD_H
