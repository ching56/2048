#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //creat two random tiles when beginning
    srand(time(NULL));
    int rand_num=rand()%16;
    int rand_num2;
    do{rand_num2 = rand()%16;}
    while(rand_num2==rand_num);
    w.block[rand_num]->show();
    w.block[rand_num2]->show();
    w.block[rand_num]->setText("2");
    w.block[rand_num2]->setText("2");

    w.block[1]->show();
    w.block[2]->show();
    w.block[1]->setText("2");
    w.block[2]->setText("2");



    return a.exec();
}
