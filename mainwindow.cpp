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

    this->oMainLayout = new QHBoxLayout();

    this->oSurface = new Surface();
    this->oMainLayout->addWidget(this->oSurface);

    this->oRightVBoxLayout = new QVBoxLayout();
    this->oMainLayout->addLayout(this->oRightVBoxLayout);

    this->oOptionsGroupBox = new QGroupBox();

    this->oOptionsGroupBox->setMinimumWidth(200);
    this->oOptionsGroupBox->setMaximumWidth(200);

    this->oOptionsGroupBox->setTitle("Options");

    this->oRightVBoxLayout->addWidget(this->oOptionsGroupBox);

    this->oOptionsGroupBoxVBoxLayout = new QVBoxLayout();

    this->oOptionsGroupBox->setLayout(this->oOptionsGroupBoxVBoxLayout);

    this->oOptionsGroupBoxVBoxLayout->setAlignment(Qt::AlignTop);

    this->oShowMousePositionVectorsCheckBox = new QCheckBox();
    this->oShowMousePositionVectorsCheckBox->setText("Show mouse position vectors");
    this->oShowMousePositionVectorsCheckBox->setChecked(this->oSurface->bShowMousePositionVectors);
    connect(this->oShowMousePositionVectorsCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowMousePositionVectorsChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowMousePositionVectorsCheckBox);

    this->oShowAxisCheckBox = new QCheckBox();
    this->oShowAxisCheckBox->setText("Show axis");
    this->oShowAxisCheckBox->setChecked(this->oSurface->bShowAxis);
    connect(this->oShowAxisCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowAxisCheckBoxChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowAxisCheckBox);

    this->oShowEarthCheckBox = new QCheckBox();
    this->oShowEarthCheckBox->setText("Show earth");
    this->oShowEarthCheckBox->setChecked(this->oSurface->bShowEarth);
    connect(this->oShowEarthCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowEarthCheckBoChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowEarthCheckBox);

    this->oShowCitiesCheckBox = new QCheckBox();
    this->oShowCitiesCheckBox->setText("Show cities");
    this->oShowCitiesCheckBox->setChecked(this->oSurface->bShowCities);
    connect(this->oShowCitiesCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowCitiesCheckBoxChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowCitiesCheckBox);

    this->oShowCityCheckBox = new QCheckBox();
    this->oShowCityCheckBox->setText("Show city");
    this->oShowCityCheckBox->setChecked(this->oSurface->bShowCity);
    connect(this->oShowCityCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowCityCheckBoxChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowCityCheckBox);

    this->oCityComboBox = new QComboBox();
    this->oCityStringListModel = new QStringListModel();
    this->oCityStringListModel->setStringList(*this->oSurface->oCitiesNames);
    this->oCityComboBox->setModel(this->oCityStringListModel);
    connect(this->oCityComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(fnOnCityComboBoxChange(int)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oCityComboBox);

    this->oAdditionalPointsWindow = new AdditionalPointsWindow();

    ui->centralWidget->setLayout(this->oMainLayout);
}

MainWindow::~MainWindow()
{
    delete this->oSurface;
    delete ui;
}

void MainWindow::fnOnShowMousePositionVectorsChange(bool bValue)
{
    this->oSurface->bShowMousePositionVectors = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnShowAxisCheckBoxChange(bool bValue)
{
    this->oSurface->bShowAxis = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnShowEarthCheckBoChange(bool bValue)
{
    this->oSurface->bShowEarth = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnShowCitiesCheckBoxChange(bool bValue)
{
    this->oSurface->bShowCities = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnShowCityCheckBoxChange(bool bValue)
{
    this->oSurface->bShowCity = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnCityComboBoxChange(int iIndex)
{
    this->oSurface->iCityId = iIndex;
    this->oSurface->repaint();
}
