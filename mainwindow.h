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

protected:
    Surface *oSurface;
    Ui::MainWindow *ui;

    QHBoxLayout *oMainLayout;
    QVBoxLayout *oRightVBoxLayout;
    QGroupBox *oOptionsGroupBox;
    QVBoxLayout *oOptionsGroupBoxVBoxLayout;
    QCheckBox *oShowMousePositionVectorsCheckBox;
    QCheckBox *oShowAxisCheckBox;
    QCheckBox *oShowEarthCheckBox;
    QCheckBox *oShowCitiesCheckBox;

public slots:
    void fnOnShowMousePositionVectorsChange(bool bValue);
    void fnOnShowAxisCheckBoxChange(bool bValue);
    void fnOnShowEarthCheckBoChange(bool bValue);
    void fnOnShowCitiesCheckBoxChange(bool bValue);
};

#endif // MAINWINDOW_H
