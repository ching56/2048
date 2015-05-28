#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend int main(int argc, char *argv[]);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

public slots:
    void moveblock();

private:
    QLabel* block[16];
    Ui::MainWindow *ui;
    int score;
    int after[16];
    QString b[13];
    QString c[13];
    int pos_x[16];
    int pos_y[16];
    bool moved;
    QTimer *timer;
    int before_b[16];
    int after_b[16];
    bool full;

};

#endif // MAINWINDOW_H
