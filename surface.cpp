#include "surface.h"

Surface::Surface(QWidget *parent) : QOpenGLWidget(parent)
{
    this->oCoordinates = new QVector<Coordinate>();

    QFile oCSVFile(":/main/world_cities.csv");
    if (!oCSVFile.open(QIODevice::ReadOnly)) {
        qDebug() << oCSVFile.errorString();
        return;
    }

    QStringList wordList;
    while (!oCSVFile.atEnd()) {
        QByteArray line = oCSVFile.readLine();
        QList<QByteArray> oSplitedLine = line.split(',');

        this->oCoordinates->push_back(Coordinate(oSplitedLine[2].toFloat(), oSplitedLine[3].toFloat()));
    }
}

Surface::~Surface()
{
    delete this->oEarthTexture;
    delete this->oCoordinates;
}

void Surface::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    QImage oEarthImage = QImage(QString(":/main/earth.jpg"));
    this->oEarthTexture = new QOpenGLTexture(oEarthImage);
}

void Surface::resizeGL(int w, int h)
{
    /*
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0,  w,
            0,  h,
            0,  w);
    */

    glViewport(0, 0, w, h);
}

void Surface::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    gluLookAt(50, 50, 50,
              0, 0, 0,
              1, 0, 0);
    */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(1.0, 1.0, 1.0);

    qDebug() << "oRotateAngles" << oRotateAngles;
    glRotatef(this->oRotateAngles[0], 1.0, 0.0, 0.0);
    glRotatef(this->oRotateAngles[1], 0.0, 1.0, 0.0);
    glRotatef(this->oRotateAngles[2], 0.0, 0.0, 1.0);

    //glRotatef(30.0, 0.0, 0.0, 1.0);
    //glRotatef(30.0, 1.0, -1.0, 0.0);

    QVector4D oVectorNewMousePositon = this->fnCalculateWorldMousePosition(this->oNewMousePosition);
    QVector4D oVectorOldMousePositon = this->fnCalculateWorldMousePosition(this->oOldMousePosition);

    QVector3D oVectorNewMousePositonAngles = this->fnCalculateVectorAnglesToAxis(oVectorNewMousePositon);
    QVector3D oVectorOldMousePositonAngles = this->fnCalculateVectorAnglesToAxis(oVectorOldMousePositon);

    oRotateAnglesDelta = oVectorOldMousePositonAngles-oVectorNewMousePositonAngles;
    qDebug() << "oRotateAnglesDelta" << oRotateAnglesDelta;

    if (this->bShowMousePositionVectors) {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(oVectorNewMousePositon[0], oVectorNewMousePositon[1], oVectorNewMousePositon[2]);
        //glVertex3f(oVectorOldMousePositon[0], oVectorOldMousePositon[1], oVectorOldMousePositon[2]);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        //glVertex3f(oVectorNewMousePositon[0], oVectorNewMousePositon[1], oVectorNewMousePositon[2]);
        glVertex3f(oVectorOldMousePositon[0], oVectorOldMousePositon[1], oVectorOldMousePositon[2]);
        glEnd();
    }

    if (this->bShowAxis) {
        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-10.0, 0.0, 0.0);
        glVertex3f(10.0, 0.0, 0.0);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, -10.0, 0.0);
        glVertex3f(0.0, 10.0, 0.0);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, -10.0);
        glVertex3f(0.0, 0.0, 10.0);
        glEnd();
    }

    if (this->bShowEarth) {
        GLUquadricObj *oQuadric = gluNewQuadric();
        gluQuadricNormals(oQuadric, GLU_SMOOTH);
        gluQuadricTexture(oQuadric, true);

        glColor3f(1.0, 1.0, 1.0);
        this->oEarthTexture->bind();

        gluSphere(oQuadric, 0.5, 360, 360);
        gluDeleteQuadric(oQuadric);
    }

    if (this->bShowCities) {
        for (int iIndex=0; iIndex<this->oCoordinates->length(); iIndex++) {
            glPushMatrix();

            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90+30, 0.0, 1.0, 0.0);

            float x = 0.55*cos(qDegreesToRadians(this->oCoordinates->at(iIndex).fLongitude))*cos(qDegreesToRadians(this->oCoordinates->at(iIndex).fLatitude));
            float y = 0.55*-sin(qDegreesToRadians(this->oCoordinates->at(iIndex).fLatitude));
            float z = 0.55*-sin(qDegreesToRadians(this->oCoordinates->at(iIndex).fLongitude))*cos(qDegreesToRadians(this->oCoordinates->at(iIndex).fLatitude));

            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(0.0, 0.0, 0.0);
            glVertex3f(x, y, z);
            glEnd();

            glPopMatrix();
        }
    }

    glFlush();
}

