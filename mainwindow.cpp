#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->resize(win_w, win_h);

    this->setMaximumSize(1300,700);
    this->setMinimumSize(640,480);
    this->cellsize = 30;
    this->toolbarsize = 50;
    this->speed = 120;
    this->buttonStart = new QPushButton("Почати гру", this);

    this->buttonStart->resize(100, this->buttonStart->height());
    this->buttonStart->move(win_w / 2 - this->buttonStart->width() / 2, win_h / 2 - this->buttonStart->height() / 2);
    this->buttonStart->show();

    connect(buttonStart, SIGNAL(clicked(bool)), this, SLOT(slotStart()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotStart()
{
    this->buttonStart->setVisible(0);

    this->buttonPause = new QPushButton("Пауза", this);
    this->labelScore = new QLabel("0", this);
    this->labelScore2 = new QLabel("0", this);
    this->timer1 = new QTimer(this);

    //малюємо поле та змінюємо розмір екрану
    this->field = new Field(75, 40);
    this->cellsize = win_w / field->getWidth();
    if(field->getHeight() * cellsize > this->maximumHeight() - toolbarsize ||
       field->getHeight() * cellsize < this->minimumHeight() - toolbarsize)
    {
        cellsize = (win_h - toolbarsize) / field->getHeight();
    }
    this->resize(field->getWidth() * cellsize, field->getHeight() * cellsize + toolbarsize);
    firstdrawField();

    this->buttonPause->move(10, 15);
    this->labelScore->move(200, 15);
    this->labelScore2->move(300, 15);

    this->buttonPause->setVisible(1);
    this->labelScore->setVisible(1);
    this->labelScore2->setVisible(1);

    timer1->start(speed);

    connect(this->buttonPause, SIGNAL(clicked(bool)),this, SLOT(slotPause()));
    connect(timer1, SIGNAL(timeout()),this,SLOT(slotTimer1()));
}

void MainWindow::slotPause()
{
    this->buttonPause->hide();
    timer1->stop();
    this->buttonResume = new QPushButton("Продовжити", this);
    this->buttonResume->move(10, 15);
    this->buttonResume->show();
    connect(this->buttonResume, SIGNAL(clicked(bool)),this,SLOT(slotResume()));
}

void MainWindow::slotTimer1()
{
    this->labelScore->setNum(this->field->snake.getLength());
    this->labelScore2->setNum(this->field->snake2.getLength());
    if(!this->field->moveSnake())
    {
        timer1->stop();
        this->looseScreen = new QWidget();
        this->looseScreen->resize(300,100);
        this->looseScreen->show();
        this->labelLoose = new QLabel("Виграв гравець 2! Натисніть кнопку для виходу.", looseScreen);
        this->labelLoose->resize(250,labelLoose->height());
        this->labelLoose->move(150 - labelLoose->width() / 2, 10);
        this->labelLoose->show();
        this->buttonExit = new QPushButton("Вихід", looseScreen);
        this->buttonExit->move(150 - buttonExit->width() / 2, 70);
        this->buttonExit->show();
        this->buttonRestart = new QPushButton("Ще раз!", looseScreen);
        this->buttonRestart->move(150 - buttonRestart->width() / 2, 40);
        this->buttonRestart->show();
        connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(slotExit()));
        connect(buttonRestart,SIGNAL(clicked(bool)), this, SLOT(slotRestart()));
    }
    else if(!this->field->moveSnake2())
    {
        timer1->stop();
        this->looseScreen = new QWidget();
        this->looseScreen->resize(300,100);
        this->looseScreen->show();
        this->labelLoose = new QLabel("Виграв гравець 1! Натисніть кнопку для виходу.", looseScreen);
        this->labelLoose->resize(250,labelLoose->height());
        this->labelLoose->move(150 - labelLoose->width() / 2, 10);
        this->labelLoose->show();
        this->buttonExit = new QPushButton("Вихід", looseScreen);
        this->buttonExit->move(150 - buttonExit->width() / 2, 50);
        this->buttonExit->show();
        this->buttonRestart = new QPushButton("Ще раз!", looseScreen);
        this->buttonRestart->move(150 - buttonRestart->width() / 2, 40);
        this->buttonRestart->show();
        connect(buttonExit, SIGNAL(clicked(bool)), this, SLOT(slotExit()));
        connect(buttonRestart,SIGNAL(clicked(bool)), this, SLOT(slotRestart()));
    }
    redrawField();
}

void MainWindow::slotResume()
{
    this->buttonResume->hide();
    this->buttonPause->show();
    timer1->start(speed);
}

void MainWindow::slotExit()
{
    this->looseScreen->setVisible(0);
    this->setVisible(0);
    exit(0);
}

void MainWindow::firstdrawField()
{
    for(int i = 0; i < this->field->getWidth(); i++)
    {
        QList<QLabel *> tempLabelList;
        this->labelsField.push_back(tempLabelList);
        for(int j = 0; j < this->field->getHeight(); j++)
        {
            QLabel *tempLabel = new QLabel("", this);
            switch(field->getCell(i,j))
            {
            case nothing:
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
                break;
            case wall:
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
                break;
            case snakePart:
                tempLabel->resize(cellsize - 2, cellsize - 2);
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 200);"));
                break;
            case snake2Part:
                tempLabel->resize(cellsize - 2, cellsize - 2);
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));
                break;
            case foodPart:
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
                break;
            default:
                tempLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
                break;
            }
            tempLabel->resize(cellsize, cellsize);
            tempLabel->move(i * cellsize, j * cellsize + toolbarsize);
            this->labelsField[i].push_back(tempLabel);
            this->labelsField[i][j]->show();
        }
    }
}

