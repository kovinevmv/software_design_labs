#include "shapescene.h"
#include "square.h"
#include "sinwave.h"
#include "text.h"
#include "squarewithtext.h"

#include <QThread>
#include <QMouseEvent>
#include <QGraphicsSceneEvent>
#include <QTextStream>
#include <QInputDialog>
#include <QMessageBox>

#include <exception>

ShapeScene::ShapeScene(QObject *parent)
    : QGraphicsScene(parent) {
    setItemIndexMethod(QGraphicsScene::NoIndex);
    m_delete_later.reserve(1000);

    m_animation = new QPropertyAnimation(this, "scale");
    m_animation->setDuration(800);
    m_animation->setStartValue(0);
    m_animation->setEndValue(1);

    m_ampl = 100;
    m_freq = 10.0 / 200;

    connect(m_animation, &QPropertyAnimation::finished, this, &ShapeScene::animation_frame_finished);
}

ShapeScene::~ShapeScene() {
    for (auto it = m_figures.begin(); it != m_figures.end(); it++) {
        if (*it) {
            delete  *it;
        }
    }

    for (Shape* item : m_delete_later) {
        if (item) {
            delete item;
        }
    }
}

void ShapeScene::set_shape_type(ShapeType new_shape_type) {
    m_shape_type = new_shape_type;
}

ShapeType ShapeScene::get_shape_type() const {
    return m_shape_type;
}

void ShapeScene::set_create_color(QColor new_create_color) {
    m_create_color = new_create_color;
}

QColor ShapeScene::get_create_color() const {
    return m_create_color;
}

int ShapeScene::get_create_size() const {
    return m_create_size;
}

void ShapeScene::set_create_size(int new_create_size) {
    m_create_size = new_create_size;
}

const ListSet<Shape *> &ShapeScene::get_figures() const {
    return m_figures;
}

void ShapeScene::clear_scene() {
    this->clear();

    for (Shape* item : m_delete_later) {
        if (item) {
            delete item;
        }
    }

    m_figures.clear();
    m_delete_later.clear();
}


void ShapeScene::set_sin_amplitude(double amplitude){
    m_ampl = amplitude;
}

void ShapeScene::set_sin_freq(double freq){
    m_freq = freq;
}


void ShapeScene::serialize(QDataStream &stream) {
    stream << (int)m_figures.size(); // number of figures

    for (auto it = m_figures.begin(); it != m_figures.end(); it++) {
        stream << *it;
    }
}

void ShapeScene::deserialize(QDataStream &stream) {
    int figures_num;
    stream >> figures_num;

    if (figures_num > 0) {
        clear_scene();
    } else {
        return;
    }

    for (int i = 0; i < figures_num; i++) {
        QGraphicsItem* figure = Shape::load_figure(stream);

        if (figure) {
            addItem(figure);
            m_figures.insert(dynamic_cast<Shape*>(figure));
        }
    }
}

void ShapeScene::iterate_container() {
    m_cur_animating_object = m_figures.begin();

    if (m_cur_animating_object != m_figures.end()) {
        m_animation->setTargetObject(*m_cur_animating_object);
        m_animation->start();
    } else {
        emit animation_on_scene_end();
        return;
    }
}

void ShapeScene::animation_frame_finished() {
    m_cur_animating_object++;

    if (m_cur_animating_object != m_figures.end()) {
        m_animation->setTargetObject(*m_cur_animating_object);
        m_animation->start();
    } else {
        emit animation_on_scene_end();
    }
}

void ShapeScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    auto item = this->itemAt(event->scenePos(), QTransform::fromScale(1, 1));

    if (item) {
        if (event->button() == Qt::RightButton) {
            QMessageBox msgBox;
            msgBox.setText("Удаление фигуры");
            msgBox.setInformativeText("Вы хотите удалить фигуру?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.setDefaultButton(QMessageBox::Ok);
            int res = msgBox.exec();
            if (res == QMessageBox::Ok){


                try {
                    this->removeItem(item);

                    auto shape_item = dynamic_cast<Shape*>(item);
                    m_delete_later << shape_item;
                    for (Shape* item : m_delete_later) {
                        if (item) {
                            try {
                                delete item;

                            } catch (...) {

                            }
                        }
                    }
                    m_delete_later.clear();
                    m_figures.erase(m_figures.find(item));

                } catch (...) {
                }
            }
        }
    } else {
        if (event->button() == Qt::LeftButton) {
            QString text;

            switch (m_shape_type) {

                case ShapeType::Square:

                    item = new Square(m_create_color, m_create_size, m_ampl, m_freq);
                    break;

                case ShapeType::SinWave:
                    item = new SinWave(m_create_color, m_create_size, QPointF(-1, 0), QPointF(1, 0), m_ampl, m_freq);
                    break;

                case ShapeType::Text:

                    text = QInputDialog::getText(dynamic_cast<QWidget*>(this->parent()),
                                                      "Текст в фигуре", "Текст");

                    if (text.isEmpty()) {
                        return;
                    } else {
                        item = new Text(m_create_color, m_create_size, text);
                    }

                    break;
                case ShapeType::SquareWithText:

                    auto text = QInputDialog::getText(dynamic_cast<QWidget*>(this->parent()),
                                                                  "Текст в фигуре", "Текст");

                    if (text.isEmpty()) {
                        return;
                    } else {
                        item = new SquareWithText(m_create_color, m_create_size, text, m_ampl, m_freq);
                    }

                    break;
            }

            item->setPos(event->scenePos());

            this->addItem(item);

            m_figures.insert(dynamic_cast<Shape*>(item));
        }
    }
}
