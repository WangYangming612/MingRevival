#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QMainWindows.h"

class QMainWindows : public QMainWindow
{
    Q_OBJECT

public:
    QMainWindows(QWidget *parent = nullptr);
    ~QMainWindows();

private:
    Ui::QMainWindowsClass ui;
};

