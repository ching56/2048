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
    /*int rand_num=rand()%16;
    int rand_num2;
    do{rand_num2 = rand()%16;}
    while(rand_num2==rand_num);
    w.block[rand_num]->show();
    w.block[rand_num2]->show();
    w.block[rand_num]->setText("2");
    w.block[rand_num2]->setText("2");

    w.block[0]->show();
    w.block[0]->setText("2");
    w.block[1]->show();
    w.block[1]->setText("4");
    w.block[2]->show();
    w.block[2]->setText("2");
    w.block[3]->show();
    w.block[3]->setText("2");
    w.block[4]->show();
    w.block[4]->setText("16");
    w.block[5]->show();
    w.block[5]->setText("2");
    w.block[6]->show();
    w.block[6]->setText("2");
    w.block[7]->show();
    w.block[7]->setText("2");
    w.block[8]->show();
    w.block[8]->setText("4");*/
    w.block[9]->show();
    w.block[9]->setText(w.b[1]);
    w.block[9]->setStyleSheet(w.c[1]);
    w.block[10]->show();
    w.block[10]->setText(w.b[1]);
    w.block[10]->setStyleSheet(w.c[1]);
    //w.block[11]->show();
    //w.block[11]->setText(w.b[2]);
    //w.block[11]->setStyleSheet(w.c[2]);/*
    /*w.block[12]->show();
    w.block[12]->setText("32");
    w.block[12]->show();
    w.block[12]->setText(w.b[1]);
    w.block[12]->setStyleSheet(w.c[1]);
    w.block[14]->show();
    w.block[14]->setText(w.b[10]);
    w.block[14]->setStyleSheet(w.c[10]);
    w.block[15]->show();
    w.block[15]->setText(w.b[10]);
    w.block[15]->setStyleSheet(w.c[10]);*/


    return a.exec();
}
