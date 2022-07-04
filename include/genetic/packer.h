#ifndef PACKER_H
#define PACKER_H

#include <vector>

#include "individual.h"
#include "abstract/icrossover.h"
#include "abstract/imutator.h"
#include "abstract/iparent_selector.h"

/**
 * @brief Класс, отвечающий за решение задачи раскроя
 * с помощью генетического алгоритма
 */
class Packer
{
public:
	/**
	 * @brief Конструктор класса генетического алгоритма
	 * @details На основе переданных условий задачи (конфигурации прямоугольников и ширина ленты)
	 * инициализируется генетический алгоритм для рещения задачи. Также могут быть заданы параметры алгоритма
	 * 
	 * @param rectangles Конфигурации прямоугольников, которые необходимо разместить на ленте
	 * @param tape_width Ширина замощаемой ленты
	 * @param parent_selector Оператор выбора родителя
	 * @param population_size Размер популяции в генетическом алгоритме
	 * @param crossover1_probability Вероятность использования первого оператора кроссовера
	 * @param crossover2_probability Вероятность использования второго оператора кроссовера
	 * @param mutation_probability Вероятность использования оператора мутации
	 */
	Packer(
		const std::vector<std::pair<int, int>>& rectangles,
		int tape_width,
		IParentSelector* parent_selector,
		int population_size = 20,
		float crossover1_probability = 0.45,
		float crossover2_probability = 0.45,
		float mutation_probability = 0.1
	);
	~Packer();

	/**
	 * @brief Метод для отладки текущей популяции
	 * @details Выводится фитнес всех особей в текущей популяции
	 */
	void print_population() const;

	/**
	 * @brief Метод генерации нового поколения
	 */
	void generate_new_breed();
protected:
	/**
	 * @brief Метод генерации начальной популяции
	 */
	void init_population();

	/**
	 * Прямоугольники для замощения ленты
	 */
	std::vector<std::pair<int, int>> rectangles_;
	/**
	 * Ширина ленты
	 */
	int tape_width_;
	/**
	 * Размер популяции
	 */
	int population_size_;
	/**
	 * Текущая популяция
	 */
	std::vector<Individual> population_;

	/**
	 * Вероятности выбора операторов во время генерации нового поколения
	 */
	float probabilities_[3];

	/**
	 * Указатели на операторы кроссовера и мутации
	 */
	ICrossover* crossover1_operator_;
	ICrossover* crossover2_operator_;
	IMutator* mutation_operator_;
	/**
	 * Указатель на оператор выбора родителя
	 */
	IParentSelector* parent_selector_;
};

#endif
