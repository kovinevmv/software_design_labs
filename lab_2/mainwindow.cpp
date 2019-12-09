#include "shapescenemdiwindow.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMdiSubWindow>
#include <QMdiArea>
#include <QInputDialog>
#include <QColorDialog>
#include <QColor>
#include <QFileDialog>
#include <QGraphicsView>
#include <QMessageBox>
#include <QDataStream>
#include <QSplitter>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      cur_color(Qt::red),
      cur_shape_type(ShapeType::Square) {


    ui->setupUi(this);
    cur_size = ui->figure_size_slider->value();
    ui->enable_square->setChecked(true);

    auto colcode = cur_color.name();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_figure_size_slider_valueChanged(int value) {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_create_size(value);
    }
}


void MainWindow::on_sin_ampl_valueChanged(int value) {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_sin_amplitude(value / 200.0);
    }
}

void MainWindow::on_sin_freq_valueChanged(int value) {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_sin_freq(value);
    }
}

void MainWindow::on_pushButton_clicked() {
    // change to all scenes

    auto new_color = QColorDialog::getColor(Qt::green, this, "Выбрать цвет фигуры");

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_create_color(new_color);
    }

    auto colcode = new_color.name();
}

void MainWindow::on_enable_SinWave_clicked() {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_shape_type(ShapeType::SinWave);
    }
}

void MainWindow::on_enable_square_clicked() {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_shape_type(ShapeType::Square);
    }
}

void MainWindow::on_enable_text_clicked() {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_shape_type(ShapeType::Text);
    }
}

void MainWindow::on_enable_text_with_square_clicked() {
    // change to all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->set_shape_type(ShapeType::SquareWithText);
    }
}

void MainWindow::on_exit_triggered() {
    QApplication::exit();
}

void MainWindow::on_save_to_file_triggered() {
    // apply to current active scene

    auto cur_scene = get_cur_scene();
    if (!cur_scene) {
        return;
    }

    auto file_name = QFileDialog::getSaveFileName(this, "Сохранить в файл", QString(), "Text File(*.data)");

    if (file_name.isEmpty()) {
        return;
    }

    QFile file(file_name);

    if (file.open(QIODevice::WriteOnly)) {
        QDataStream output(&file);
        cur_scene->serialize(output);
    }

    file.close();
}

void MainWindow::on_load_from_file_triggered() {
    // apply to current active scene

    auto cur_scene = get_cur_scene();
    if (!cur_scene) {
        return;
    }

    auto file_name = QFileDialog::getOpenFileName(this, "Открыть из файла", QString(), "*");

    if (file_name.isEmpty()) {
        return;
    }

    QFile file(file_name);

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream input(&file);
        cur_scene->deserialize(input);
    }

    file.close();
}

void MainWindow::on_clear_triggered() {
    auto cur_shape_scene = get_cur_scene();
    if (cur_shape_scene) {
        cur_shape_scene->clear_scene();
    }
}

void MainWindow::on_action_triggered() {
    auto new_window = new ShapeSceneMDIWindow(ui->mdi_area);

    connect(new_window->shape_scene, &ShapeScene::animation_on_scene_end,
            this, &MainWindow::on_scene_animation_end);

    new_window->shape_scene->set_shape_type(cur_shape_type);
    new_window->shape_scene->set_create_size(cur_size);
    new_window->shape_scene->set_create_color(cur_color);

    auto new_shape_window = ui->mdi_area->addSubWindow(new_window);
    new_shape_window->setWindowTitle(QString::number(num_scenes++) + ": Окно");

    new_window->show();
}

ShapeScene *MainWindow::get_cur_scene() {
    auto current_subwindow = ui->mdi_area->currentSubWindow();
    if (current_subwindow) {
        auto cur_scene_as_widget = current_subwindow->widget();
        auto cur_scene_window = dynamic_cast<ShapeSceneMDIWindow*>(cur_scene_as_widget);

        return cur_scene_window->shape_scene;
    } else {
        return nullptr;
    }
}

QList<ShapeScene *> MainWindow::get_cur_scenes() {
    auto scenes = ui->mdi_area->subWindowList();
    QList<ShapeScene*> result;

    for (auto scene : scenes) {
        auto scene_as_widget = scene->widget();
        auto shape_scene_mdi_window = dynamic_cast<ShapeSceneMDIWindow*>(scene_as_widget);

        result.push_back(shape_scene_mdi_window->shape_scene);
    }

    return result;
}

void MainWindow::on_scene_animation_end() {
    ui->menuBar->setEnabled(true);
    ui->mdi_area->setEnabled(true);
    //ui->figures_type_select->setEnabled(true);
}

void MainWindow::on_action_2_triggered() {
    // clear all scenes

    auto all_scenes = get_cur_scenes();
    for (auto scene : all_scenes) {
        scene->clear_scene();
    }
}

void MainWindow::on_action_3_triggered() {
    // iterate over container
    // with animation

    auto cur_shape_scene = get_cur_scene();
    if (cur_shape_scene) {
        ui->menuBar->setEnabled(false);
        ui->mdi_area->setEnabled(false);
        //ui->figures_type_select->setEnabled(false);

        cur_shape_scene->iterate_container();
    }
}
