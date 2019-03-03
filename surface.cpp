#include "surface.h"

Surface::Surface(QWidget *parent) : QOpenGLWidget(parent)
{
    //qDebug() << glGetString(GL_VERSION);

    this->oCitiesCoordinates = new QVector<Coordinate>();
    this->oAdditionalPointsCoordinates = new QVector<Coordinate>();

    this->oCitiesNames = new QStringList();
    this->oAdditionalPointsNames = new QStringList();

    QFile oCSVFile(":/main/world_cities.csv");
    if (!oCSVFile.open(QIODevice::ReadOnly)) {
        qDebug() << oCSVFile.errorString();
        return;
    }

    QByteArray oLine = oCSVFile.readLine();

    while (!oCSVFile.atEnd()) {
        oLine = oCSVFile.readLine();
        QList<QByteArray> oSplitedLine = oLine.split(',');

        this->oCitiesNames->append(QString(oSplitedLine[0]));

        this->oCitiesCoordinates->push_back(Coordinate(
            oSplitedLine[2].toFloat(),
            oSplitedLine[3].toFloat(),
            &this->oCitiesNames->last()
        ));
    }
}

Surface::~Surface()
{
    delete this->poVColorBoxShader;
    delete this->poFColorBoxShader;
    delete this->oEarthTexture;
    delete this->oCitiesCoordinates;
    delete this->oCitiesNames;
}

void Surface::initializeGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_ALPHA_TEST);

    QImage oEarthImage = QImage(QString(":/main/earth.jpg"));
    this->oEarthTexture = new QOpenGLTexture(oEarthImage);

    poVColorBoxShader = new QOpenGLShader(QOpenGLShader::Vertex);
    poFColorBoxShader = new QOpenGLShader(QOpenGLShader::Fragment);

    poVColorBoxShader->compileSourceFile(":/main/vcolorboxshader.vsh");
    poFColorBoxShader->compileSourceFile(":/main/fcolorboxshader.fsh");

    oShaderProgram.addShader(poVColorBoxShader);
    oShaderProgram.addShader(poFColorBoxShader);

    qDebug() << oShaderProgram.log();

    if (!oShaderProgram.link()) {
        qDebug() << "Error while linking shader program";
        return;
    }
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
        gluQuadricTexture(oQuadric, GL_TRUE);

        oShaderProgram.bind();

        glColor3f(1.0, 1.0, 1.0);
        this->oEarthTexture->bind(0);

        oShaderProgram.setUniformValue("texture", 0);

        gluSphere(oQuadric, 1.0, 360, 360);

        oShaderProgram.release();

        gluDeleteQuadric(oQuadric);
    }

    if (this->bShowCities) {
        glAlphaFunc(GL_NOTEQUAL, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(5.0);

        for (int iIndex=0; iIndex<this->oCitiesCoordinates->length(); iIndex++) {
            glPushMatrix();

            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90+30, 0.0, 1.0, 0.0);

            const Coordinate &oCoordinate = this->oCitiesCoordinates->at(iIndex);

            float fX = cos(qDegreesToRadians(oCoordinate.fLongitude))*cos(qDegreesToRadians(oCoordinate.fLatitude));
            float fY = -sin(qDegreesToRadians(oCoordinate.fLatitude));
            float fZ = -sin(qDegreesToRadians(oCoordinate.fLongitude))*cos(qDegreesToRadians(oCoordinate.fLatitude));

            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(1.0*fX, 1.0*fY, 1.0*fZ);
            glVertex3f(1.01*fX, 1.01*fY, 1.01*fZ);
            glEnd();

            glBegin(GL_POINTS);
            glColor4f(1.0, 0.0, 0.0, 0.5);
            glVertex3f(fX, fY, fZ);
            glEnd();

            glPopMatrix();
        }

        glDisable(GL_POINT_SMOOTH);
        glBlendFunc(GL_NONE, GL_NONE);
        glDisable(GL_BLEND);
    }

    if (this->bShowCity) {
        glAlphaFunc(GL_NOTEQUAL, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(5.0);

        const Coordinate &oCityCoordinate = this->oCitiesCoordinates->at(this->iCityId);

        glPushMatrix();

        glRotatef(90, 1.0, 0.0, 0.0);
        glRotatef(90+30, 0.0, 1.0, 0.0);

        float fX = cos(qDegreesToRadians(oCityCoordinate.fLongitude))*cos(qDegreesToRadians(oCityCoordinate.fLatitude));
        float fY = -sin(qDegreesToRadians(oCityCoordinate.fLatitude));
        float fZ = -sin(qDegreesToRadians(oCityCoordinate.fLongitude))*cos(qDegreesToRadians(oCityCoordinate.fLatitude));

        glBegin(GL_LINES);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(1.0*fX, 1.0*fY, 1.0*fZ);
        glVertex3f(1.05*fX, 1.05*fY, 1.05*fZ);
        glEnd();

        glBegin(GL_POINTS);
        glColor4f(1.0, 0.0, 0.0, 0.5);
        glVertex3f(fX, fY, fZ);
        glEnd();

        glPopMatrix();

        glDisable(GL_POINT_SMOOTH);
        glBlendFunc(GL_NONE, GL_NONE);
        glDisable(GL_BLEND);
    }

    if (this->bShowAdditionalPoints) {
        glAlphaFunc(GL_NOTEQUAL, 0);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(5.0);

        for (int iIndex=0; iIndex<this->oAdditionalPointsCoordinates->length(); iIndex++) {
            glPushMatrix();

            glRotatef(90, 1.0, 0.0, 0.0);
            glRotatef(90+30, 0.0, 1.0, 0.0);

            const Coordinate &oCoordinate = this->oAdditionalPointsCoordinates->at(iIndex);

            float fX = cos(qDegreesToRadians(oCoordinate.fLongitude))*cos(qDegreesToRadians(oCoordinate.fLatitude));
            float fY = -sin(qDegreesToRadians(oCoordinate.fLatitude));
            float fZ = -sin(qDegreesToRadians(oCoordinate.fLongitude))*cos(qDegreesToRadians(oCoordinate.fLatitude));

            glBegin(GL_LINES);
            glColor3f(1.0, 0.0, 0.0);
            glVertex3f(1.0*fX, 1.0*fY, 1.0*fZ);
            glVertex3f(1.01*fX, 1.01*fY, 1.01*fZ);
            glEnd();

            glBegin(GL_POINTS);
            glColor4f(1.0, 0.0, 0.0, 0.5);
            glVertex3f(fX, fY, fZ);
            glEnd();

            glPopMatrix();
        }

        glDisable(GL_POINT_SMOOTH);
        glBlendFunc(GL_NONE, GL_NONE);
        glDisable(GL_BLEND);
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
        1.0f-(2.0f*((float)(oPoint.y()-0)/(this->height()-0))),
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

        this->oRotateAngles += this->oRotateAnglesDelta*fRotateCoef;
        /*
        this->fXAngle += 8 * dy;
        this->fYAngle += 8 * dx;
        this->fZAngle += 0;
        */
        this->repaint();
    } else if (oEvent->buttons().testFlag(Qt::MouseButton::RightButton)) {
        this->oNewMousePosition = oEvent->pos();
        this->oOldMousePosition = this->oLastMousePosition;

        this->oRotateAngles += this->oRotateAnglesDelta*fRotateCoef;
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
