#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <vector>
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

private:
    QLabel* block[16];
    Ui::MainWindow *ui;
    int score;
    QString b[13];
    QString c[13];
    void move(vector<int>& before, vector<int>& after);
};

#endif // MAINWINDOW_H
