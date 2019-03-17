#ifndef SURFACE_H
#define SURFACE_H

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QDebug>
#include <QFile>
#include <QMouseEvent>
#include <QtMath>
#include <QByteArray>
#include <QMatrix4x4>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QOpenGLVersionFunctions>
#include <QtOpenGL/qglfunctions>

#if defined(Q_OS_MACOS)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif
#if defined(Q_OS_LINUX)
#include <GL/glu.h>
#endif

struct Coordinate {
    Coordinate() {}
    Coordinate(float fLatitude, float fLongitude, QString *psCityName):
        fLatitude(fLatitude),
        fLongitude(fLongitude),
        psCityName(psCityName)
    {

    }

    QString *psCityName;
    float fLatitude = 0;
    float fLongitude = 0;
    float fColorR = 1.0;
    float fColorG = 0.0;
    float fColorB = 0.0;
    float fX = 0.0;
    float fY = 0.0;
    float fZ = 0.0;
    bool bShowDirection = false;
    bool bShow = false;
    float fDirectionLatitude = 0;
    float fDirectionLongitude = 0;
};

class Surface : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit Surface(QWidget *parent = nullptr);
    ~Surface();

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    QVector4D fnCalculateWorldMousePosition(QPoint oPoint);
    QVector3D fnCalculateVectorAnglesToAxis(QVector4D oVector);

public:
    QOpenGLTexture *oEarthTexture;
    QOpenGLTexture *oEarthPoliticalTexture;
    QVector<Coordinate> *oCitiesCoordinates;
    QStringList *oCitiesNames;
    QVector<Coordinate> *oAdditionalPointsCoordinates;
    QStringList *oAdditionalPointsNames;

    QOpenGLShader *poVColorBoxShader;
    QOpenGLShader *poFColorBoxShader;

    QOpenGLShaderProgram oShaderProgram;

    QPoint oLastMousePosition;
    QPoint oNewMousePosition;
    QPoint oOldMousePosition;
    QVector3D oRotateAngles = {0, 0, 0};
    QVector3D oRotateAnglesDelta = {0, 0, 0};

    bool bShowMousePositionVectors = false;
    bool bShowAxis = true;
    bool bShowEarth = true;
    bool bShowPoliticalEarthMap = true;
    bool bShowCenters = true;
    bool bShowColorBox = true;
    bool bShowCities = true;
    bool bShowCity = false;
    int iCityId = 0;
    bool bShowAdditionalPoints = false;

    float fRotateCoef = 8.0;

signals:

    void clicked();

public slots:
};

#endif // SURFACE_H
