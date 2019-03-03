#ifndef ADDITIONALPOINTSWINDOW_H
#define ADDITIONALPOINTSWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QTextEdit>

class AdditionalPointsWindow : public QWidget
{
    Q_OBJECT

public:
    AdditionalPointsWindow(QWidget *parent = nullptr);

public:
    QVBoxLayout *oMainLayout;
    QGroupBox *oGroupBox;
    QVBoxLayout *oGroupBoxLayout;
    QTextEdit *oPointersTextEdit;
};

#endif // ADDITIONALPOINTSWINDOW_H
