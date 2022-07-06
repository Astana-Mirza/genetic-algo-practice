#ifndef PANMIXING_PARENT_SELECTOR
#define PANMIXING_PARENT_SELECTOR

#include <random>

#include "abstract/iparent_selector.h"

/**
 * @brief Оператор выбора родителя методом панмиксии
 * @details Случайным образом выбирается родитель, 
 * все варианты выбора равновероятны
 */
class PanmixingParentSelector: public IParentSelector
{
public:
    /**
     * @brief Конструктор оператора выбора родителя методом панмиксии
     */
    PanmixingParentSelector();

    /**
     * @brief Выбор родительской особи методом панмиксии
     * 
     * @param population Текушая популяция
     * @param population_size Размер популяции
     * 
     * @return Родительская особь
     */
    size_t exec(
        const std::vector<Individual>& population,
        size_t population_size
    );
protected:
    /**
     * Генератор случайных чисел
     */
    std::random_device rd_;
    std::default_random_engine random_generator_;
};

#endif
