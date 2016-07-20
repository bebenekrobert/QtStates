#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStateMachine>
#include <QFinalState>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void powerOn1stLbl();
    void powerOn2ndLbl();
    void powerOn3rdLbl();
    void powerOff1stLbl();
    void powerOff2ndLbl();
    void powerOff3rdLbl();

private:
    Ui::MainWindow *ui;
    QStateMachine machine;
    QState *s1;
    QState *s2;
    QState *s3;
    QFinalState *s4;
};

#endif // MAINWINDOW_H
