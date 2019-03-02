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

#if defined(Q_OS_MACOS)
#include <OpenGL/glu.h>
#endif
#if defined(Q_OS_LINUX)
#include <GL/glu.h>
#endif

struct Coordinate {
    Coordinate() {}
    Coordinate(float fLatitude, float fLongitude):fLatitude(fLatitude), fLongitude(fLongitude) {}
    float fLatitude = 0;
    float fLongitude = 0;
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
protected:

    QOpenGLTexture *oEarthTexture;
    QVector<Coordinate> *oCoordinates;

    QPoint oLastMousePosition;
    QPoint oNewMousePosition;
    QPoint oOldMousePosition;
    QVector3D oRotateAngles = {0, 0, 0};
    QVector3D oRotateAnglesDelta = {0, 0, 0};

    bool bShowMousePositionVectors = false;
    bool bShowAxis = true;
    bool bShowEarth = true;
    bool bShowCities = true;

signals:

    void clicked();

public slots:
};

#endif // SURFACE_H
