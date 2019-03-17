#include "additionalpointswindow.h"

AdditionalPointsWindow::AdditionalPointsWindow(QWidget *parent):
    QWidget(parent)
{
    Qt::WindowFlags iFlags = Qt::Window;

    this->setWindowFlags(iFlags);

    this->move(((MainWindow *)this->parent())->rect().center());

    this->hide();
    this->resize(600, 400);
    this->setWindowTitle("Additional points");

    this->oMainLayout = new QVBoxLayout();
    this->setLayout(this->oMainLayout);

    this->oGroupBox = new QGroupBox();
    this->oMainLayout->addWidget(this->oGroupBox);

    this->oGroupBoxLayout = new QVBoxLayout();
    this->oGroupBox->setLayout(this->oGroupBoxLayout);

    this->oCommentLabel = new QLabel();
    this->oCommentLabel->setText("Name, Latitude, Longitude[, Color, Direction Latitude, Direction Longitude]");
    this->oGroupBoxLayout->addWidget(this->oCommentLabel);

    this->oAdditionalPointsTextEdit = new QTextEdit();
    this->oGroupBoxLayout->addWidget(this->oAdditionalPointsTextEdit);

    this->oBottomLayout = new QHBoxLayout();
    this->oBottomLayout->setAlignment(Qt::AlignRight);
    this->oMainLayout->addLayout(this->oBottomLayout);

    this->oSaveButton = new QPushButton();
    this->oSaveButton->setText("Save");
    connect(this->oSaveButton, SIGNAL(clicked(bool)), this, SLOT(fnOnSaveClick(bool)));
    this->oBottomLayout->addWidget(this->oSaveButton);

    this->oCancelButton = new QPushButton();
    this->oCancelButton->setText("Cancel");
    connect(this->oCancelButton, SIGNAL(clicked(bool)), this, SLOT(fnOnCancelClick(bool)));
    this->oBottomLayout->addWidget(this->oCancelButton);
}

void AdditionalPointsWindow::fnLoadCSVFile()
{
    QFile oCSVFile("additional_points.csv");

    Surface *oSurface = ((MainWindow *) this->parent())->oSurface;

    oSurface->oAdditionalPointsNames->clear();
    oSurface->oAdditionalPointsCoordinates->clear();

    this->oAdditionalPointsTextEdit->clear();

    if (oCSVFile.open(QFile::ReadOnly)) {
        while (!oCSVFile.atEnd()) {
            QByteArray oLine = oCSVFile.readLine();
            this->oAdditionalPointsTextEdit->append(QString(oLine).remove(QChar('\n')));

            QList<QByteArray> oSplitedLine = oLine.split(',');

            if (oSplitedLine.length()<3) {
                qDebug() << "Wrong number (<3) of arguments: " << oLine;
                continue;
            }

            oSurface->oAdditionalPointsNames->append(QString(oSplitedLine[0]));

            oSurface->oAdditionalPointsCoordinates->push_back(Coordinate(
                oSplitedLine[1].toFloat(),
                oSplitedLine[2].toFloat(),
                &oSurface->oAdditionalPointsNames->last()
            ));

            Coordinate &oC = oSurface->oAdditionalPointsCoordinates->last();
            oC.fX = cos(qDegreesToRadians(oC.fLongitude))*cos(qDegreesToRadians(oC.fLatitude));
            oC.fY = -sin(qDegreesToRadians(oC.fLatitude));
            oC.fZ = -sin(qDegreesToRadians(oC.fLongitude))*cos(qDegreesToRadians(oC.fLatitude));

            if (oSplitedLine.length()>=4) {
                bool bStatus = false;
                unsigned int uiColor = QString(oSplitedLine[3]).toUInt(&bStatus, 16);
                oC.fColorR = uiColor >> 16 & 0xFF;
                oC.fColorG = uiColor >> 8 & 0xFF;
                oC.fColorB = uiColor & 0xFF;
            }

            if (oSplitedLine.length()>=6) {
                oC.bShowDirection = true;
                oC.fDirectionLatitude = oSplitedLine[4].toFloat();
                oC.fDirectionLongitude = oSplitedLine[5].toFloat();
            }
        }
    }

    oCSVFile.close();

    emit fnUpdatePoints(oSurface->oAdditionalPointsNames);
}

void AdditionalPointsWindow::fnOnCancelClick(bool bChecked)
{
    this->hide();
}

void AdditionalPointsWindow::fnOnSaveClick(bool bChecked)
{
    Surface *oSurface = ((MainWindow *) this->parent())->oSurface;

    oSurface->oAdditionalPointsNames->clear();
    oSurface->oAdditionalPointsCoordinates->clear();

    QFile oCSVFile("additional_points.csv");

    if (oCSVFile.open(QFile::WriteOnly)) {
        oCSVFile.write(QByteArray(this->oAdditionalPointsTextEdit->toPlainText().toUtf8()));
    } else {
        qDebug() << "Can't save to file additional_points.csv";
    }

    oCSVFile.close();

    QStringList oStringList(this->oAdditionalPointsTextEdit->toPlainText().split('\n'));

    for (int iIndex=0; iIndex<oStringList.length(); iIndex++) {
        qDebug() << oStringList.at(iIndex).split(',');
        QStringList oSplitedLine = oStringList.at(iIndex).split(',');

        if (oSplitedLine.length()<3) {
            qDebug() << "Wrong number (<3) of arguments: " << oStringList.at(iIndex);
            continue;
        }

        oSurface->oAdditionalPointsNames->append(oSplitedLine[0]);
        //qDebug() << oSurface << oSurface->oAdditionalPointsNames << oSplitedLine[0];
        //qDebug() << oSplitedLine[1].toFloat() << oSplitedLine[2].toFloat() << &oSurface->oAdditionalPointsNames->last() << oSurface->oAdditionalPointsNames->last();

        oSurface->oAdditionalPointsCoordinates->push_back(Coordinate(
            oSplitedLine[1].toFloat(),
            oSplitedLine[2].toFloat(),
            &oSurface->oAdditionalPointsNames->last()
        ));

        Coordinate &oC = oSurface->oAdditionalPointsCoordinates->last();
        oC.fX = cos(qDegreesToRadians(oC.fLongitude))*cos(qDegreesToRadians(oC.fLatitude));
        oC.fY = -sin(qDegreesToRadians(oC.fLatitude));
        oC.fZ = -sin(qDegreesToRadians(oC.fLongitude))*cos(qDegreesToRadians(oC.fLatitude));

        if (oSplitedLine.length()>=4) {
            bool bStatus = false;
            unsigned int uiColor = QString(oSplitedLine[3]).toUInt(&bStatus, 16);
            oC.fColorR = uiColor >> 16 & 0xFF;
            oC.fColorG = uiColor >> 8 & 0xFF;
            oC.fColorB = uiColor & 0xFF;
        }

        if (oSplitedLine.length()>=6) {
            oC.bShowDirection = true;
            oC.fDirectionLatitude = oSplitedLine[4].toFloat();
            oC.fDirectionLongitude = oSplitedLine[5].toFloat();
        }
    }

    this->hide();

    emit fnUpdatePoints(oSurface->oAdditionalPointsNames);
}
