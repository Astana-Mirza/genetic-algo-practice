#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>

//! @brief Структура всех насторек генетического алгоритма и логирования.
struct Settings
{
    //! @brief Тип выбора родителей для кроссинговера.
    enum class PairSelectionType
    {
        Panmixing,
        Roulette
    };

    //! @brief Тип отбора особей в новую популяцию.
    enum class IndividualSelectionType
    {
        Truncation,
        Elite
    };

    //! @brief Критерий остановки алгоритма.
    enum class StopCondition
    {
        Fitness,
        StepCount,
        Distance
    };

    QString log_file;
    double p_mutation                          = 0.04;
    double p_crossover1                        = 0.48;
    double p_crossover2                        = 0.48;
    double bad_part                            = 0.25;
    double fitness                             = 0.1;
    double distance                            = 0.01;
    size_t population_size                     = 12;
    size_t step_count                          = 100;
    PairSelectionType pair_select_type         = PairSelectionType::Panmixing;
    IndividualSelectionType indiv_select_type  = IndividualSelectionType::Elite;
    StopCondition stop_condition               = StopCondition::StepCount;
    // Log::LogLevel log_level                    = Log::Info;
    bool log_to_file                           = false;
    bool log_to_console                        = false;
};

#endif // #ifndef SETTINGS_H
