#ifndef RESULT_H
#define RESULT_H

#include <vector>
#include <array>

//! @brief Результат одного шага генетического алгоритма.
struct Result
{
    //! @brief состояние алгоритма, пройденное на этом шаге.
    enum class State
    {
        Start,                 //! < стартовое состояние.
        InitPopulation,        //! < создание первой популяции.
        IndividualGeneration,  //! < создание новых особей (мутация или кроссинговер).
        Selection,             //! < отбор особей в новую популяцию.
        End                    //! < конец работы алгоритма.
    };
    State state;                                            //! < пройденное состояние алгоритма.
    std::vector<std::array<size_t, 3>> changed_individuals; //! < список добавленных особей в виде
                                                            //! троек индексов (родитель1, родитель2, особь)
};

#endif // #ifndef RESULT_H
