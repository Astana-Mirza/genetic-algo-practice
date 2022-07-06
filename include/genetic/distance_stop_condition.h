#ifndef DISTANCE_STOP_CONDITION_H
#define DISTANCE_STOP_CONDITION_H

#include <abstract/istop_condition.h>

class DistanceStopCondition : public IStopCondition
{
public:
    //! @brief Конструктор, принимающий максимальную разницу фитнесов.
    //! @param distance максимальная допустимая разница между фитнесами.
    DistanceStopCondition(double distance);

    //! @brief Проверка условия остановки алгоритма.
    //! @param packer объект алгоритма, решающего задачу упаковки.
    bool is_stop(const Packer &packer) const override;

private:
    double distance_;     //! предельно допустимая разница фитнесов.
};

#endif // #ifndef DISTANCE_STOP_CONDITION_H
