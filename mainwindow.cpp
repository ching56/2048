#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <math.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{       ui->setupUi(this);

        //hide all tiles
        block[0] = ui->tile_1;
        block[1] = ui->tile_2;
        block[2] = ui->tile_3;
        block[3] = ui->tile_4;
        block[4] = ui->tile_5;
        block[5] = ui->tile_6;
        block[6] = ui->tile_7;
        block[7] = ui->tile_8;
        block[8] = ui->tile_9;
        block[9] = ui->tile_10;
        block[10] =ui->tile_11;
        block[11] =ui->tile_12;
        block[12] =ui->tile_13;
        block[13] =ui->tile_14;
        block[14] =ui->tile_15;
        block[15] =ui->tile_16;

        for(int i=0;i<16;i++)
            block[i]->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString temp_string;
    int temp_int=0;

    if(event->key() == Qt::Key_Right){
        //move
        for(int l=3;l<16;l=l+4)
             for(int i=l-1;i>l-4;i--){
                  while(block[i]->text() != "0" && block[i+1]->text() == "0" && i<l){
                      block[i+1]->setText(block[i]->text());
                      block[i+1]->show();
                      block[i]->setText("0");
                      block[i]->hide();
                      i++;
                      if(i>14)break;
                  }
             }
        //change value

        for(int l=3;l<16;l=l+4)
             for(int i=l;i>l-3;i--){
                  for(int j=i-1;j>l-4;j--)
                        if(block[i]->text() != "0" && block[i]->text() == block[j]->text()){
                             block[j]->setText("0");
                             block[j]->hide();
                             temp_int = log2(block[i]->text().toInt());
                             temp_string.setNum(pow(2,temp_int+1));
                             block[i]->setText(temp_string);
                         }
             }
        //clean tile
        for(int i=0;i<16;i++)
            if(block[i]->text()=="0")
                block[i]->hide();
    }
    if(event->key() == Qt::Key_Left){

        //move
        for(int l=0;l<16;l=l+4)
             for(int i=l+1;i<l+4;i++){
                  while(block[i]->text() != "0" && block[i-1]->text() == "0" && i>l){
                      block[i-1]->setText(block[i]->text());
                      block[i-1]->show();
                      block[i]->setText("0");
                      block[i]->hide();
                      i--;
                      if(i<1)break;
                  }
             }
        //change value

        for(int l=0;l<16;l=l+4)
             for(int i=l;i<l+3;i++){
                  for(int j=i+1;j<l+4;j++)
                        if(block[i]->text() != "0" && block[i]->text() == block[j]->text()){
                             block[j]->setText("0");
                             block[j]->hide();
                             temp_int = log2(block[i]->text().toInt());
                             temp_string.setNum(pow(2,temp_int+1));
                             block[i]->setText(temp_string);
                         }
             }


        //clean tile
        for(int i=0;i<16;i++)
            if(block[i]->text()=="0")
                block[i]->hide();

    }
    if(event->key() == Qt::Key_Up){
        //move
        for(int l=0;l<4;l++)
             for(int i=l+4;i<l+13;i=i+4){
                  while(block[i]->text() != "0" && block[i-4]->text() == "0" && i>l){
                      block[i-4]->setText(block[i]->text());
                      block[i-4]->show();
                      block[i]->setText("0");
                      block[i]->hide();
                      i=i-4;
                      if(i<4)break;
                  }
             }
        //change value
        for(int l=0;l<4;l++)
             for(int i=l;i<l+9;i=i+4){
                  for(int j=i+4;j<l+13;j=j+4)
                        if(block[i]->text() != "0" && block[i]->text() == block[j]->text()){
                             block[j]->setText("0");
                             block[j]->hide();
                             temp_int = log2(block[i]->text().toInt());
                             temp_string.setNum(pow(2,temp_int+1));
                             block[i]->setText(temp_string);
                         }
             }
        //clean tile
        for(int i=0;i<16;i++)
            if(block[i]->text()=="0")
                block[i]->hide();

    }
    if(event->key() == Qt::Key_Down){
        //move
        for(int l=12;l<16;l++)
             for(int i=l-4;i>l-13;i=i-4){
                  while(block[i]->text() != "0" && block[i+4]->text() == "0" && i<l){
                      block[i+4]->setText(block[i]->text());
                      block[i+4]->show();
                      block[i]->setText("0");
                      block[i]->hide();
                      i=i+4;
                      if(i>11)break;
                  }
             }
        //change value
        for(int l=12;l<16;l++)
             for(int i=l;i>l-9;i=i-4){
                  for(int j=i-4;j>l-13;j=j-4)
                        if(block[i]->text() != "0" && block[i]->text() == block[j]->text()){
                             block[j]->setText("0");
                             block[j]->hide();
                             temp_int = log2(block[i]->text().toInt());
                             temp_string.setNum(pow(2,temp_int+1));
                             block[i]->setText(temp_string);
                         }
             }
        //clean tile
        for(int i=0;i<16;i++)
            if(block[i]->text()=="0")
                block[i]->hide();

    }
}