void Surface::mousePressEvent(QMouseEvent *oEvent)
{
    this->oLastMousePosition = oEvent->pos();
    this->oOldMousePosition = this->oLastMousePosition;
}

QVector3D Surface::fnCalculateVectorAnglesToAxis(QVector4D oVector)
{
    QVector3D oResultVector = {0, 0, 0};

    oResultVector[0] = qRadiansToDegrees(acosf(oVector[0] / oVector.length()));
    oResultVector[1] = qRadiansToDegrees(acosf(oVector[1] / oVector.length()));
    oResultVector[2] = qRadiansToDegrees(acosf(oVector[2] / oVector.length()));

    qDebug() << oResultVector;

    return oResultVector;
}

QVector4D Surface::fnCalculateWorldMousePosition(QPoint oPoint)
{
    GLfloat afProjectionMatrix[16] = {0};
    glGetFloatv(GL_PROJECTION_MATRIX, afProjectionMatrix);
    QMatrix4x4 oProjectionMatrix(afProjectionMatrix);

    GLfloat afModelViewMatrix[16] = {0};
    glGetFloatv(GL_MODELVIEW_MATRIX, afModelViewMatrix);
    QMatrix4x4 oModelViewMatrix(afModelViewMatrix);

    //GLint aiViewport[4] = {0};
    //glGetIntegerv(GL_VIEWPORT, aiViewport);

    QMatrix4x4 oMultpliedMP = oProjectionMatrix*oModelViewMatrix;
    QMatrix4x4 oInvertedMP = oMultpliedMP.inverted();

    GLfloat fWinZ = -1;

    QVector4D oVectorMousePosition(
        (2.0f*((float)(oPoint.y()-0)/(this->height()-0)))-1.0f,
        1.0f-(2.0f*((float)(oPoint.x()-0)/(this->width()-0))),
        (float)2.0 * fWinZ - (float)1.0,
        1.0
    );

    QVector4D oVectorMouseWorldPosition = oVectorMousePosition*oInvertedMP;

    /*
    oVectorMouseWorldPosition[3] = 1.0 / oVectorMouseWorldPosition[3];
    oVectorMouseWorldPosition[2] *= oVectorMouseWorldPosition[3];
    oVectorMouseWorldPosition[1] *= oVectorMouseWorldPosition[3];
    oVectorMouseWorldPosition[0] *= oVectorMouseWorldPosition[3];
    */

    qDebug() << oVectorMouseWorldPosition;

    return oVectorMouseWorldPosition;
}

void Surface::mouseMoveEvent(QMouseEvent *oEvent)
{
    int dx = oEvent->x() - this->oLastMousePosition.x();
    int dy = oEvent->y() - this->oLastMousePosition.y();

    if (oEvent->buttons().testFlag(Qt::MouseButton::LeftButton)) {
        this->oNewMousePosition = oEvent->pos();
        this->oOldMousePosition = this->oLastMousePosition;

        this->oRotateAngles += this->oRotateAnglesDelta;
        /*
        this->fXAngle += 8 * dy;
        this->fYAngle += 8 * dx;
        this->fZAngle += 0;
        */
        this->repaint();
    } else if (oEvent->buttons().testFlag(Qt::MouseButton::RightButton)) {
        this->oNewMousePosition = oEvent->pos();
        this->oOldMousePosition = this->oLastMousePosition;

        this->oRotateAngles += this->oRotateAnglesDelta;
        /*
        this->fXAngle += 8 * dy;
        this->fYAngle += 0;
        this->fZAngle += 8 * dx;
        */
        this->repaint();
    }
    this->oLastMousePosition = oEvent->pos();
}

void Surface::mouseReleaseEvent(QMouseEvent * /* event */)
{
    //this->oRotateAngles += this->oRotateAnglesDelta;

    this->repaint();
    emit clicked();
}
