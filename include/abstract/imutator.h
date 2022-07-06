#ifndef IMUTATOR_H
#define IMUTATOR_H

#include <vector>

class Individual;
class Gene;

/**
 * @brief Интерфейс оператора мутации
 */
class IMutator
{
public:
    /**
     * @brief Генерация генов нового потомка
     * @details Метод генерирует гены нового потомка путем случайной мутации генов родителя
     * 
     * @param parent Родительская особь
     * 
     * @return Гены потомка
     */
    virtual std::vector<Gene> exec(const Individual& parent) = 0;
    virtual ~IMutator() = default;
};

#endif
