#ifndef ISTOP_CONDITION_H
#define ISTOP_CONDITION_H

class Packer;

//! @brief Интерфейс условия остановки генетического алгоритма.
class IStopCondition
{
public:
    //! @brief Проверка условия остановки алгоритма.
    //! @param packer объект алгоритма, решающего задачу упаковки.
    virtual bool is_stop(const Packer& packer) const = 0;

    virtual ~IStopCondition() = default;
};

#endif // #ifndef ISTOP_CONDITION_H
