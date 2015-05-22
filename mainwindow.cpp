#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <math.h>
#include <cstdlib>
#include <QString>
#include <QElapsedTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{       ui->setupUi(this);

        b[0] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">0</span></p></body></html>";
        b[1] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">2</span></p></body></html>";
        b[2] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">4</span></p></body></html>";
        b[3] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">8</span></p></body></html>";
        b[4] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">16</span></p></body></html>";
        b[5] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">32</span></p></body></html>";
        b[6] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">64</span></p></body></html>";
        b[7] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">128</span></p></body></html>";
        b[8] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">256</span></p></body></html>";
        b[9] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">512</span></p></body></html>";
        b[10] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">1024</span></p></body></html>";
        b[11] = "<html><head/><body><p><span style=\" font-size:36pt; color:#ffffff;\">2048</span></p></body></html>";
        b[12] = "<html><head/><body><p><span style=\" font-size:30pt; color:#ffffff;\">2048!</span></p></body></html>";

        c[0] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(216, 179, 104);}";
        c[1] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(123, 163, 168);}";
        c[2] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(244, 243, 222);}";
        c[3] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(190, 173, 146);}";
        c[4] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(91, 73, 71);}";
        c[5] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(64, 128, 0);}";
        c[6] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 171, 216);}";
        c[7] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 137, 114);}";
        c[8] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(245, 197, 100);}";
        c[9] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(242, 87, 45);}";
        c[10] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(66, 168, 129);}";
        c[11] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(31, 135, 132);}";
        c[12] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 105, 125);}";


        score = 0;
        ui->text2048->setAttribute(Qt::WA_TranslucentBackground, true);

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


        ui->lcdNumber->setDigitCount(7);


        for(int i=0;i<16;i++){
            block[i]->setText(b[0]);
            block[i]->hide();
        }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    srand(time(NULL));

    int rand_num;
    int temp_int=0;
    bool wall=false;
    bool full=true;
    bool end=false;

    if(event->key() == Qt::Key_Right){
        //move
        for(int l=3;l<16;l=l+4)
             for(int i=l-1;i>l-4;i--){
                  while(block[i]->text() != b[0] && block[i+1]->text() == b[0] && i<l){
                      block[i+1]->setText(block[i]->text());
                      block[i+1]->show();
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i++;
                      if(i>14)break;
                  }
             }
        //change value

        for(int l=3;l<16;l=l+4)
             for(int i=l;i>l-3;i--){
                  for(int j=i-1;j>l-4;j--)
                        if(block[i]->text() != b[0] && block[i]->text() == block[j]->text()){
                             for(int k=j+1;k<i;k++)
                                 if(block[k]->text() != b[0]){
                                     wall=true;
                                     break;
                                 }
                             if(wall){wall=false;break;}
                             block[j]->setText(b[0]);
                             block[j]->hide();
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                         }
             }
    }
    if(event->key() == Qt::Key_Left){

        //move
        for(int l=0;l<16;l=l+4)
             for(int i=l+1;i<l+4;i++){
                  while(block[i]->text() != b[0] && block[i-1]->text() == b[0] && i>l){
                      block[i-1]->setText(block[i]->text());
                      block[i-1]->show();
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i--;
                      if(i<1)break;
                  }
             }
        //change value

        for(int l=0;l<16;l=l+4)
             for(int i=l;i<l+3;i++){
                  for(int j=i+1;j<l+4;j++)
                        if(block[i]->text() != b[0] && block[i]->text() == block[j]->text()){
                             for(int k=i+1;k<j;k++)
                                 if(block[k]->text() != b[0]){
                                     wall=true;
                                     break;
                                }
                             if(wall){wall=false;break;}
                             block[j]->setText(b[0]);
                             block[j]->hide();
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                         }
             }
    }
    if(event->key() == Qt::Key_Up){
        //move
        for(int l=0;l<4;l++)
             for(int i=l+4;i<l+13;i=i+4){
                  while(block[i]->text() != b[0] && block[i-4]->text() == b[0] && i>l){
                      block[i-4]->setText(block[i]->text());
                      block[i-4]->show();
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i=i-4;
                      if(i<4)break;
                  }
             }
        //change value
        for(int l=0;l<4;l++)
             for(int i=l;i<l+9;i=i+4){
                  for(int j=i+4;j<l+13;j=j+4)
                        if(block[i]->text() != b[0] && block[i]->text() == block[j]->text()){
                             for(int k=i+4;k<j;k=k+4)
                                if(block[k]->text() != b[0]){
                                    wall=true;
                                    break;
                             }
                             if(wall){wall=false;break;}
                             block[j]->setText(b[0]);
                             block[j]->hide();
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                         }
             }
    }
    if(event->key() == Qt::Key_Down){
        //move
        for(int l=12;l<16;l++)
             for(int i=l-4;i>l-13;i=i-4){
                  while(block[i]->text() != b[0] && block[i+4]->text() == b[0] && i<l){
                      block[i+4]->setText(block[i]->text());
                      block[i+4]->show();
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i=i+4;
                      if(i>11)break;
                  }
             }
        //change value
        for(int l=12;l<16;l++)
             for(int i=l;i>l-9;i=i-4){
                  for(int j=i-4;j>l-13;j=j-4)
                        if(block[i]->text() != b[0] && block[i]->text() == block[j]->text()){
                             for(int k=j+4;k<i;k=k+4)
                                if(block[k]->text() != b[0]){
                                    wall=true;
                                    break;
                             }
                             if(wall){wall=false;break;}
                             block[j]->setText(b[0]);
                             block[j]->hide();
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                         }
             }
    }

    for(int i=0;i<16;i++)
        if(block[i]->text()==b[0])
            full=false;
    if(!full){
        do{rand_num=rand()%16;}while(block[rand_num]->text()!=b[0]);
        block[rand_num]->setText(b[1]);
        block[rand_num]->show();
    }else{
        //end statement
       bool thesame=false;

       for(int i=0;i<16;i+=4)
           for(int j=i;j<i+3;j++)
               if(block[j]->text()==block[j+1]->text())
                   thesame=true;
       if(!thesame){
            for(int i=0;i<4;i++)
                for(int j=i;j<i+12;j+=4)
                    if(block[j]->text()==block[j+4]->text())
                        thesame=true;
       }
       if(thesame){
           end=false;

       }else{end=true;};

    }

    for(int i=0;i<16;i++)
        if(block[i]->text()==b[11])
            end=true;
    for(int i=0;i<16;i++)
        for(int k=0;k<13;k++)
            if(block[i]->text()==b[k])
                block[i]->setStyleSheet(c[k]);


    if(end){
        QElapsedTimer t;

        for(int i=0;i<16;i++){
            block[i]->setText(b[12]);
            block[i]->show();
        }
        for(int i=0;i<16;i++)
            for(int k=0;k<13;k++)
                if(block[i]->text()==b[k])
                    block[i]->setStyleSheet(c[k]);
        QWidget::setEnabled(false);
        t.start();
        while(t.elapsed()<2000)
            QCoreApplication::processEvents();
        on_pushButton_clicked();
        QWidget::setEnabled(true);
    }
}

void MainWindow::on_pushButton_clicked()
{
    for(int i=0;i<16;i++){
        block[i]->setText(b[0]);
        block[i]->hide();
    }

    score = 0;
    ui->lcdNumber->display(score);

    srand(time(NULL));
    int rand_num=rand()%16;
    int rand_num2;
    do{rand_num2 = rand()%16;}
    while(rand_num2==rand_num);
    block[rand_num]->show();
    block[rand_num2]->show();
    block[rand_num]->setText(b[1]);
    block[rand_num2]->setText(b[1]);
    for(int i=0;i<16;i++)
        for(int k=0;k<13;k++)
            if(block[i]->text()==b[k])
                block[i]->setStyleSheet(c[k]);
}
