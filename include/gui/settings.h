#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <logger/log.h>

//! @brief Структура всех насторек генетического алгоритма и логирования.
struct Settings
{
    //! @brief Тип выбора родителей для кроссинговера.
    enum class PairSelectionType
    {
        Panmixing,      //! < панмиксия.
        Roulette        //! < метод рулетки.
    };

    //! @brief Тип отбора особей в новую популяцию.
    enum class IndividualSelectionType
    {
        Truncation,     //! < отбор усечением.
        Elite           //! < элитарный отбор.
    };

    //! @brief Критерий остановки алгоритма.
    enum class StopCondition
    {
        Fitness,        //! < остановка по фитнесу.
        StepCount,      //! < остановка по количеству шагов.
        Distance        //! < остановка по разнице фитнесов.
    };

    QString log_file;                                     //! < файл лога.
    double p_mutation                          = 0.04;    //! < вероятность мутации.
    double p_crossover1                        = 0.48;    //! < вероятность кроссинговера 1.
    double p_crossover2                        = 0.48;    //! < вероятность кроссинговера 2.
    double bad_part                            = 0.25;    //! < доля непригодных особей в методе усечения.
    double fitness                             = 0.1;     //! < предельное значение фитнеса для остановки.
    double distance                            = 0.01;    //! < предельная разница в фитнесах для остановки.
    size_t population_size                     = 12;      //! < размер популяции.
    size_t step_count                          = 100;     //! < количество шагов алгоритма.
    PairSelectionType pair_select_type         = PairSelectionType::Panmixing;    //! < тип выбора родителей.
    IndividualSelectionType indiv_select_type  = IndividualSelectionType::Elite;  //! < тип отбора особей в популяцию.
    StopCondition stop_condition               = StopCondition::StepCount;        //! < критерий остановки алгоритма.
    Log::LogLevel log_level                    = Log::Info;                       //! < уровень логирования.
    bool log_to_file                           = false;                           //! < записывать ли логи в файл.
    bool log_to_console                        = false;                           //! < записывать ли логи в консоль.
};

#endif // #ifndef SETTINGS_H
