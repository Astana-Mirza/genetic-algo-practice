#ifndef ISELECTOR_H
#define ISELECTOR_H

#include <vector>

class Individual;

/**
 * @brief Оператор отбора особей в новом поколении
 */
class ISelector
{
public:
    /**
     * @brief Отбор особей в новое поколение
     * @details Метод выбирает заданное количество особей в новое поколение
     * 
     * @param population Популяция, из которой будет происходить выбор особей
     * @param population_size Желаемый размер популяции
     * 
     * @return Новое поколение
     */
    virtual std::vector<Individual> exec(
        const std::vector<Individual>& population,
        size_t population_size
    ) = 0;
    virtual ~ISelector() = default;
};

#endif
