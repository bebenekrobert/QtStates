#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    s1 = new QState();
    s2 = new QState();
    s3 = new QState();
    s1->addTransition(ui->pushButton, SIGNAL(clicked()), s2);
    s2->addTransition(ui->pushButton, SIGNAL(clicked()), s3);
    s3->addTransition(ui->pushButton, SIGNAL(clicked()), s1);
    machine.addState(s1);
    machine.addState(s2);
    machine.addState(s3);
    machine.setInitialState(s1);
    machine.start();

    s1->assignProperty(ui->label, "text", "In st s1");
    s2->assignProperty(ui->label, "text", "In st s2");
    s3->assignProperty(ui->label, "text", "In st s3");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->label->setText("clicked");
    qDebug() << "clicked";
}
