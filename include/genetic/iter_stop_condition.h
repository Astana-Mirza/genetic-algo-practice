#ifndef ITER_STOP_CONDITION_H
#define ITER_STOP_CONDITION_H

#include <cstddef>
#include <abstract/istop_condition.h>

class IterStopCondition : public IStopCondition
{
public:
    //! @brief Конструктор, принимающий количество итераций.
    //! @param iter_count необходимое количество итераций.
    IterStopCondition(size_t iter_count);

    //! @brief Проверка условия остановки алгоритма.
    //! @param packer объект алгоритма, решающего задачу упаковки.
    bool is_stop(const Packer &packer) const override;

private:
    size_t iter_count_;     //! необходимое количество итераций алгоритма.
};

#endif // #ifndef ITER_STOP_CONDITION_H
