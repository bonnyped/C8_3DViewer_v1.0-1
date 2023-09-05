#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QSettings>
#include <QMessageBox>
#include <QShortcut>
#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include "myopenglwidget.h"
#include <qgifimage.h>
#include <string>
#include <QTimer> // for GIF
#include <QByteArray>
#define WIDTH_GIF 1920
#define HEIGHT_GIF 1920
#define ORGANIZATION_NAME "School21"
#define ORGANIZATION_DOMAIN "edu.21-school.ru"
#define APPLICATION_NAME "Hamlet3DViewer"
QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum typeLineL {
        SOLID,
        DASHED,
        };

enum typePointP {
        NONE,
        CIRCLE,
        SQUARE,
        };

enum typeProjectionP {
        PARALLEL,
        CENTRAL,
        };

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString fileName_2 = nullptr;

private slots:
    void style_viewer();

    void on_pButtonOpenFile_clicked();

    void onPositionRadioButtonStart();
    void on_radioButtonParallel_clicked();
    void on_radioButtonCentral_clicked();
    void on_radioButtonSolid_clicked();
    void on_radioButtonDashed_clicked();
    void on_radioButtonNone_clicked();
    void on_radioButtonCircle_clicked();
    void on_radioButtonSquare_clicked();

    void on_sliderRotationX_valueChanged(int value);
    void on_sliderRotationY_valueChanged(int value);
    void on_sliderRotationZ_valueChanged(int value);

    void setSliderPosition();
    void setSliderMinMaxStep();

    void on_SliderSizePoint_valueChanged(int value);
    void on_SliderSizeLine_valueChanged(int value);
    void on_sliderTranslateX_valueChanged(int value);
    void on_sliderTranslateY_valueChanged(int value);
    void on_sliderTranslateZ_valueChanged(int value);
    void on_sliderModelScale_valueChanged(int value);

    void on_pushButtonColorBackground_clicked();
    void on_pushButtonColorLines_clicked();
    void on_pushButtonColorPoints_clicked();

    void resetVert();

    void on_pushButtonScreen_clicked();
    void on_pushButtonGif_clicked();
    void screenGifTimerOn();

    void on_buttonRotationXMinus_clicked();
    void on_buttonRotationXPlus_clicked();
    void on_buttonRotationYMinus_clicked();
    void on_buttonRotationYPlus_clicked();
    void on_buttonRotationZMinus_clicked();
    void on_buttonRotationZPlus_clicked();

    void on_buttonTranslateXMinus_clicked();
    void on_buttonTranslateXPlus_clicked();
    void on_buttonTranslateYMinus_clicked();
    void on_buttonTranslateYPlus_clicked();
    void on_buttonTranslateZMinus_clicked();
    void on_buttonTranslateZPlus_clicked();

    void on_buttonScaleMinus_clicked();
    void on_buttonScalePlus_clicked();

private:
    Ui::MainWindow *ui;
    MyOpenGLWidget *myOpenGLWidget;
    void saveSettingsViewer();
    void loadSettingsViewer();
    QTimer *timerGif;
    void connectSlots();
    QGifImage *gifImage;
    QString gifName = nullptr;
    int framesCounter = -30;
    void paintEvent(QPaintEvent *event) override;
};


#endif // MAINWINDOW_H
