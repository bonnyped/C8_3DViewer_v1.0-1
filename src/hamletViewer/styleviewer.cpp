#include "styleviewer.h"


QString StyleViewer::getStartButton()
{
    return "QPushButton {"
           "    border-button: none;"
           "    image: url(:resources/open_directory.svg);"
           "    color: rgb(230, 46, 46);"
           "}";
}

QString StyleViewer::getStartMainWindow()
{
    return " QMainWindow {"
           "background-color:rgb(56, 57, 58);"
           "}";
}

QString StyleViewer::getStartQFrame()
{
    return " QFrame {"
           "    border-radius: 15px;"
           "    background-color: rgb(46, 47, 48);"
           "}";
}

QString StyleViewer::getStartQFrameHead()
{
    return " QFrame {"
           "    border-top-left-radius: 15px;"
           "    border-top-right-radius: 15px;"
           "    background-color: rgb(46, 47, 48);"
           "    color:rgb(246, 245, 244);"
           "}";
}


QString StyleViewer::getPushButtonScreen()
{
    return "QPushButton{"
           "    border: 2px solid rgb(0, 0, 5);"
           "    border-radius:10px;"
           "    padding:6px;"
           "    background-color:rgb(217, 235, 188);"
           "    image:url(:/scrinsh2.svg);"
           "}"
            "QPushButton::pressed{"
            "    border: 2px solid rgb(0, 0, 5);"
            "    border-radius:10px;"
            "    padding:8px;"
            "    background-color:rgb(217, 235, 188);"
            "    image:url(:/scrinsh2.svg);"
            "}"
            "QPushButton::hover{"
           "    border: 3px solid rgb(0, 0, 5);"
           "    border-radius:10px;"
           "    padding:7px;"
           "    background-color:rgb(217, 235, 188);"
           "}";
}

QString StyleViewer::getPushButtonOpenFile()
{
     return "QPushButton{"
           "    border: 1px solid rgb(46, 47, 48);;"
           "    border-radius:10px;"
           "    padding:0px;"
           "    background-color:rgb(84, 85, 86);"
            "    image: url(:/open_directory.svg);"
           "}"
           "QPushButton::hover{"
           "    border: 1px solid rgb(46, 47, 48);"
           "    border-radius:10px;"
           "    padding:1px;"
           "    background-color:rgb(75, 77, 79);"
           "    image: url(:/open_directory.svg);"
           "}";
}

QString StyleViewer::getPushButtonRebootSettings()
{
     return "QToolButton{"
            "    border: 1px solid rgb(46, 47, 48);;"
            "    border-radius:3px;"
            "    padding:1px;"
            "    background-color:rgb(84, 85, 86);"
            "    image: url(:/reset_settings.svg);"
           "}"
           "QToolButton::hover{"
           "    border: 1px solid rgb(46, 47, 48);;"
           "    border-radius:3px;"
           "    padding:1px;"
           "    background-color:rgb(75, 77, 79);"
           "    image: url(:/reset_settings.svg);"
           "}";
}

QString StyleViewer::getPushButtonGif()
{
    return "QPushButton{"
           "    border: 2px solid rgb(0, 0, 5);"
           "    border-radius:10px;"
           "    padding:6px;"
           "    background-color:rgb(217, 235, 188);"
           "    image:url(:/gif.svg);"
           "}"
           "QPushButton::pressed{"
            "    border: 2px solid rgb(0, 0, 5);"
            "    border-radius:10px;"
            "    padding:8px;"
            "    background-color:rgb(217, 235, 188);"
            "    image:url(:/gif.svg);"
           "}"
            "QPushButton::hover{"
            "    border: 3px solid rgb(0, 0, 5);"
            "    border-radius:10px;"
            "    padding:7px;"
            "    background-color:rgb(217, 235, 188);"
            "    image:url(:/gif.svg);"
            "}";
}

QString StyleViewer::getQTabWidgetStart()
{
    return " QTabWidget {"
           "    border-radius: 26px;"
           "    background-color: rgb(41, 42, 43);"
           "    color:rgb(246, 245, 244);"
           "}";
    }

QString StyleViewer::getRadioButtonInfo()
{
    return " QRadioButton {"
           "    color:rgb(246, 245, 244);"
           "}";
}

QString StyleViewer::getQLabelInfo()
{
    return " QLabel {"
           "    color:rgb(246, 245, 244);"
           "}";
}

QString StyleViewer::getQLabelModelText()
{
    return " QLabel {"
           "    color:rgb(246, 245, 244);"
           "}";
}

QString StyleViewer::getQLabelModelInfo()
{
    return " QLabel {"
           "    color:rgb(217, 235, 188);"
           "}";
}

QString StyleViewer::getQLabelPathFile()
{
    return " QLabel {"
           "    background-color:rgb(233, 213, 5);"
           "    color: white;"
           "}";
}

