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

    this->oShowCentersCheckBox = new QCheckBox();
    this->oShowCentersCheckBox->setText("Show centers");
    this->oShowCentersCheckBox->setChecked(this->oSurface->bShowCenters);
    connect(this->oShowCentersCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowCentersCheckBoChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowCentersCheckBox);

    this->oShowColorBoxCheckBox = new QCheckBox();
    this->oShowColorBoxCheckBox->setText("Show color box");
    this->oShowColorBoxCheckBox->setChecked(this->oSurface->bShowColorBox);
    connect(this->oShowColorBoxCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowColorBoxCheckBoChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowColorBoxCheckBox);

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

    this->oShowAdditionalPointsCheckBox = new QCheckBox();
    this->oShowAdditionalPointsCheckBox->setText("Show additional points");
    this->oShowAdditionalPointsCheckBox->setChecked(this->oSurface->bShowAdditionalPoints);
    connect(this->oShowAdditionalPointsCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowAdditionalPointsChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowAdditionalPointsCheckBox);

    this->oAdditionalPointsWindow = new AdditionalPointsWindow(this);

    this->oShowoAdditionalPointsWindowButton = new QPushButton();
    this->oShowoAdditionalPointsWindowButton->setText("Additional points");
    connect(this->oShowoAdditionalPointsWindowButton, SIGNAL(clicked(bool)), this, SLOT(fnOnShowoAdditionalPointsWindowButtonClick(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowoAdditionalPointsWindowButton);

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

void MainWindow::fnOnShowCentersCheckBoChange(bool bValue)
{
    this->oSurface->bShowCenters = bValue;
    this->oSurface->repaint();
}

void MainWindow::fnOnShowColorBoxCheckBoChange(bool bValue)
{
    this->oSurface->bShowColorBox = bValue;
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

void MainWindow::fnOnShowoAdditionalPointsWindowButtonClick(bool bChecked)
{
    this->oAdditionalPointsWindow->show();
}

void MainWindow::fnOnShowAdditionalPointsChange(bool bValue)
{
    this->oSurface->bShowAdditionalPoints = bValue;
    this->oSurface->repaint();
}
