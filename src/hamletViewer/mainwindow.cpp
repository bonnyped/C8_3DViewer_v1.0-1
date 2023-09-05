#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "styleviewer.h"
#include <QTextEdit>
#include <QTabBar>
#include <QWidget>
#include <QPainter>
#include <QStyleOption>
#include <QShortcut>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

 setlocale(LC_NUMERIC, "C");
    ui->setupUi(this);
    myOpenGLWidget = this->findChild<MyOpenGLWidget *>("viewOpenGL");
    style_viewer();
    onPositionRadioButtonStart();
    setSliderMinMaxStep();
    setSliderPosition();
    ui->tabWidgetInfoModel->setCurrentIndex(1);
    ui->tabWidgetInfoModel->tabBar()->hide();
    loadSettingsViewer();
    timerGif = new QTimer(0);
    connectSlots();
}

MainWindow::~MainWindow()
{
    saveSettingsViewer();
    delete timerGif;
    delete ui;

}

void MainWindow::saveSettingsViewer()
{
    QSettings settingsSave("HAMLET_3D_VIEWER", "SET_HAMLET");
    settingsSave.setValue("settings", 1);
    settingsSave.setValue("background_color", ui->viewOpenGL->getBackgroundColorQColor());
    settingsSave.setValue("point_color", ui->viewOpenGL->getPointColorQColor());
    settingsSave.setValue("line_color", ui->viewOpenGL->getLineColorQColor());
    settingsSave.setValue("type_projection", ui->viewOpenGL->getTypeProjection());
    settingsSave.setValue("type_points", ui->viewOpenGL->getTypePoint());
    settingsSave.setValue("type_lines", ui->viewOpenGL->getTypeLine());
    settingsSave.setValue("size_points", ui->viewOpenGL->getSizePointValue());
    settingsSave.setValue("size_lines", ui->viewOpenGL->getSizeLineValue());
}

void MainWindow::loadSettingsViewer()
{

    QSettings settingsLoad("HAMLET_3D_VIEWER", "SET_HAMLET");
    if (settingsLoad.value("settings").toInt()) {
        // COLOR
        QVariant color = settingsLoad.value("background_color");
        QColor v = color.value<QColor>();
        ui->viewOpenGL->setBackgroundQColor(v);
        ui->pushButtonColorBackground->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + ui->viewOpenGL->getBackgroundColorQString());

        color = settingsLoad.value("point_color");
        v = color.value<QColor>();
        ui->viewOpenGL->setPointQColor(v);
        ui->pushButtonColorPoints->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + ui->viewOpenGL->getPointColorQString());
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(0, ui->viewOpenGL->getPointColorQString());

        color = settingsLoad.value("line_color");
        v = color.value<QColor>();
        ui->viewOpenGL->setLineQColor(v);
        ui->pushButtonColorLines->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + ui->viewOpenGL->getLineColorQString());
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(1, ui->viewOpenGL->getLineColorQString());

        // Type
        ui->viewOpenGL->setTypeProjection(settingsLoad.value("type_projection").toInt());
        ui->viewOpenGL->setTypePoint(settingsLoad.value("type_points").toInt());
        ui->viewOpenGL->setTypeLine(settingsLoad.value("type_lines").toInt());
        onPositionRadioButtonStart();

        //Position slider (size point and line)
        ui->viewOpenGL->setSizePointValue(settingsLoad.value("size_points").toInt());
        ui->viewOpenGL->setSizeLineValue(settingsLoad.value("size_lines").toInt());
        ui->SliderSizePoint->setValue(ui->viewOpenGL->getSizePointValue());
        ui->SliderSizeLine->setValue(ui->viewOpenGL->getSizeLineValue());

        // file ???

        //
        ui->viewOpenGL->update();
    } else {
        QColor newColorBackground = Qt::black;
        QColor newColorLine = Qt::white;
        QColor newColorPoint = Qt::red;
        ui->pushButtonColorBackground->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + newColorBackground.name());
        ui->viewOpenGL->setBackgroundQColor(newColorBackground);
        ui->viewOpenGL->setBackgroundColor(newColorBackground.redF(), newColorBackground.greenF(),newColorBackground.blueF());
        ui->pushButtonColorLines->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + newColorLine.name());
        ui->viewOpenGL->setLineQColor(newColorLine);
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(1, ui->viewOpenGL->getLineColorQString());
        ui->viewOpenGL->setLineColor(newColorLine.redF(), newColorLine.greenF(),newColorLine.blueF());
        ui->pushButtonColorPoints->setStyleSheet("border: 1px; border-radius: 6px; background-color: " + newColorPoint.name());
        ui->viewOpenGL->setPointQColor(newColorPoint);
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(0, ui->viewOpenGL->getPointColorQString());
    }
}

