#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QDebug>
#include <QGroupBox>
#include <QCheckBox>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QStringListModel>
#include <QPushButton>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include "additionalpointswindow.h"
#include "surface.h"
#include "checkablestringlistmodel.h"

class AdditionalPointsWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    Ui::MainWindow *ui;

    Surface *oSurface;

    QHBoxLayout *oMainLayout;
    QVBoxLayout *oRightVBoxLayout;
    QGroupBox *oOptionsGroupBox;
    QVBoxLayout *oOptionsGroupBoxVBoxLayout;
    QCheckBox *oShowMousePositionVectorsCheckBox;
    QCheckBox *oShowAxisCheckBox;
    QCheckBox *oShowEarthCheckBox;
    QCheckBox *oShowPoliticalEarthMapCheckBox;
    QCheckBox *oShowCentersCheckBox;
    QCheckBox *oShowColorBoxCheckBox;
    QCheckBox *oShowCitiesCheckBox;
    QCheckBox *oShowCityCheckBox;
    QListView *oCitiesList;
    CheckableStringListModel *oCitiesListModel;
    QSortFilterProxyModel *oCitiesListProxyModel;
    QLineEdit *oCitiesFilterLineEdit;
    QStringListModel *oCityStringListModel;
    QCheckBox *oShowAdditionalPointsCheckBox;
    QListView *oAdditionalPointsList;
    QSortFilterProxyModel *oAdditionalPointsListProxyModel;
    CheckableStringListModel *oAdditionalPointsListModel;
    QLineEdit *oAdditionalPointsFilterLineEdit;
    AdditionalPointsWindow *oAdditionalPointsWindow;
    QPushButton *oShowoAdditionalPointsWindowButton;

public slots:
    void fnOnListModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>());
    void fnUpdateAdditionalPointsList(QStringList *oCitiesNames);
    void fnOnShowMousePositionVectorsChange(bool bValue);
    void fnOnShowAxisCheckBoxChange(bool bValue);
    void fnOnShowEarthCheckBoChange(bool bValue);
    void fnOnShowPoliticalEarthMapCheckBoChange(bool bValue);
    void fnOnShowCentersCheckBoChange(bool bValue);
    void fnOnShowColorBoxCheckBoChange(bool bValue);
    void fnOnShowCitiesCheckBoxChange(bool bValue);
    void fnOnShowCityCheckBoxChange(bool bValue);
    void fnOnCityComboBoxChange(int iIndex);
    void fnOnShowoAdditionalPointsWindowButtonClick(bool bChecked = false);
    void fnOnShowAdditionalPointsChange(bool bValue);
};

#endif // MAINWINDOW_H
