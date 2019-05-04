#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QMainWindow>

#include <QGraphicsScene>
#include"polygon.h"
#include <map>
#include <QMessageBox>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_Replay_clicked();

private:
    void mousePressEvent(QMouseEvent *ev);
    void drawPolygon();
    void drawX(int x, int y);
    void drawO(int x, int y);

private:
    Ui::MainWindow *ui;
    QMouseEvent *e;
    QGraphicsScene *scene;
    QMessageBox messWin;
    polygon p;
    pair<int, int> coord;

    unsigned countWinX, countWinO;
};

#endif // MAINWINDOW_H