void MainWindow::onPositionRadioButtonStart()
{

    if (ui->viewOpenGL->getTypeProjection() == CENTRAL) {
        ui->radioButtonCentral->setChecked(true);
        ui->viewOpenGL->setTypeProjection(CENTRAL);
    } else {
        ui->radioButtonParallel->setChecked(true);
        ui->viewOpenGL->setTypeProjection(PARALLEL);
    }


    if (ui->viewOpenGL->getTypePoint() == CIRCLE) {
        ui->radioButtonCircle->setChecked(true);
    } else if (ui->viewOpenGL->getTypePoint() == SQUARE){
        ui->radioButtonSquare->setChecked(true);
    } else {
        ui->radioButtonNone->setChecked(true);
    }


    if (ui->viewOpenGL->getTypeLine() == DASHED) {
        ui->radioButtonDashed->setChecked(true);
    } else {
        ui->radioButtonSolid->setChecked(true);
    }
}

void MainWindow::style_viewer()
{
    this->setStyleSheet(StyleViewer::getStartMainWindow());
    //    ui->tabLinePointWidget->setStyleSheet(StyleViewer::getQTabWidgetStart());
    ui->frameTypeProjection->setStyleSheet(StyleViewer::getStartQFrameHead());
    ui->frameBackgroundColor->setStyleSheet(StyleViewer::getStartQFrame());
    ui->frameRotation->setStyleSheet(StyleViewer::getStartQFrame());
    ui->frameTranslate->setStyleSheet(StyleViewer::getStartQFrame());
    ui->frameModelScale->setStyleSheet(StyleViewer::getStartQFrame());
    ui->frameLine_typeLines->setStyleSheet(StyleViewer::getStartQFrame());
    ui->framePoints->setStyleSheet(StyleViewer::getStartQFrame());

    //type projection
    ui->radioButtonCentral->setStyleSheet(StyleViewer::getRadioButtonInfo());
    ui->radioButtonParallel->setStyleSheet(StyleViewer::getRadioButtonInfo());
    // points
    ui->radioButtonNone->setStyleSheet(StyleViewer::getRadioButtonInfo());
    ui->radioButtonCircle->setStyleSheet(StyleViewer::getRadioButtonInfo());
    ui->radioButtonSquare->setStyleSheet(StyleViewer::getRadioButtonInfo());
    //lines
    ui->radioButtonSolid->setStyleSheet(StyleViewer::getRadioButtonInfo());
    ui->radioButtonDashed->setStyleSheet(StyleViewer::getRadioButtonInfo());

    //line Info SETTINGS
    ui->labelProjectionTypeText->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextBackground->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextRotation->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextXRotation->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextYRotation->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextZRotation->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextTranslate->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextXTranslate->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextYTranslate->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextZTranslate->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextModelScale->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextLineColor->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextSizeLines->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextPointsColor->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelTextSizePoints->setStyleSheet(StyleViewer::getQLabelInfo());
    ui->labelPathToTheModelFile->setStyleSheet(StyleViewer::getQLabelPathFile());
    ui->pButtonOpenFile->setStyleSheet(StyleViewer::getPushButtonOpenFile());
    ui->toolButtonReset ->setStyleSheet(StyleViewer::getPushButtonRebootSettings());
    //line ModelInfo tab
    ui->labelTextFileName->setStyleSheet(StyleViewer::getQLabelModelText());
    ui->labelTextNumberVertex->setStyleSheet(StyleViewer::getQLabelModelText());
    ui->labelTextNumberEdges->setStyleSheet(StyleViewer::getQLabelModelText());
    ui->labelInfoFileName->setStyleSheet(StyleViewer::getQLabelModelInfo());
    ui->labelInfoNumberVertex->setStyleSheet(StyleViewer::getQLabelModelInfo());
    ui->labelInfoNumberEdges->setStyleSheet(StyleViewer::getQLabelModelInfo());

    // pushButton
    ui->pushButtonScreen->setStyleSheet(StyleViewer::getPushButtonScreen());
    ui->pushButtonGif->setStyleSheet(StyleViewer::getPushButtonGif());

}