void MainWindow::redrawField()
{
    QList<QPoint *> tempList = this->field->getRecentlyChanged();
    for(int i = 0; i < tempList.size(); i++)
    {
        if(field->getCell(tempList[i]->x(),tempList[i]->y()) == nothing)
        {
            labelsField[tempList[i]->x()][tempList[i]->y()]->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        }
        else if(field->getCell(tempList[i]->x(),tempList[i]->y()) == snakePart)
        {
            labelsField[tempList[i]->x()][tempList[i]->y()]->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 200);"));
        }
        else if(field->getCell(tempList[i]->x(),tempList[i]->y()) == snake2Part)
        {
            labelsField[tempList[i]->x()][tempList[i]->y()]->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 0, 0);"));
        }
        else if(field->getCell(tempList[i]->x(),tempList[i]->y()) == foodPart)
        {
            labelsField[tempList[i]->x()][tempList[i]->y()]->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
        if(this->field->snake.getVector() != 2)
        {
            this->field->snake.setVector(0);
        }
        break;
    case Qt::Key_S:
        if(this->field->snake.getVector() != 1)
        {
            this->field->snake.setVector(3);
        }
        break;
    case Qt::Key_D:
        if(this->field->snake.getVector() != 0)
        {
            this->field->snake.setVector(2);
        }
        break;
    case Qt::Key_W:
        if(this->field->snake.getVector() != 3)
        {
            this->field->snake.setVector(1);
        }
        break;
        //
    case Qt::Key_J:
        if(this->field->snake2.getVector() != 2)
        {
            this->field->snake2.setVector(0);
        }
        break;
    case Qt::Key_K:
        if(this->field->snake2.getVector() != 1)
        {
            this->field->snake2.setVector(3);
        }
        break;
    case Qt::Key_L:
        if(this->field->snake2.getVector() != 0)
        {
            this->field->snake2.setVector(2);
        }
        break;
    case Qt::Key_I:
        if(this->field->snake2.getVector() != 3)
        {
            this->field->snake2.setVector(1);
        }
        break;
    case Qt::Key_P:
        this->slotPause();
        break;
    case Qt::Key_R:
        this->slotResume();
        break;
    default:
        break;
    }
}

void MainWindow::slotRestart(){
    slotPause();
    this->field->clear();
    this->looseScreen->hide();
    redrawField();
}
