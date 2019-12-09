#ifndef SHAPESCENE_H
#define SHAPESCENE_H

#include "shape.h"
#include "shapetypes.h"
#include "listset.hpp"

#include <QGraphicsScene>
#include <QList>
#include <QDataStream>
#include <QPropertyAnimation>

class ShapeScene : public QGraphicsScene
{

Q_OBJECT

public:

    ShapeScene(QObject* parent = nullptr);
    ~ShapeScene() override;

    void set_shape_type(ShapeType new_shape_type);
    ShapeType get_shape_type() const;

    void set_create_color(QColor new_create_color);
    QColor get_create_color() const;

    int get_create_size() const;
    void set_create_size(int new_create_size);

    const ListSet<Shape*>& get_figures() const;

    void clear_scene();

    void serialize(QDataStream& stream);
    void deserialize(QDataStream& stream);

    void iterate_container();

    void set_sin_amplitude(double amplitude);
    void set_sin_freq(double freq);

signals:

    void animation_on_scene_end();

private:

    QColor m_create_color;
    int m_create_size;

    double m_ampl;
    double m_freq;

    ShapeType m_shape_type;

    ListSet<Shape*> m_figures;
    QList<Shape*> m_delete_later;

    ListSet<Shape*>::iterator m_cur_animating_object;
    QPropertyAnimation* m_animation;

private slots:

    void animation_frame_finished();

protected:

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // SHAPESCENE_H
