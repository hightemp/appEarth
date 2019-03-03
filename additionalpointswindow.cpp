#include "additionalpointswindow.h"

AdditionalPointsWindow::AdditionalPointsWindow(QWidget *parent):
    QWidget(parent)
{
    this->hide();
    this->resize(600, 400);
    this->setWindowTitle("Additional points");

    this->oMainLayout = new QVBoxLayout();
    this->setLayout(this->oMainLayout);

    this->oGroupBox = new QGroupBox();
    this->oMainLayout->addWidget(this->oGroupBox);

    this->oGroupBoxLayout = new QVBoxLayout();
    this->oGroupBox->setLayout(this->oGroupBoxLayout);

    this->oPointersTextEdit = new QTextEdit();
    this->oGroupBoxLayout->addWidget(this->oPointersTextEdit);
}
