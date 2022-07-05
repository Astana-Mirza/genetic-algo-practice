#ifndef RECTANGLE_REPRESENTATION_H
#define RECTANGLE_REPRESENTATION_H

#include <cstddef>

/**
 * @brief Класс представления прямоугольника
 */
class RectangleRepresentation
{
public:
    /**
     * @brief Конструктор класса представления прямоугольника
     * @param index Номер прямоугольника
     * @param x Координата X расположения прямоугольника
     * @param y Координата Y расположения прямоугольника
     * @param rotation Флаг поворота прямоугольника
     */
    RectangleRepresentation(
        size_t index,
        size_t x,
        size_t y,
        bool rotation = false
    );

    /**
     * @brief Получение номера прямоугольника
     * @return Номер прямоугольника
     */
    size_t get_index() const;
    /**
     * @brief Получение координаты X прямоугольника
     * @return Координата X
     */
    size_t get_x() const;
    /**
     * @brief Получение координаты Y прямоугольника
     * @return Координата Y
     */
    size_t get_y() const;
    /**
     * @brief Получение флага поворота прямоугольника
     * @return Флаг поворота
     */
    bool get_rotation() const;
protected:
    size_t index_;
    size_t x_;
    size_t y_;
    bool rotation_;
};

#endif // RECTANGLE_REPRESENTATION_H
