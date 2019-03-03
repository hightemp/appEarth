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
#include "additionalpointswindow.h"

#include "surface.h"

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
    QCheckBox *oShowCitiesCheckBox;
    QCheckBox *oShowCityCheckBox;
    QComboBox *oCityComboBox;
    QStringListModel *oCityStringListModel;
    AdditionalPointsWindow *oAdditionalPointsWindow;

public slots:
    void fnOnShowMousePositionVectorsChange(bool bValue);
    void fnOnShowAxisCheckBoxChange(bool bValue);
    void fnOnShowEarthCheckBoChange(bool bValue);
    void fnOnShowCitiesCheckBoxChange(bool bValue);
    void fnOnShowCityCheckBoxChange(bool bValue);
    void fnOnCityComboBoxChange(int iIndex);
};

#endif // MAINWINDOW_H
