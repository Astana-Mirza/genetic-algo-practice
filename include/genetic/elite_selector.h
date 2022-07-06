#ifndef ELITE_SELECTOR_H
#define ELITE_SELECTOR_H

#include "abstract/iselector.h"

/**
 * @brief Оператор отбора особей в новом поколении элитарным методом
 * @details Отбирает N лучших (по значению фитнеса особей) 
 * и возвращает их как новое поколение
 */
class EliteSelector: public ISelector
{
public:
    /**
     * @brief Отбор особей в новое поколение элитарным методом
     * @details Метод выбирает заданное количество особей в новое поколение
     * 
     * @param population Популяция, из которой будет происходить выбор особей
     * @param population_size Желаемый размер популяции
     * 
     * @return Новое поколение
     */
    std::vector<Individual> exec(
        const std::vector<Individual>& population, 
        size_t population_size
    );
};

#endif
