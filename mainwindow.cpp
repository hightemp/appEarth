#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setMinimumSize(600, 600);

    ui->setupUi(this);

    ui->centralWidget->setLayout(new QVBoxLayout);

    this->oSurface = new Surface(this);
    ui->centralWidget->layout()->addWidget(this->oSurface);
}

MainWindow::~MainWindow()
{
    delete this->oSurface;
    delete ui;
}
