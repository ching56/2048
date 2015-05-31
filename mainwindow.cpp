#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QKeyEvent>
#include <QString>
#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{       ui->setupUi(this);

        // initialize the variable
        timer = new QTimer();
        full=true;
        score = 0;
        moved=false;

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
        c[1] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(151, 236, 113);}";
        c[2] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 171, 206);}";
        c[3] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(190, 173, 146);}";
        c[4] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(40, 81, 113);}";
        c[5] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(216, 179, 104);}";
        c[6] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(47, 150, 169);}";
        c[7] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 137, 114);}";
        c[8] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(245, 197, 100);}";
        c[9] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(242, 87, 45);}";
        c[10] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(66, 168, 129);}";
        c[11] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(31, 135, 132);}";
        c[12] = "QLabel { border-width:1px;border-color:black;border-radius: 10px;background-color: rgb(0, 105, 125);}";

        //set the signal & slot connection
        connect(timer,SIGNAL(timeout()),this,SLOT(moveblock()));

        //to make the access more convenient set the qlabels in ui to array
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

        //set the score board
        ui->lcdNumber->setDigitCount(7);
        //set the frame hide, and it will appear when the game end
        ui->frame->hide();

        //initialize the array which used in animation
        for(int i=0;i<16;i++){
            after[i]=-1;
        }

        //initialize all labels to 0 and hide
        for(int i=0;i<16;i++){
            block[i]->setText(b[0]);
            block[i]->setStyleSheet(c[0]);
            block[i]->hide();
        }

        //save the positions of all labels
        for(int i=0;i<16;i++){
            pos_x[i]=block[i]->pos().x();
            pos_y[i]=block[i]->pos().y();
        }

        //show two label when the gmae execute
        block[8]->show();
        block[8]->setText(b[1]);
        block[8]->setStyleSheet(c[1]);
        block[10]->show();
        block[10]->setText(b[1]);
        block[10]->setStyleSheet(c[1]);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //when frame is showed,the game ended, keypress make no effect
    if(ui->frame->isVisible())return;
    //when animation is processing, keypress make no effect
    if(timer->isActive())return;

    srand(time(NULL));
    full=true;
    int temp_int=0;
    int speed=1;
    bool change=false;
    bool wall=false;
    for(int i=0;i<16;i++){
        after[i]=-1;
    }
    for(int i=0;i<16;i++){
        for(int k=0;k<13;k++){
            if(block[i]->text()!=b[0])
                after[i]=i;
        }
        for(int j=0;j<13;j++){
            if(block[i]->text()==b[j])
                before_b[i]=j;

        }
    }

    if(event->key() == Qt::Key_Right){





        //move
        for(int l=3;l<16;l=l+4)
             for(int i=l-1;i>l-4;i--){
                  while(block[i]->text() != b[0] && block[i+1]->text() == b[0] && i<l){
                      block[i+1]->setText(block[i]->text());
                      block[i+1]->setStyleSheet(block[i]->styleSheet());
                      block[i+1]->show();
                      for(int k=0;k<16;k++)
                          if(after[k]==i)
                              after[k]++;
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i++;
                      change=true;
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
                             for(int m=0;m<16;m++)
                                 if(after[m]==j)
                                     after[m]++;
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                             change=true;
                         }
             }
        for(int i=0;i<16;i++){
            for(int j=0;j<13;j++){
                if(block[i]->text()==b[j])
                    after_b[i]=j;
            }
        }
        //motion
        for(int i=0;i<16;i++){
            //restore
            if(after[i]!=-1){
                    if(after[i]!=i){
                        block[after[i]]->setText(b[before_b[after[i]]]);
                        block[after[i]]->setStyleSheet(c[before_b[after[i]]]);
                        if(block[after[i]]->text()==b[0])block[after[i]]->hide();
                        block[i]->setText(b[before_b[i]]);
                        block[i]->setStyleSheet(c[before_b[i]]);
                    }
            }
        }
        for(int i=0;i<16;i++){
            if(after[i]!=-1&&after[i]!=i)block[i]->show();
        }
        if(change)
        timer->start(speed);
    }
    if(event->key() == Qt::Key_Left){

        //move
        for(int l=0;l<16;l=l+4)
             for(int i=l+1;i<l+4;i++){
                  while(block[i]->text() != b[0] && block[i-1]->text() == b[0] && i>l){
                      block[i-1]->setText(block[i]->text());
                      block[i-1]->show();
                      for(int k=0;k<16;k++)
                          if(after[k]==i)
                              after[k]--;
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i--;
                      change=true;
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
                             for(int m=0;m<16;m++)
                                 if(after[m]==j)
                                     after[m]--;
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                             change=true;
                         }
             }
        for(int i=0;i<16;i++){
            for(int j=0;j<13;j++){
                if(block[i]->text()==b[j])
                    after_b[i]=j;
            }
        }
        //motion
        for(int i=0;i<16;i++){
            //restore
            if(after[i]!=-1){
                    if(after[i]!=i){
                        block[after[i]]->setText(b[before_b[after[i]]]);
                        block[after[i]]->setStyleSheet(c[before_b[after[i]]]);
                        if(block[after[i]]->text()==b[0])block[after[i]]->hide();
                        block[i]->setText(b[before_b[i]]);
                        block[i]->setStyleSheet(c[before_b[i]]);
                    }
            }
        }
        for(int i=0;i<16;i++)
            if(after[i]!=-1&&after[i]!=i)block[i]->show();
        if(change)
        timer->start(speed);
    }
    if(event->key() == Qt::Key_Up){
        //move
        for(int l=0;l<4;l++)
             for(int i=l+4;i<l+13;i=i+4){
                  while(block[i]->text() != b[0] && block[i-4]->text() == b[0] && i>l){
                      block[i-4]->setText(block[i]->text());
                      block[i-4]->show();
                      for(int k=0;k<16;k++)
                          if(after[k]==i)
                              after[k]-=4;
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i=i-4;
                       change=true;
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
                             for(int m=0;m<16;m++)
                                 if(after[m]==j)
                                     after[m]-=4;
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                             change=true;
                         }

             }
        for(int i=0;i<16;i++){
            for(int j=0;j<13;j++){
                if(block[i]->text()==b[j])
                    after_b[i]=j;
            }
        }
        //motion
        for(int i=0;i<16;i++){
            //restore
            if(after[i]!=-1){
                    if(after[i]!=i){
                        block[after[i]]->setText(b[before_b[after[i]]]);
                        block[after[i]]->setStyleSheet(c[before_b[after[i]]]);
                        if(block[after[i]]->text()==b[0])block[after[i]]->hide();
                        block[i]->setText(b[before_b[i]]);
                        block[i]->setStyleSheet(c[before_b[i]]);
                    }
            }
        }
        for(int i=0;i<16;i++)
            if(after[i]!=-1&&after[i]!=i)block[i]->show();
        if(change)
        timer->start(speed);
    }
    if(event->key() == Qt::Key_Down){
        //move
        for(int l=12;l<16;l++)
             for(int i=l-4;i>l-13;i=i-4){
                  while(block[i]->text() != b[0] && block[i+4]->text() == b[0] && i<l){
                      block[i+4]->setText(block[i]->text());
                      block[i+4]->show();
                      for(int m=0;m<16;m++)
                          if(after[m]==i)
                              after[m]+=4;
                      block[i]->setText(b[0]);
                      block[i]->hide();
                      i=i+4;
                      change=true;
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
                             for(int m=0;m<16;m++)
                                 if(after[m]==j)
                                     after[m]+=4;
                             score = score+5;
                             ui->lcdNumber->display(score);
                             for(int k=0;k<12;k++)
                                 if(block[i]->text()==b[k])
                                     temp_int=k+1;
                             block[i]->setText(b[temp_int]);
                             change=true;
                         }
             }
        for(int i=0;i<16;i++){
            for(int j=0;j<13;j++){
                if(block[i]->text()==b[j])
                    after_b[i]=j;
            }
        }
    //motion
    for(int i=0;i<16;i++){
        //restore
        if(after[i]!=-1){
                if(after[i]!=i){
                    block[after[i]]->setText(b[before_b[after[i]]]);
                    block[after[i]]->setStyleSheet(c[before_b[after[i]]]);
                    if(block[after[i]]->text()==b[0])block[after[i]]->hide();
                    block[i]->setText(b[before_b[i]]);
                    block[i]->setStyleSheet(c[before_b[i]]);
                }
        }
    }
    for(int i=0;i<16;i++)
        if(after[i]!=-1&&after[i]!=i)block[i]->show();

    if(change)
    timer->start(speed);



    }

    for(int i=0;i<16;i++){
        for(int j=0;j<13;j++)
           if(block[i]->text()==b[j])
               block[i]->setStyleSheet(c[j]);
        if(block[i]->text()==b[0]){block[i]->hide();}
        else{block[i]->show();}
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

void MainWindow::on_pushButton_2_clicked()
{
    on_pushButton_clicked();
    ui->frame->hide();
}

void MainWindow::moveblock()
{

    moved=true;
    bool end=false;
    int rand_num;
    int unit=22;
    for(int i=0;i<16;i++){
       if(after[i]!=i&&after[i]!=-1){
       if(block[i]->pos().x()<pos_x[after[i]]){//avoid trigger this one when left

          block[i]->move(block[i]->pos().x()+unit,block[i]->pos().y());

          moved=false;
       }
       if(block[i]->pos().y()<pos_y[after[i]]){
           block[i]->move(block[i]->pos().x(),block[i]->pos().y()+unit);
           moved=false;
       }
       if(block[i]->pos().x()>pos_x[after[i]]){
           block[i]->move(block[i]->pos().x()-unit,block[i]->pos().y());
           moved=false;
       }
       if(block[i]->pos().y()>pos_y[after[i]]){
           block[i]->move(block[i]->pos().x(),block[i]->pos().y()-unit);
           moved=false;
       }
       }
    }

    if(moved){
        for(int i=0;i<16;i++){
            //restore

            if(after[i]!=-1){
                    if(after[i]!=i){


                        block[after[i]]->show();
                        block[after[i]]->setText(b[after_b[after[i]]]);
                        block[after[i]]->setStyleSheet(b[after_b[after[i]]]);
                        block[i]->setText(b[after_b[i]]);

                        block[i]->setStyleSheet(b[after_b[i]]);
                        //if(block[i]->text()==b[0])block[i]->hide();
                        block[i]->move(pos_x[i],pos_y[i]);

                    }

            }
        }
        timer->stop();

        for(int i=0;i<16;i++)
            if(block[i]->text()==b[0])
                full=false;
        if(!full){
            do{rand_num=rand()%16;}while(block[rand_num]->text()!=b[0]);
            block[rand_num]->setText(b[1]);
            block[rand_num]->show();
            full=true;
            for(int i=0;i<16;i++)
                if(block[i]->text()==b[0])
                    full=false;
        }
        if(full){
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
            ui->frame->show();
            ui->socrelabel->setText(QString::number(score));
        }
        for(int i=0;i<16;i++)if(block[i]->text()==b[0])block[i]->hide();
    }
    for(int i=0;i<16;i++){
        for(int j=0;j<13;j++)
           if(block[i]->text()==b[j])
               block[i]->setStyleSheet(c[j]);
        if(block[i]->text()==b[0]){block[i]->hide();}
        else{block[i]->show();}
    }


}

