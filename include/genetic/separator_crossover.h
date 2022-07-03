#ifndef SEPARATOR_CROSSOVER_H
#define SEPARATOR_CROSSOVER_H

#include "abstract/icrossover.h"

/**
 * @brief Оператор кроссовера с изменением индексов прямоугольников
 * @details Данный оператор кроссовера формирует отрезок 
 * 0 <= l <= r <= количество генов, после чего гены потомка с индексами из промежутка копируются у родителя 2,
 * гены с индексами получают координату и флаг поворота от родителя 2, индекс прямоугольника - от родителя 1 (с разрешением конфликтов)
 * Разрешение конфликтов:
 * В процессе копирования генов родителя 1 (следует после копирования генов родителя 2)
 * могут попасться гены, отвечающие за прямоугольники, гены с информацией о которых были скопированы у родителя 2.
 * В таком случае, если ген, отвечающий за данный прямоугольник, у родителя 2 находится под индексом k, то
 * берется ген родителя 1 с индексом k. Так повторяется до тех пор, пока конфликт не исчезнет
 */
class SeparatorCrossover: public ICrossover
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
	std::vector<Gene> exec(const Individual& parent1, const Individual& parent2);
};

#endif
