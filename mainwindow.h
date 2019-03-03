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
#include "additionalpointswindow.h"
#include "surface.h"

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
    QCheckBox *oShowColorBoxCheckBox;
    QCheckBox *oShowCitiesCheckBox;
    QCheckBox *oShowCityCheckBox;
    QComboBox *oCityComboBox;
    QStringListModel *oCityStringListModel;
    QCheckBox *oShowAdditionalPointsCheckBox;
    AdditionalPointsWindow *oAdditionalPointsWindow;
    QPushButton *oShowoAdditionalPointsWindowButton;

public slots:
    void fnOnShowMousePositionVectorsChange(bool bValue);
    void fnOnShowAxisCheckBoxChange(bool bValue);
    void fnOnShowEarthCheckBoChange(bool bValue);
    void fnOnShowColorBoxCheckBoChange(bool bValue);
    void fnOnShowCitiesCheckBoxChange(bool bValue);
    void fnOnShowCityCheckBoxChange(bool bValue);
    void fnOnCityComboBoxChange(int iIndex);
    void fnOnShowoAdditionalPointsWindowButtonClick(bool bChecked = false);
    void fnOnShowAdditionalPointsChange(bool bValue);
};

#endif // MAINWINDOW_H
