#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "shapescene.h"
#include "shapescenemdiwindow.h"

#include <QMainWindow>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_figure_size_slider_valueChanged(int value);

    void on_sin_ampl_valueChanged(int value);

    void on_sin_freq_valueChanged(int value);

    void on_pushButton_clicked();

    void on_enable_SinWave_clicked();

    void on_enable_square_clicked();

    void on_enable_text_clicked();

    void on_enable_text_with_square_clicked();

    void on_exit_triggered();

    void on_save_to_file_triggered();

    void on_load_from_file_triggered();

    void on_clear_triggered();

    void on_action_triggered();

    void on_action_2_triggered();

    void on_action_3_triggered();

private:

    ShapeScene* get_cur_scene();
    QList<ShapeScene*> get_cur_scenes();

    Ui::MainWindow *ui;

    QColor cur_color;
    ShapeType cur_shape_type;
    int cur_size;
    int num_scenes = 1;

private slots:

    void on_scene_animation_end();
};
#endif // MAINWINDOW_H
