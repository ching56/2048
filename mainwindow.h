#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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

private:
    QLabel* block[16];
    Ui::MainWindow *ui;
    int score;
    QString b[13];
    QString c[13];
};

#endif // MAINWINDOW_H
