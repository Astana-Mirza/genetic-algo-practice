#ifndef ORDER_MUTATOR_H
#define ORDER_MUTATOR_H

#include <vector>
#include <random>

#include "abstract/imutator.h"
#include "gene.h"

class Individual;


/**
 * @brief Оператор мутации с изменением порядка генов
 * @details Данный оператор выбирает случайным образом 
 * 2 различных гена, которые меняет местами. 
 * Также у данных генов с вероятностью 50% может быть изменен флаг поворота (одновременно у обоих).
 * Также с вероятностью 25% может быть изменена координата прямоугольника из первого гена,
 * с вероятностью 25% - координата прямоугольника из второго гена,
 * с вероятностью 25% - координата прямоугольника в обоих генах
 */
class OrderMutator: public IMutator
{
public:
	/**
	 * @brief Конструктор оператора мутации с изменением порядка генов
	 * 
	 * @param rectangles Прямоугольники, размещаемые на ленте
	 * @param tape_width Ширина ленты
	 */
	OrderMutator(
		const std::vector<std::pair<int, int>> rectangles,
		int tape_width
	);
	/**
	 * @brief Метод вызова оператора мутации с изменением порядка генов

	 * @param parent Особь, гены которого мутируют для получения потомка
	 * @return Гены потомка
	 */
	std::vector<Gene> exec(const Individual& parent);
protected:
	/**
	 * @brief Метод генерации новой координаты прямоугольника
	 * @details Генерируется новая координата прямоугольника таким образом, чтобы 
	 * он не выходил за границы ленты
	 * 
	 * @param parent Родительская особь
	 * @param gene_index Индекс гена родительской особи
	 * @param change_rotation Флаг изменения поворота прямоугольника
	 */
	int generate_new_coordinate(
		const Individual& parent,
		int gene_index,
		bool change_rotation
	);

	/**
	 * Прямоугольники для замощения ленты
	 */
	std::vector<std::pair<int, int>> rectangles_;
	/**
	 * Ширина ленты
	 */
	int tape_width_;

	/**
	 * Генератор случайных чисел
	 */
	std::random_device rd_;
	std::default_random_engine random_generator_;
};

#endif
