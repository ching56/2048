#include "block.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <vector>
#include <cstdlib>
using namespace std;
bool block::exist[16]={false};
int block::value[16]={0};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // create a scene
    QGraphicsScene * scene = new QGraphicsScene();

    // create an item to add to the scene
    vector<block*> blo(16);
    srand(time(NULL));
    int aa = rand()%16;
    blo.at(aa)=new block();
    int b;
    do{b=rand()%16;}while(rand()%16==aa);

    //when start, creat 2 blcok
    blo.at(b)=new block();
    scene->addItem(blo.at(aa));
    scene->addItem(blo.at(b));
    blo.at(aa)->setFlag(QGraphicsItem::ItemIsFocusable);
    blo.at(aa)->setPos(25+aa%4*90,aa/4%4*90+200);
    blo.at(b)->setFlag(QGraphicsItem::ItemIsFocusable);
    blo.at(b)->setPos(25+b%4*90,b/4%4*90+200);
    block::exist[aa]=true;
    block::exist[b]=true;
    //test focus
    blo.at(b)->setFocus();

 /*   for(int i=0;i<16;i++){
    blo.push_back(new block());
    scene->addItem(blo[i]);

    blo[i]->setFlag(QGraphicsItem::ItemIsFocusable);
    blo[i]->setPos(25+i%4*90,i/4%4*90+200);
    }
*/
    QGraphicsView * view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    view->show();
    view->setWindowTitle("2048");
    view->setFixedSize(400,600);
    scene->setSceneRect(0,0,400,600);


    return a.exec();
}