void MainWindow::connectSlots()
{
    connect(ui->toolButtonReset, &QPushButton::clicked, this, &MainWindow::setSliderPosition);
    connect(ui->toolButtonReset, &QPushButton::clicked, this, &MainWindow::resetVert);
    connect(timerGif, SIGNAL(timeout()), this, SLOT(screenGifTimerOn()));
}

void MainWindow::setSliderPosition() {

    ui->SliderSizePoint->setValue(1);
    ui->SliderSizeLine->setValue(1);
    ui->sliderModelScale->setValue(50);
    ui->sliderRotationX->setValue(0);
    ui->sliderRotationY->setValue(0);
    ui->sliderRotationZ->setValue(0);
    ui->sliderTranslateX->setValue(0);
    ui->sliderTranslateY->setValue(0);
    ui->sliderTranslateZ->setValue(0);
    ui->viewOpenGL->update();
}

void MainWindow::setSliderMinMaxStep() {
    ui->sliderRotationX->setMinimum(-360);
    ui->sliderRotationX->setMaximum(360);
    ui->sliderRotationX->setTickInterval(1);
    ui->sliderRotationY->setMinimum(-360);
    ui->sliderRotationY->setMaximum(360);
    ui->sliderRotationY->setTickInterval(1);
    ui->sliderRotationZ->setMinimum(-360);
    ui->sliderRotationZ->setMaximum(360);
    ui->sliderRotationZ->setTickInterval(1);
    ui->SliderSizePoint->setMinimum(1);
    ui->SliderSizePoint->setMaximum(64);
    ui->SliderSizePoint->setTickInterval(1);
    ui->SliderSizeLine->setMinimum(1);
    ui->SliderSizeLine->setMaximum(16);
    ui->SliderSizeLine->setTickInterval(1);
    ui->sliderTranslateX->setMinimum(-150);
    ui->sliderTranslateX->setMaximum(150);
    ui->sliderTranslateX->setTickInterval(1);
    ui->sliderTranslateY->setMinimum(-150);
    ui->sliderTranslateY->setMaximum(150);
    ui->sliderTranslateY->setTickInterval(1);
    ui->sliderTranslateZ->setMinimum(-200);
    ui->sliderTranslateZ->setMaximum(200);
    ui->sliderTranslateZ->setTickInterval(1);
    ui->sliderModelScale->setMinimum(0);
    ui->sliderModelScale->setMaximum(1000);
    ui->sliderModelScale->setTickInterval(1);
}

// push Button Open File
void MainWindow::on_pButtonOpenFile_clicked()
{
    int status_load = ERROR;
    QString fileName = QFileDialog::getOpenFileName(this,QString::fromUtf8("Open a file"), QDir::homePath() + "/Desktop/","tr(*.obj)",0,QFileDialog::DontUseNativeDialog);
    QByteArray fileNameBa= fileName.toLocal8Bit();
    char *fname = fileNameBa.data();
    QFileInfo fileInfo(fileName);
    setSliderPosition();
    ui->labelPathToTheModelFile->setText(fname);
    ui->viewOpenGL->fileName = fileName;
    status_load = myOpenGLWidget->loadModel(fname);
    qDebug() << "status load = " <<status_load << "\n";
    if (status_load == ALL_RIGHT) {
        ui->tabWidgetInfoModel->setCurrentIndex(0);
        ui->labelInfoFileName->setText(" " + fileInfo.fileName());
        ui->labelInfoNumberEdges->setText(QString::number(ui->viewOpenGL->model.number_struct.number_of_indexes / 2));
        ui->labelInfoNumberVertex->setText(QString::number(ui->viewOpenGL->model.number_struct.number_of_vertices));
    } else {
        ui->tabWidgetInfoModel->setCurrentIndex(1);
        ui->labelInfoFileName->setText(" ");
        ui->labelInfoNumberEdges->setText("ERROR");
        ui->labelInfoNumberVertex->setText("ERROR");
    }

}

