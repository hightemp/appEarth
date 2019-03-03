#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setMinimumSize(800, 600);

    ui->setupUi(this);

    ui->menuBar->hide();
    ui->mainToolBar->hide();

    QHBoxLayout *oMainLayout = new QHBoxLayout();

    this->oSurface = new Surface(this);
    oMainLayout->addWidget(this->oSurface);

    QVBoxLayout *oRightVBoxLayout = new QVBoxLayout();
    oMainLayout->addLayout(oRightVBoxLayout);

    QGroupBox *oOptionsGroupBox = new QGroupBox();

    oOptionsGroupBox->setMinimumWidth(200);
    oOptionsGroupBox->setMaximumWidth(200);

    oRightVBoxLayout->addWidget(oOptionsGroupBox);

    ui->centralWidget->setLayout(oMainLayout);
}

MainWindow::~MainWindow()
{
    delete this->oSurface;
    delete ui;
}
