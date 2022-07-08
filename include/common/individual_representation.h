#ifndef INDIVIDUAL_REPRESENTATION_H
#define INDIVIDUAL_REPRESENTATION_H

#include <vector>
#include <array>

#include "rectangle_representation.h"

/**
 * @brief Класс представления решения
 */
class IndividualRepresentation
{
public:
    /**
     * @brief Добавление информации о прямоугольнике
     * @param index Номер прямоугольника
     * @param x Координата X прямоугольника
     * @param y Координата Y прямоугольника
     * @param rotation Флаг поворота прямоугольника
     */
    void add_rectangle(size_t index, size_t x, size_t y, bool rotation = false);
    /**
     * @brief Получение расположения прямоугольников на ленте
     * @return Расположение прямоугольников
     */
    const std::vector<RectangleRepresentation>& get_configuration() const;
protected:
    /**
     * Расположение прямоугольников
     */
    std::vector<RectangleRepresentation> configutation_;
};

#endif // INDIVIDUAL_REPRESENTATION_H
