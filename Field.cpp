#include "Field.h"

Field::Field()
{
    this->width = 75;
    this->height = 40;
    this->snake.setId(0);
    this->snake2.setId(1);
    this->snake2.setVector(0);
    for(int i = 0; i < width; i++)
    {
        QList<int> tempList;
        this->cells.push_back(tempList);
        for(int j = 0; j < height; j++)
        {
            if(i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                cells[i].push_back(wall);
            }
            else
            {
                cells[i].push_back(nothing);
            }
        }
    }
    cells[5][5] = snakePart;
    cells[50][30] = snake2Part;
    this->snake.setStartPoint(5,5);
    this->snake2.setStartPoint(50,30);
    food = new QPoint();
    placeFood();
}

Field::Field(int width, int height, int head_x, int head_y)
{
    this->width = width;
    this->height = height;
    this->snake.setId(0);
    this->snake2.setId(1);
    this->snake2.setVector(0);
    for(int i = 0; i < width; i++)
    {
        QList<int> tempList;
        this->cells.push_back(tempList);
        for(int j = 0; j < height; j++)
        {
            if(i == head_x && j == head_y)
            {
                cells[i].push_back(snakePart);
            }
            else if(i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                cells[i].push_back(wall);
            }
            else
            {
                cells[i].push_back(nothing);
            }
        }
    }
    food = new QPoint();
    this->cells[head_x][head_y] = snakePart;
    this->cells[width - head_x][height - head_y] = snake2Part;
    this->snake.setStartPoint(head_x, head_y);
    this->snake2.setStartPoint(width - head_x, height - head_y);
    placeFood();
}

Field::Field(int width, int height)
{
    this->snake.setId(0);
    this->snake2.setId(1);
    this->snake2.setVector(0);
    if(width > 14 && height > 14 && width < 100 && height < 50)//звіряємось з максимальними і мінімальними розмірами поля
    {
        this->width = width;
        this->height = height;
    }
    else
    {
        this->width = 20;
        this->height = 20;
    }
    for(int i = 0; i < width; i++)
    {
        QList<int> tempList;
        this->cells.push_back(tempList);
        for(int j = 0; j < height; j++)
        {
            if(i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                this->cells[i].push_back(1);
            }
            else
            {
                this->cells[i].push_back(0);
            }
        }
    }
    food = new QPoint();
    this->cells[5][5] = snakePart;
    this->cells[width - 5][height - 5] = snake2Part;
    this->snake.setStartPoint(5,5);
    this->snake2.setStartPoint(width - 5, height - 5);
    placeFood();
}

void Field::setWidth(int width)
{
    this->width = width;
}

void Field::setHeight(int height)
{
    this->height = height;
}

void Field::setSize(int width, int height)
{
    this->width = width;
    this->height = height;
}

int Field::getWidth()
{
    return this->width;
}

int Field::getHeight()
{
    return this->height;
}

int Field::getCell(int x, int y)
{
    if(x < width && y < height && x >= 0 && y >= 0)
        return cells[x][y];
    else
        return 5;
}

QList<QList<int> > Field::getCells()
{
    return this->cells;
}

void Field::placeFood()
{
    while(1)
    {
        QTime midnight(0,0,0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        int x = qrand() % width;
        qsrand(midnight.secsTo(QTime::currentTime()));
        int y = qrand() % height;
        if(cells[x][y] == nothing)
        {
            cells[x][y] = foodPart;
            food->setX(x);
            food->setY(y);
            break;
        }
    }
}

bool Field::moveSnake()
{
    this->recentlychanged.clear();
    int a = 0;
    int b = 0;
    QPoint *temp;
    switch(this->snake.getVector())//перевіряємо напрямок
    {
    case 0:
        a = -1;
        b = 0;
        break;
    case 1:
        a = 0;
        b = -1;
        break;
    case 2:
        a = +1;
        b = 0;
        break;
    case 3:
        a = 0;
        b = +1;
        break;
    }
    switch(canMove(this->snake.getHead()->x() + a, this->snake.getHead()->y() + b))
    {
    case nothing:
        temp = this->snake.moving();
        this->cells[temp->x()][temp->y()] = nothing;
        break;
    case wall:
        return false;
        break;
    case foodPart:
        this->snake.movingWithEating();
        this->placeFood();
        this->recentlychanged.push_back(food);
        break;
    }
    this->recentlychanged.push_back(temp);
    for(int i = 0; i < snake.getSnakePoints().size(); i++)
    {
        this->cells[snake.getSnakePoints()[i]->x()][snake.getSnakePoints()[i]->y()] = snakePart;
    }
    this->recentlychanged.push_back(snake.getSnakePoints()[0]);
    return true;
}

bool Field::moveSnake2()
{
    int a = 0;
    int b = 0;
    QPoint *temp;
    switch(this->snake2.getVector())//перевіряємо напрямок
    {
    case 0:
        a = -1;
        b = 0;
        break;
    case 1:
        a = 0;
        b = -1;
        break;
    case 2:
        a = +1;
        b = 0;
        break;
    case 3:
        a = 0;
        b = +1;
        break;
    }
    switch(canMove(this->snake2.getHead()->x() + a, this->snake2.getHead()->y() + b))
    {
    case nothing:
        temp = this->snake2.moving();
        this->cells[temp->x()][temp->y()] = nothing;
        break;
    case wall:
        return false;
        break;
    case foodPart:
        this->snake2.movingWithEating();
        this->placeFood();
        this->recentlychanged.push_back(food);
        break;
    }
    this->recentlychanged.push_back(temp);
    for(int i = 0; i < snake2.getSnakePoints().size(); i++)
    {
        this->cells[snake2.getSnakePoints()[i]->x()][snake2.getSnakePoints()[i]->y()] = snake2Part;
    }
    this->recentlychanged.push_back(snake2.getSnakePoints()[0]);
    return true;
}

int Field::canMove(int x, int y)
{
    if(cells[x][y] == wall || cells[x][y] == snakePart || cells[x][y] == snake2Part)
    {
        return wall;
    }
    else if(cells[x][y] == foodPart)
    {
        return foodPart;
    }
    else if(cells[x][y] == nothing)
    {
        return nothing;
    }
    return 0;
}

QList<QPoint* > Field::getRecentlyChanged()
{
    return this->recentlychanged;
}

void Field::clear(){
    this->width = 75;
    this->height = 40;
    this->snake.setId(0);
    this->snake2.setId(1);
    this->snake2.setVector(0);
    for(int i = 0; i < width; i++)
    {
        QList<int> tempList;
        this->cells.push_back(tempList);
        for(int j = 0; j < height; j++)
        {
            if(i == 0 || i == width - 1 || j == 0 || j == height - 1)
            {
                cells[i].push_back(wall);
            }
            else
            {
                cells[i].push_back(nothing);
            }
        }
    }
    cells[5][5] = snakePart;
    cells[50][30] = snake2Part;
    this->snake.setLength(0);
    this->snake2.setLength(0);
    this->snake.setStartPoint(5,5);
    this->snake2.setStartPoint(50,30);
    placeFood();
}
