#include "block.h"
#include <QKeyEvent>
#include <QDebug>

block::block()
{
    this -> setRect(0,0,80,80);
}

void block::keyPressEvent(QKeyEvent *event)
{

    int px=findX(pos().x())+1;
    int py=findY(pos().y())+1;
    int index=px+(py-1)*4-1;
    int origin=index;
    if((event->key() == Qt::Key_Right)&&pos().x()<295){
        while((!exist[index+1])){
            if(index%4==3)break;
            exist[index]=false;
            setPos(x()+90,y());
            index++;
            exist[index]=true;
        }
    }
    if((event->key() == Qt::Key_Left)&&pos().x()>25){
        while(!exist[index-1]){
            if(index%4==0)break;
            exist[index]=false;
            setPos(x()-90,y());
            index--;
            exist[index]=true;
        }
    }
    if((event->key() == Qt::Key_Up)&&pos().y()>200){
        while(!exist[index-4]){
            if(index/4==0)break;
            exist[index]=false;
            setPos(x(),y()-90);
            index=index-4;
            exist[index]=true;
        }

    }
    if((event->key() == Qt::Key_Down)&&pos().y()<470){
        while(!exist[index+4]){
            if(index/4==3)break;
            exist[index]=false;
            setPos(x(),y()+90);
            index=index+4;
            exist[index]=true;
        }
    }
    /*for(int i=0;i<16;i++) {
    exist[i]?qDebug()<<"true":qDebug()<<"false";
    qDebug()<<" ";
    if(i%4+1==4)qDebug()<<endl;
    }
    qDebug()<<"X";*/
}

int block::findX(int x)
{
    return (x-25)/90;
}

int block::findY(int y)
{
    return (y-200)/90;
}
