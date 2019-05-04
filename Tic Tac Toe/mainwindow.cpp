#include "mainwindow.h"
#include "ui_mainwindow.h"

void drawMap(QGraphicsScene *scene);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene();

    messWin.setWindowTitle("Сообщение");
    messWin.setStandardButtons(QMessageBox :: Ok);

    ui->graphicsView->setScene(scene);  /// Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по вертикали
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); /// Отключаем скроллбар по горизонтали

    scene->setSceneRect(0, 0, 480, 240);

    coord.first = -1;
    coord.second = -1;
    drawMap(scene);

    countWinO = 0;
    countWinX = 0;

    ui->label_step->setText("X");
    ui->label_winO->setText(QString::number(countWinO));
    ui->label_winX->setText(QString::number(countWinX));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void drawMap(QGraphicsScene *scene)
{
    scene->addLine(scene->width() / 2 - 120, scene->height() / 2 + 40, scene->width() / 2 + 120, scene->height() / 2 + 40, QPen(Qt::black));
    scene->addLine(scene->width() / 2 - 120, scene->height() / 2 - 40, scene->width() / 2 + 120, scene->height() / 2 - 40, QPen(Qt::black));
    scene->addLine(scene->width() / 2 + 40, scene->height() / 2 - 110, scene->width() / 2 + 40, scene->height() / 2 + 110, QPen(Qt::black));
    scene->addLine(scene->width() / 2 - 40, scene->height() / 2 - 110, scene->width() / 2 - 40, scene->height() / 2 + 110, QPen(Qt::black));
}

void MainWindow::on_pushButton_Replay_clicked()
{
    p.clear();
    scene->clear();
    drawMap(scene);

    ui->label_step->setText("X");
}

pair<int, int> coordinatToStep(int x, int y, QGraphicsScene *scene)
{
    pair<int, int> tmp(-1, -1);
    if((115 <= x && x <= 195)&&(105 <= y && y <= 185))
    {
        tmp.first = 0;
        tmp.second = 0;
    }
    else if((195 <= x && x <= 275)&&(105 <= y && y <= 185))
    {
        tmp.first = 0;
        tmp.second = 1;
    }
    else if((275 <= x && x <= 355)&&(105 <= y && y <= 185))
    {
        tmp.first = 0;
        tmp.second = 2;
    }
    else if((115 <= x && x <= 195)&&(185 <= y && y <= 265))
    {
        tmp.first = 1;
        tmp.second = 0;
    }
    else if((195 <= x && x <= 275)&& (185 <= y && y <= 265))
    {
        tmp.first = 1;
        tmp.second = 1;
    }
    else if((275 <= x && x <= 355)&&(185 <= y && y <= 265))
    {
        tmp.first = 1;
        tmp.second = 2;
    }
    else if((115 <= x && x <= 195)&&(265 <= y && y <= 345))
    {
        tmp.first = 2;
        tmp.second = 0;
    }
    else if((195 <= x && x <= 275)&&(265 <= y && y <= 345))
    {
        tmp.first = 2;
        tmp.second = 1;
    }
    else if((275 <= x && x <= 355)&&(265 <= y && y <= 345))
    {
        tmp.first = 2;
        tmp.second = 2;
    }
    return tmp;
}


void MainWindow::mousePressEvent(QMouseEvent *ev)
{
    coord = coordinatToStep(ev->x(), ev->y(), scene);
    if(p.step(coord.first, coord.second))
    {
        drawPolygon();
    }

    switch (p.statusGame())
    {
    case X:
    {
        countWinX++;
        ui->label_winX->setText(QString::number(countWinX));

        messWin.setText("Победили крестики!");
        int res = messWin.exec();
        if(res == QMessageBox::Ok)
        {
            QMessageBox::Cancel;
            this->on_pushButton_Replay_clicked();
        }
    }   break;
    case O:
    {
        countWinO++;
        ui->label_winO->setText(QString::number(countWinO));

        messWin.setText("Победили нолики!");
        int res = messWin.exec();
        if(res == QMessageBox::Ok)
        {
            QMessageBox::Cancel;
            this->on_pushButton_Replay_clicked();
        }
    }    break;
    case XO:
    {
        messWin.setText("Ничья!");
        int res = messWin.exec();
        if(res == QMessageBox::Ok)
        {
            QMessageBox::Cancel;
            this->on_pushButton_Replay_clicked();
        }
    }
        break;
    case null:
        break;
    }
}

void MainWindow::drawPolygon()
{
    for(auto i = 0; i < p.size(); ++i)
    {
        for(auto j = 0; j < p.size(); ++j)
        {
            if(p.getCellValue(i, j) == X)
            {
                drawX(i, j);
            }
            else if(p.getCellValue(i, j) == O)
            {
                drawO(i, j);
            }
        }
    }

    if(p.getPlayer() == X)
    {
        ui->label_step->setText("X");
    }
    else
    {
        ui->label_step->setText("O");
    }

}

void MainWindow::drawX(int x, int y)
{
    scene->addLine(scene->width() / 2 - 105 + 80 * y , scene->height() / 4 + 5 + 80 * x, scene->width() / 2 - 50 + 80 * y, scene->height() / 4  - 35 + 80 * x, QPen(Qt::black));
    scene->addLine(scene->width() / 2 - 105 + 80 * y , scene->height() / 4 - 35 + 80 * x, scene->width() / 2 - 50 + 80 * y , scene->height() / 4  + 5 + 80 * x, QPen(Qt::black));
}

void MainWindow::drawO(int x, int y)
{
    scene->addEllipse(scene->width() / 2 - 105 + 80 * y, scene->height() / 4 - 45 + 80 * x, 50, 50, QPen(Qt::black), QBrush(Qt::transparent));
}
