#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    s1 = new QState();
    s11 = new QState(s1);
    s12 = new QState(s1);
    s13 = new QState(s1);
    s11->addTransition(ui->pushButton, SIGNAL(clicked()), s12);
    s12->addTransition(ui->pushButton, SIGNAL(clicked()), s13);
    s13->addTransition(ui->pushButton, SIGNAL(clicked()), s11);
    machine.addState(s1);
    s2 = new QFinalState();
    machine.addState(s2);
    machine.setInitialState(s1);
    s1->setInitialState(s11);
    machine.start();

    s11->assignProperty(ui->label, "text", "In st s11");
    s12->assignProperty(ui->label, "text", "In st s12");
    s13->assignProperty(ui->label, "text", "In st s13");

    QObject::connect(s11, SIGNAL(entered()), this, SLOT(powerOn1stLbl()));
    QObject::connect(s11, SIGNAL(exited()), this, SLOT(powerOff1stLbl()));
    QObject::connect(s12, SIGNAL(entered()), this, SLOT(powerOn2ndLbl()));
    QObject::connect(s12, SIGNAL(exited()), this, SLOT(powerOff2ndLbl()));
    QObject::connect(s13, SIGNAL(entered()), this, SLOT(powerOn3rdLbl()));
    QObject::connect(s13, SIGNAL(exited()), this, SLOT(powerOff3rdLbl()));

    s1->addTransition(ui->quitButton, SIGNAL(clicked()), s2);
    QObject::connect(&machine, SIGNAL(finished()), QApplication::instance(), SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;

    delete s1;
    delete s2;
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
