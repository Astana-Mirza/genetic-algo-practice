#ifndef ICROSSOVER_H
#define ICROSSOVER_H

#include <vector>

class Individual;
class Gene;

/**
 * @brief Интерфейс оператора кроссовера
 */
class ICrossover
{
public:
	/**
	 * @brief Генерация генов нового потомка
	 * @details Метод генерирует гены нового потомка на основе генов его родителей
	 * 
	 * @param parent1 Первый родитель потомка
	 * @param parent2 Второй родитель потомка
	 * 
	 * @return Гены потомка
	 */
	virtual std::vector<Gene> exec(const Individual& parent1, const Individual& parent2) = 0;
};

#endif
