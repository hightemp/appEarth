#ifndef ADDITIONALPOINTSWINDOW_H
#define ADDITIONALPOINTSWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QFile>
#include "mainwindow.h"

class AdditionalPointsWindow : public QWidget
{
    Q_OBJECT

public:
    AdditionalPointsWindow(QWidget *parent = nullptr);

    void fnLoadCSVFile();

public:
    QVBoxLayout *oMainLayout;
    QGroupBox *oGroupBox;
    QVBoxLayout *oGroupBoxLayout;
    QLabel *oCommentLabel;
    QTextEdit *oAdditionalPointsTextEdit;
    QHBoxLayout *oBottomLayout;
    QPushButton *oCancelButton;
    QPushButton *oSaveButton;

public slots:
    void fnOnCancelClick(bool bChecked=false);
    void fnOnSaveClick(bool bChecked=false);

signals:
    void fnUpdatePoints(QStringList *oAdditionalPointsNames);
};

#endif // ADDITIONALPOINTSWINDOW_H
