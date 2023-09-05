#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopenglwidget.h"
#include <iostream>
#include <QTextEdit>



MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
    :QOpenGLWidget {parent}
{
    setFormat(QSurfaceFormat::defaultFormat());
     setlocale(LC_NUMERIC, "C");
}

MyOpenGLWidget::~MyOpenGLWidget()
{
    free_model(&model);
    if (copyVert) {
        free(copyVert);
    }
}

void MyOpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST); // Буфер глубины
}

void MyOpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void MyOpenGLWidget::paintGL()
{
    setBackgroundColor(backgroundColor.redF(), backgroundColor.greenF(),backgroundColor.blueF());
    float a = normaliza_0_1(255.0, RGB_MIN, RGB_MAX);
    glClearColor(backgroundRed,backgroundGreen,backgroundBlue,a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                 // Очистка Буфер Цвета и Глубины

    if (model.extreme_values.max_all <= 1.0)
        model.extreme_values.max_all+= 1.0;

    glMatrixMode(GL_PROJECTION);                                    // матрица проекции
    glLoadIdentity();

    if (typeProjection == CENTRAL) {
        glFrustum(-1, 1,  -1,
                  1, model.extreme_values.max_all , model.extreme_values.max_all * 10);
        glTranslatef(0.0, 0.0, model.extreme_values.max_all*(-1.5));

    } else if (typeProjection == PARALLEL){
        glOrtho( -1, 1,  -1, 1,  1, 1);
    }
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_DOUBLE, 0, model.vertex_obj);

    drawLines();

    if (typePoints != NONE) {
        drawPoints();

    }
    glDisableClientState(GL_VERTEX_ARRAY);

}

void MyOpenGLWidget::drawLines()
{
    GLfloat a = normaliza_0_1(255.0, RGB_MIN, RGB_MAX);
    qColorToRGB(lineColor,lineRed,lineGreen,lineBlue);
    glColor4f(this->lineRed,this->lineGreen,this->lineBlue,a);

    if (typeLine == DASHED) {

        glEnable(GL_LINE_STIPPLE);// Открываем режим рисования линий
        glLineStipple(2,0X00FF);// Устанавливаем режим рисования линий

        glLineWidth(sizeLine);

        glDrawElements(GL_LINES,  model.number_struct.number_of_indexes*2, GL_UNSIGNED_INT, model.polygons_obj);

        glDisable(GL_LINE_STIPPLE);


    } else if (typeLine == SOLID) {
        glLineWidth(sizeLine);

        glDrawElements(GL_LINES,  model.number_struct.number_of_indexes*2, GL_UNSIGNED_INT, model.polygons_obj);

    }

}

void MyOpenGLWidget::drawPoints()
{
    GLfloat a = normaliza_0_1(255.0, RGB_MIN, RGB_MAX);
    qColorToRGB(pointColor,pointRed,pointGreen,pointBlue);
    glColor4f(this->pointRed,this->pointGreen,this->pointBlue, a);
    glPointSize(sizePoint);
    if (typePoints == CIRCLE) {
        glEnable(GL_POINT_SMOOTH);
        glDrawArrays(GL_POINTS, 0, model.number_struct.number_of_vertices);
        glDisable(GL_POINT_SMOOTH);
    } else if (typePoints == SQUARE) {
        glDrawArrays(GL_POINTS, 0, model.number_struct.number_of_vertices);
    }
}

