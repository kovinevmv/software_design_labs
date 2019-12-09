#ifndef SHAPETYPES_H
#define SHAPETYPES_H

#include <QDataStream>

enum class ShapeType {
    Square = 0,
    SinWave,
    Text,
    SquareWithText
};

inline QDataStream& operator<<(QDataStream& stream, const ShapeType& type) {
    stream << static_cast<unsigned>(type);
    return stream;
}

inline QDataStream& operator>>(QDataStream& stream, ShapeType& type) {
    unsigned value;
    stream >> value;
    type = static_cast<ShapeType>(value);
    return stream;
}

#endif // SHAPETYPES_H
