#include "shapeview.h"

#include "shapescenemdiwindow.h"
#include "ui_shapescenemdiwindow.h"

ShapeSceneMDIWindow::ShapeSceneMDIWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShapeSceneMDIWindow)
{
    ui->setupUi(this);
    shape_scene = new ShapeScene(this);
    ui->figures_view->setScene(shape_scene);
}

ShapeSceneMDIWindow::~ShapeSceneMDIWindow()
{
    delete ui;
}
