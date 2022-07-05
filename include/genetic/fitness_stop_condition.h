#ifndef FITNESS_STOP_CONDITION_H
#define FITNESS_STOP_CONDITION_H

#include <abstract/istop_condition.h>

class FitnessStopCondition : IStopCondition
{
public:
    //! @brief Конструктор, принимающий минимальный искомый фитнес.
    //! @param fitness минимальный искомый фитнес.
    FitnessStopCondition(double fitness);

    //! @brief Проверка условия остановки алгоритма.
    //! @param packer объект алгоритма, решающего задачу упаковки.
    bool is_stop(const Packer &packer) const override;

private:
    double fitness_;     //! минимальный удовлетворительный фитнесс.
};

#endif // #ifndef FITNESS_STOP_CONDITION_H
