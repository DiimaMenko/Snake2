#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include <QKeyEvent>
#include "Field.h"

#define win_w 1300
#define win_h 700

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotStart();
    void slotPause();
    void slotTimer1();
    void slotResume();
    void slotExit();
    void slotRestart();

protected:
    virtual void keyPressEvent(QKeyEvent *event);
private:
    void redrawField();//перемальовуємо необхідні мітки(labelsField)
    void firstdrawField();//малюємо все поле.
    Ui::MainWindow *ui;
    QWidget *looseScreen;
    QPushButton *buttonStart;
    QPushButton *buttonPause;
    QPushButton *buttonResume;
    QPushButton *buttonExit;
    QPushButton *buttonRestart;
    QLabel *labelLoose;
    QTimer *timer1;
    QLabel *labelScore;
    QLabel *labelScore2;
    int cellsize;
    int toolbarsize;
    int speed;

    Field *field;
    QList<QList<QLabel *> > labelsField;
};

#endif // MAINWINDOW_H
