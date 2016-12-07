#ifndef SNAKE_H
#define SNAKE_H

#include <QList>
#include <QPoint>

class Snake
{
    int id;
    int length;//довжина змійки
    int vector;//напрямок руху
    QList<QPoint *> snakePoints;//координати всіх квадратів змійки
public:
    Snake();
    ~Snake(){}

    void setLength(int length);//вибираємо довжину
    void setStartPoint(QPoint *some);//задаємо початкову точку змії
    void setStartPoint(int x, int y);//задаємо початкову точку змії
    void setVector(int vector);//задаємо напрямок
    void setId(int id);

    int getId();
    int getVector();//повертає напрямок руху змії
    int getLength();//повертає довжину змії
    QPoint *getHead();//повертає початкову точку змії
    QList<QPoint *> getSnakePoints();//повертає всі точки змії

    QPoint *moving();// Рухаємо змію
    void movingWithEating();//рухаємо змію і збільшуємо довжину
};

#endif // SNAKE_H
