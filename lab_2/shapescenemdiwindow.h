#ifndef SHAPESCENEMDIWINDOW_H
#define SHAPESCENEMDIWINDOW_H

#include "shapescene.h"
#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class ShapeSceneMDIWindow;
}

class ShapeSceneMDIWindow : public QWidget
{
    Q_OBJECT

    friend class MainWindow;

public:
    explicit ShapeSceneMDIWindow(QWidget *parent = nullptr);
    ~ShapeSceneMDIWindow();

private:
    Ui::ShapeSceneMDIWindow *ui;
    ShapeScene* shape_scene;
};

#endif // SHAPESCENEMDIWINDOW_H
