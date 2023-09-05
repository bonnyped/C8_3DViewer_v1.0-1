#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#ifdef __APPLE__
/* Defined before OpenGL includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#endif

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#ifdef __cplusplus
extern "C"
{
#endif 
#include "../three_d_viewer.h"
#ifdef __cplusplus
}
#endif

#define RGB_MIN 1
#define RGB_MAX 255

class MyOpenGLWidget :public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyOpenGLWidget(QWidget *parent = nullptr);
     ~MyOpenGLWidget();

    void setBackgroundColor(GLfloat r, GLfloat g, GLfloat b);
    void setBackgroundQColor(QColor newColor);
    QString getBackgroundColorQString();
    QColor getBackgroundColorQColor();

    void setPointColor(GLfloat r, GLfloat g, GLfloat b);
    void setPointQColor(QColor newColor);
    QString getPointColorQString();
    QColor getPointColorQColor();

    void setLineColor(GLfloat r, GLfloat g, GLfloat b);
    void setLineQColor(QColor newColor);
    QString getLineColorQString();
    QColor getLineColorQColor();

    void setSizePointValue(int value);
    void setSizeLineValue(int value);
    int getSizePointValue();
    int getSizeLineValue();

    void setTypeProjection(int type);
    GLint getTypeProjection();
    void setTypeLine(int type);
    GLint getTypeLine();
    void setTypePoint(int type);
    GLint getTypePoint();

    void setScaleModel(double value);
    double getScaleModel();

    void setRotateX(double value);
    double getRotateX();
    void setRotateY(double value);
    double getRotateY();
    void setRotateZ(double value);
    double getRotateZ();

    void setMoveX(double value);
    double getMoveX();
    void setMoveY(double value);
    double getMoveY();
    void setMoveZ(double value);
    double getMoveZ();
    int loadModel(const char* fileName);
    
    QString fileName;
    model_v model = {NULL,0,0,NULL,NULL,{0,0},{0.0,0.0,0.0,0.0,0.0,0.0,0}};
    double *copyVert = NULL;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h)override;
    void paintGL() override;

private:
    GLvoid qColorToRGB(const QColor &C, float &r, float &g, float &b);
    GLfloat normaliza_0_1(float val, float min, float max) const;
    GLvoid drawLines();
    GLvoid drawPoints();

    GLfloat backgroundRed, backgroundGreen, backgroundBlue;
    QColor backgroundColor;
    GLfloat pointRed, pointGreen, pointBlue;
    QColor pointColor;
    GLint sizePoint;
    GLfloat lineRed, lineGreen, lineBlue;
    QColor lineColor;
    GLint sizeLine;

    GLint typeProjection = 0;
    GLint typeLine = 0;
    GLint typePoints = 1;

    GLdouble scale_model = 50;
    GLdouble rotate_x = 0;
    GLdouble rotate_y = 0;
    GLdouble rotate_z = 0;

    GLdouble move_x = 0;
    GLdouble move_y = 0;
    GLdouble move_z = 0;
};



#endif // MYOPENGLWIDGET_H