int MyOpenGLWidget::MyOpenGLWidget::loadModel(const char *fileName)
{
    int status = ERROR;
    free_model(&this->model);
    this->model = {NULL,0,0,NULL,NULL,{0,0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    zero_out_the_structure (&model);
    status = parse_the_model_file_obj_head(&model, fileName);
    qDebug() << "status_parse = " << status;
    if (copyVert) {
        free(copyVert);
        copyVert = NULL;
    }
    if (status == ALL_RIGHT) {
        copyVert = (double*)calloc((model.number_struct.number_of_vertices*3), sizeof(double));
        for(size_t i = 0; i < model.number_struct.number_of_vertices *3; i++) {
            copyVert[i] = model.vertex_obj[i];
        }
    } else {
        free_model(&model);
        this->model = {NULL,0,0,NULL,NULL,{0,0},{0.0,0.0,0.0,0.0,0.0,0.0,0.0}};
    }
    return status;
}


// size line point
void MyOpenGLWidget::setSizePointValue(int value)
{
    sizePoint = value;
}

void MyOpenGLWidget::setSizeLineValue(int value)
{
    sizeLine = value;
}

int MyOpenGLWidget::getSizePointValue()
{
    return sizePoint;
}

int MyOpenGLWidget::getSizeLineValue()
{
    return sizeLine;
}

// TypeLine
void MyOpenGLWidget::setTypeLine(int type)
{
    typeLine = type;
}

int MyOpenGLWidget::getTypeLine()
{
    return typeLine;
}

//TypePoint
void MyOpenGLWidget::setTypePoint(int type)
{
    typePoints = type;
}

int MyOpenGLWidget::getTypePoint()
{
    return typePoints;
}

// TypeProjection
void MyOpenGLWidget::setTypeProjection(int type)
{
    typeProjection = type;
}

int MyOpenGLWidget::getTypeProjection()
{
    return typeProjection;
}

// scale
void MyOpenGLWidget::setScaleModel(double value)
{
    scale_model = value;
}

double MyOpenGLWidget::getScaleModel()
{
    return scale_model;
}

// rotate
void MyOpenGLWidget::setRotateX(double value)
{
    rotate_x = value;
}

double MyOpenGLWidget::getRotateX()
{
    return rotate_x;
}

void MyOpenGLWidget::setRotateY(double value)
{
    rotate_y = value;
}

double MyOpenGLWidget::getRotateY()
{
    return rotate_y;
}

void MyOpenGLWidget::setRotateZ(double value)
{
    rotate_z = value;
}

double MyOpenGLWidget::getRotateZ()
{
    return rotate_z;
}


// translate
void MyOpenGLWidget::setMoveX(double value)
{
    move_x = value;
}

double MyOpenGLWidget::getMoveX()
{
    return move_x;
}

void MyOpenGLWidget::setMoveY(double value)
{
    move_y = value;
}

double MyOpenGLWidget::getMoveY()
{
    return move_y;
}

void MyOpenGLWidget::setMoveZ(double value)
{
    move_z = value;
}

double MyOpenGLWidget::getMoveZ()
{
    return move_z;
}


// color
void MyOpenGLWidget::setPointQColor(QColor newColor)
{
    pointColor = newColor;
}

QString MyOpenGLWidget::getPointColorQString()
{
    return pointColor.name();
}

QColor MyOpenGLWidget::getPointColorQColor()
{
    return pointColor;
}

void MyOpenGLWidget::setLineColor(GLfloat r, GLfloat g, GLfloat b)
{
    this->lineRed = r;
    this->lineGreen = g;
    this->lineBlue = b;
}

void MyOpenGLWidget::setLineQColor(QColor newColor)
{
    lineColor = newColor;
}

QString MyOpenGLWidget::getLineColorQString()
{
    return lineColor.name();
}

QColor MyOpenGLWidget::getLineColorQColor()
{
    return lineColor;
}

void MyOpenGLWidget::setBackgroundQColor(QColor newColor)
{
    backgroundColor = newColor;
}

void MyOpenGLWidget::setBackgroundColor(GLfloat r, GLfloat g, GLfloat b)
{
    this->backgroundRed = r;
    this->backgroundGreen = g;
    this->backgroundBlue = b;
}

void MyOpenGLWidget::setPointColor(GLfloat r, GLfloat g, GLfloat b)
{
    this->pointRed = r;
    this->pointGreen = g;
    this->pointBlue = b;
}

void MyOpenGLWidget::qColorToRGB(const QColor &C, GLfloat  &r, GLfloat  &g, GLfloat  &b)
{
    r = normaliza_0_1(C.red(), RGB_MIN, RGB_MAX);
    g = normaliza_0_1(C.green(), RGB_MIN, RGB_MAX);
    b = normaliza_0_1(C.blue(), RGB_MIN, RGB_MAX);
}

float MyOpenGLWidget::normaliza_0_1(GLfloat  val, GLfloat  min, GLfloat  max) const
{
    return (val - min) / (max - min);
}

QString MyOpenGLWidget::getBackgroundColorQString()
{
    return backgroundColor.name();
}

QColor MyOpenGLWidget::getBackgroundColorQColor()
{
    return backgroundColor;
}










