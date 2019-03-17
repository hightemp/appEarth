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

    this->oShowPoliticalEarthMapCheckBox = new QCheckBox();
    this->oShowPoliticalEarthMapCheckBox->setText("Show political map");
    this->oShowPoliticalEarthMapCheckBox->setChecked(this->oSurface->bShowPoliticalEarthMap);
    connect(this->oShowPoliticalEarthMapCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowPoliticalEarthMapCheckBoChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowPoliticalEarthMapCheckBox);

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
    this->oShowCitiesCheckBox->setText("Show all cities");
    this->oShowCitiesCheckBox->setChecked(this->oSurface->bShowCities);
    connect(this->oShowCitiesCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowCitiesCheckBoxChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowCitiesCheckBox);

    this->oShowCityCheckBox = new QCheckBox();
    this->oShowCityCheckBox->setText("Show cities");
    this->oShowCityCheckBox->setChecked(this->oSurface->bShowCity);
    connect(this->oShowCityCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowCityCheckBoxChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowCityCheckBox);

    this->oCitiesFilterLineEdit = new QLineEdit();
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oCitiesFilterLineEdit);

    this->oCitiesList = new QListView();
    this->oCitiesListModel = new CheckableStringListModel(this->oSurface->oCitiesCoordinates, *this->oSurface->oCitiesNames);
    connect(
        this->oCitiesListModel,
        SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
        this,
        SLOT(fnOnListModelDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &))
    );
    this->oCitiesListProxyModel = new QSortFilterProxyModel();
    this->oCitiesListProxyModel->setSourceModel(this->oCitiesListModel);
    this->oCitiesList->setModel(this->oCitiesListProxyModel);
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oCitiesList);

    connect(
        oCitiesFilterLineEdit,
        SIGNAL(textChanged(QString)),
        oCitiesListProxyModel,
        SLOT(setFilterFixedString(QString))
    );

    this->oShowAdditionalPointsCheckBox = new QCheckBox();
    this->oShowAdditionalPointsCheckBox->setText("Show additional points");
    this->oShowAdditionalPointsCheckBox->setChecked(this->oSurface->bShowAdditionalPoints);
    connect(this->oShowAdditionalPointsCheckBox, SIGNAL(clicked(bool)), this, SLOT(fnOnShowAdditionalPointsChange(bool)));
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oShowAdditionalPointsCheckBox);

    this->oAdditionalPointsWindow = new AdditionalPointsWindow(this);
    connect(this->oAdditionalPointsWindow, SIGNAL(fnUpdatePoints(QStringList *)), this, SLOT(fnUpdateAdditionalPointsList(QStringList *)));

    this->oAdditionalPointsFilterLineEdit = new QLineEdit();
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oAdditionalPointsFilterLineEdit);

    this->oAdditionalPointsList = new QListView();
    this->oAdditionalPointsListModel = new CheckableStringListModel(this->oSurface->oAdditionalPointsCoordinates, *this->oSurface->oAdditionalPointsNames);
    connect(
        this->oAdditionalPointsListModel,
        SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
        this,
        SLOT(fnOnListModelDataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &))
    );
    this->oAdditionalPointsListProxyModel = new QSortFilterProxyModel();
    this->oAdditionalPointsListProxyModel->setSourceModel(this->oAdditionalPointsListModel);
    this->oAdditionalPointsList->setModel(this->oAdditionalPointsListProxyModel);
    this->oOptionsGroupBoxVBoxLayout->addWidget(this->oAdditionalPointsList);

    connect(
        oAdditionalPointsFilterLineEdit,
        SIGNAL(textChanged(QString)),
        oAdditionalPointsListProxyModel,
        SLOT(setFilterFixedString(QString))
    );

    this->oAdditionalPointsWindow->fnLoadCSVFile();

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

void MainWindow::fnOnListModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    qDebug() << __FUNCTION__;

    this->oSurface->repaint();
}

void MainWindow::fnUpdateAdditionalPointsList(QStringList *oAdditionalPointsNames)
{
    this->oAdditionalPointsListModel->setStringList(*oAdditionalPointsNames);
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

void MainWindow::fnOnShowPoliticalEarthMapCheckBoChange(bool bValue)
{
    this->oSurface->bShowPoliticalEarthMap = bValue;
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
