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
    s4 = new QFinalState();
    machine.addState(s4);
    machine.setInitialState(s1);
    machine.start();

    s1->assignProperty(ui->label, "text", "In st s1");
    s2->assignProperty(ui->label, "text", "In st s2");
    s3->assignProperty(ui->label, "text", "In st s3");

    QObject::connect(s1, SIGNAL(entered()), this, SLOT(powerOn1stLbl()));
    QObject::connect(s1, SIGNAL(exited()), this, SLOT(powerOff1stLbl()));
    QObject::connect(s2, SIGNAL(entered()), this, SLOT(powerOn2ndLbl()));
    QObject::connect(s2, SIGNAL(exited()), this, SLOT(powerOff2ndLbl()));
    QObject::connect(s3, SIGNAL(entered()), this, SLOT(powerOn3rdLbl()));
    QObject::connect(s3, SIGNAL(exited()), this, SLOT(powerOff3rdLbl()));

    s1->addTransition(ui->quitButton, SIGNAL(clicked()), s4);
    s2->addTransition(ui->quitButton, SIGNAL(clicked()), s4);
    s3->addTransition(ui->quitButton, SIGNAL(clicked()), s4);
    QObject::connect(&machine, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete s1;
    delete s2;
    delete s3;
}

void MainWindow::on_pushButton_clicked()
{
    //ui->label->setText("clicked");
    qDebug() << "clicked";
}

void MainWindow::powerOn1stLbl()
{
    ui->label_1->setText("1stLbl ON");
}

void MainWindow::powerOn2ndLbl()
{
    ui->label_2->setText("2ndLbl ON");
}

void MainWindow::powerOn3rdLbl()
{
    ui->label_3->setText("3rdLbl ON");
}

void MainWindow::powerOff1stLbl()
{
    ui->label_1->setText("1stLbl Off");
}

void MainWindow::powerOff2ndLbl()
{
    ui->label_2->setText("2ndLbl Off");
}

void MainWindow::powerOff3rdLbl()
{
    ui->label_3->setText("3rdLbl Off");
}