// radioButton position
void MainWindow::on_radioButtonParallel_clicked()
{
    ui->viewOpenGL->setTypeProjection(PARALLEL);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonCentral_clicked()
{
    ui->viewOpenGL->setTypeProjection(CENTRAL);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonSolid_clicked()
{
    ui->viewOpenGL->setTypeLine(SOLID);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonDashed_clicked()
{
    ui->viewOpenGL->setTypeLine(DASHED);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonNone_clicked()
{
    ui->viewOpenGL->setTypePoint(NONE);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonCircle_clicked()
{
    ui->viewOpenGL->setTypePoint(CIRCLE);
    ui->viewOpenGL->update();
}

void MainWindow::on_radioButtonSquare_clicked()
{
    ui->viewOpenGL->setTypePoint(SQUARE);
    ui->viewOpenGL->update();
}


// slider
void MainWindow::on_sliderRotationX_valueChanged(int value)
{
    x_axis_rotation(&ui->viewOpenGL->model, ((double)value - ui->viewOpenGL->getRotateX()));
    ui->viewOpenGL->setRotateX(value);
    ui->viewOpenGL->update();
}

void MainWindow::on_sliderRotationY_valueChanged(int value)
{
    y_axis_rotation(&ui->viewOpenGL->model, (value - ui->viewOpenGL->getRotateY()));
    ui->viewOpenGL->setRotateY(static_cast<double>(value));
    ui->viewOpenGL->update();

}

void MainWindow::on_sliderRotationZ_valueChanged(int value)
{
    z_axis_rotation(&ui->viewOpenGL->model, (value - ui->viewOpenGL->getRotateZ()));
    ui->viewOpenGL->setRotateZ(static_cast<double>(value));
    ui->viewOpenGL->update();
}

void MainWindow::on_SliderSizePoint_valueChanged(int value)
{
    ui->viewOpenGL->setSizePointValue(value);
    ui->viewOpenGL->update();
}

void MainWindow::on_SliderSizeLine_valueChanged(int value)
{
    ui->viewOpenGL->setSizeLineValue(value);
    ui->viewOpenGL->update();
}

void MainWindow::on_sliderTranslateX_valueChanged(int value)
{
    move_the_model_along_the_x_axis(&ui->viewOpenGL->model, (static_cast<double>(value) - ui->viewOpenGL->getMoveX()) *
                                      ui->viewOpenGL->model.extreme_values.max_all / 100);
    ui->viewOpenGL->setMoveX(static_cast<double>(value));
    ui->viewOpenGL->update();
}

void MainWindow::on_sliderTranslateY_valueChanged(int value)
{
    move_the_model_along_the_y_axis(&ui->viewOpenGL->model, (static_cast<double>(value) - ui->viewOpenGL->getMoveY()) *
                                                                ui->viewOpenGL->model.extreme_values.max_all / 100);
    ui->viewOpenGL->setMoveY(static_cast<double>(value));
    ui->viewOpenGL->update();
}


void MainWindow::on_sliderTranslateZ_valueChanged(int value)
{
    move_the_model_along_the_z_axis(&ui->viewOpenGL->model, (static_cast<double>(value) - ui->viewOpenGL->getMoveZ()) *
                                                                ui->viewOpenGL->model.extreme_values.max_all / 100);
    ui->viewOpenGL->setMoveZ(static_cast<double>(value));
    ui->viewOpenGL->update();
}

void MainWindow::on_sliderModelScale_valueChanged(int value)
{
    if (value) {
        double  coof_scale = static_cast<double>(value) / ui->viewOpenGL->getScaleModel();
        model_scale(&ui->viewOpenGL->model, coof_scale);
        ui->viewOpenGL->setScaleModel(static_cast<double>(value));
        ui->viewOpenGL->update();
    }
}


// Color
void MainWindow::on_pushButtonColorBackground_clicked()
{
    QColor newColorBackground = QColorDialog::getColor(Qt::red, this, tr("Select Background Color"));
    if (newColorBackground.isValid()) {
        ui->pushButtonColorBackground->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + newColorBackground.name());
        ui->viewOpenGL->setBackgroundQColor(newColorBackground);
        ui->viewOpenGL->setBackgroundColor(newColorBackground.redF(), newColorBackground.greenF(),newColorBackground.blueF());
       //
        ui->viewOpenGL->update();
    }
}

void MainWindow::on_pushButtonColorLines_clicked()
{
    QColor newColorLine = QColorDialog::getColor(Qt::red, this, tr("Select Line Color"));
    if (newColorLine.isValid()) {
        ui->pushButtonColorLines->setStyleSheet("border: 1px; border-radius: 13px; background-color: " + newColorLine.name());
        ui->viewOpenGL->setLineQColor(newColorLine);
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(1, ui->viewOpenGL->getLineColorQString());
        ui->viewOpenGL->setLineColor(newColorLine.redF(), newColorLine.greenF(),newColorLine.blueF());
        //
        ui->viewOpenGL->update();
    }
}

void MainWindow::on_pushButtonColorPoints_clicked()
{
    QColor newColorPoint = QColorDialog::getColor(Qt::red, this, tr("Select Point Color"));
    if (newColorPoint.isValid()) {
        ui->pushButtonColorPoints->setStyleSheet("border: 1px; border-radius: 6px; background-color: " + newColorPoint.name());
        ui->viewOpenGL->setPointQColor(newColorPoint);
        ui->tabLinePointWidget->tabBar()->QTabBar::setTabTextColor(0, ui->viewOpenGL->getPointColorQString());
        ui->viewOpenGL->update();
    }
}


// push Buttons
void MainWindow::resetVert()
{
    if (ui->viewOpenGL->copyVert) {
        for(size_t i = 0; i < ui->viewOpenGL->model.number_struct.number_of_vertices *3;i++)
            ui->viewOpenGL->model.vertex_obj[i] = ui->viewOpenGL->copyVert[i];
    }
    ui->viewOpenGL->update();
}

// SCREEN
void MainWindow::on_pushButtonScreen_clicked()
{
    QImage screen = ui->viewOpenGL->grabFramebuffer();
     QString nameObjFile = nullptr;
    if (ui->labelInfoFileName->text() != "") {
        nameObjFile = ui->labelInfoFileName->text().replace(QString(".obj"), QString(""));
        nameObjFile = nameObjFile.replace(QString(" "), QString("_"));
        QDateTime current_date = QDateTime::currentDateTime();
        QString formattedTime = current_date.toString("_dd-MM_hh-mm-ss");
        QString namePattern = "hamlet_viewer" + nameObjFile + formattedTime;
        QString filter = "jpeg file (*.jpeg);;BMP-file (*.bmp)";
        QString nameScreen = QFileDialog::getSaveFileName(this,
                                                             tr("Save as..."),
                                                             namePattern + ".jpeg",
                                                             filter,
                                                             &filter,
                                                             QFileDialog::DontUseNativeDialog);
        if(nameScreen != "") {
            screen.save(nameScreen);
            QMessageBox messageBoxImage;
            messageBoxImage.setText("Screenshot saved:");
            messageBoxImage.setInformativeText(nameScreen);
            messageBoxImage.exec();
        }
    } else {
        nameObjFile = "Ofelia_DEAD";
    }
    unsigned char *output = 0;
    output = new unsigned char[1980 * 1980 * 3];
    glReadPixels(0,0, 1980, 1980, GL_RGB, GL_UNSIGNED_BYTE,
                 output);
}

// GIF  1 Head
void MainWindow::on_pushButtonGif_clicked()
{
    QString name_obj_file = nullptr;
        if (ui->labelInfoFileName->text() != "") {
            name_obj_file = ui->labelInfoFileName->text().replace(QString(".obj"), QString(""));
            name_obj_file = name_obj_file.replace(QString(" "), QString("_"));
        } else {
            name_obj_file = "Ofelia_DEAD";
        }
        QDateTime current_date = QDateTime::currentDateTime();
        QString formattedTime = current_date.toString("_dd-MM_hh-mm-ss");
        QString name_pattern = "hamlet_viewer" + name_obj_file + formattedTime + ".gif";
        gifName = QFileDialog::getSaveFileName(this, tr("Save a gif animation"),
                                      name_pattern,  tr("gif (*.gif)"),nullptr,QFileDialog::DontUseNativeDialog);
        qDebug()<<"!" << gifName<< "!\n";
        if (gifName != "") {
            ui->pushButtonGif->setDisabled(true);
            gifImage= new QGifImage;
            gifImage->setDefaultDelay(10);
            timerGif->setInterval(100);
            timerGif->start();
        }
}


// GIF 2 timer == on
void MainWindow::screenGifTimerOn()
{
    QImage image = ui->viewOpenGL->grabFramebuffer();
    QSize image_size(WIDTH_GIF, HEIGHT_GIF);
    QImage scaled_image = image.scaled(image_size);
    if (framesCounter == 50) {
        timerGif->stop();
        gifImage->save(gifName);
        framesCounter = -30;
        QMessageBox messageBoxGif;
        messageBoxGif.setText("GIF saved:");
        messageBoxGif.setInformativeText(gifName);
        messageBoxGif.exec();
        delete gifImage;
        ui->pushButtonGif->setText("");
        ui->pushButtonGif->setEnabled(true);
        ui->labelGifTimer->setText("");
    } else if (framesCounter < 50 && framesCounter >= 0) {
        gifImage->addFrame(scaled_image.scaled(640,480,Qt::IgnoreAspectRatio,Qt::SmoothTransformation),0);
    } else if (framesCounter < 0) {
        ui->labelGifTimer->setText(QString::number(abs(framesCounter) / 10));
        ui->labelGifTimer->setStyleSheet("QLabel {""color: red;""}");
    }
    framesCounter++;
    if (framesCounter < 51 && framesCounter >= 0) {
        ui->labelGifTimer->setText(QString::number(framesCounter / 10));
        ui->labelGifTimer->setStyleSheet("QLabel {""color: yellow;""}");
    }
}


// PUSHBUTTONS: + and -
void MainWindow::on_buttonRotationXMinus_clicked()
{
    ui->sliderRotationX->setValue(ui->sliderRotationX->value() - 1);
}

void MainWindow::on_buttonRotationXPlus_clicked()
{
    ui->sliderRotationX->setValue(ui->sliderRotationX->value() + 1);
}

void MainWindow::on_buttonRotationYMinus_clicked()
{
    ui->sliderRotationY->setValue(ui->sliderRotationY->value() - 1);
}

void MainWindow::on_buttonRotationYPlus_clicked()
{
    ui->sliderRotationY->setValue(ui->sliderRotationY->value() + 1);
}

void MainWindow::on_buttonRotationZMinus_clicked()
{
    ui->sliderRotationZ->setValue(ui->sliderRotationZ->value() - 1);
}

void MainWindow::on_buttonRotationZPlus_clicked()
{
     ui->sliderRotationZ->setValue(ui->sliderRotationZ->value() + 1);
}

void MainWindow::on_buttonTranslateXMinus_clicked()
{
    ui->sliderTranslateX->setValue(ui->sliderTranslateX->value() - 1);
}

void MainWindow::on_buttonTranslateXPlus_clicked()
{
    ui->sliderTranslateX->setValue(ui->sliderTranslateX->value() + 1);
}

void MainWindow::on_buttonTranslateYMinus_clicked()
{
    ui->sliderTranslateY->setValue(ui->sliderTranslateY->value() - 1);
}

void MainWindow::on_buttonTranslateYPlus_clicked()
{
    ui->sliderTranslateY->setValue(ui->sliderTranslateY->value() + 1);
}

void MainWindow::on_buttonTranslateZMinus_clicked()
{
    ui->sliderTranslateZ->setValue(ui->sliderTranslateZ->value() - 1);
}

void MainWindow::on_buttonTranslateZPlus_clicked()
{
    ui->sliderTranslateZ->setValue(ui->sliderTranslateZ->value() + 1);
}

void MainWindow::on_buttonScaleMinus_clicked()
{
    ui->sliderModelScale->setValue(ui->sliderModelScale->value() - 1);
}

void MainWindow::on_buttonScalePlus_clicked()
{
    ui->sliderModelScale->setValue(ui->sliderModelScale->value() + 1);
}



// для отключения наследования от главного окна
void MainWindow::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QMainWindow::paintEvent(event);
}
