#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>

class block: public QGraphicsRectItem{
public:
    block();
    void keyPressEvent(QKeyEvent * event);
    static bool exist[16];
    static int value[16];
private:
    int findX(int x);
    int findY(int y);
};

#endif // BLOCK_H

