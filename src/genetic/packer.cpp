#include "genetic/packer.h"
#include "genetic/separator_crossover.h"
#include "genetic/order_crossover.h"
#include "genetic/order_mutator.h"

#include <random>
#include <algorithm>

Packer::Packer(
	const std::vector<std::pair<int, int>>& rectangles,
	int tape_width,
	IParentSelector* parent_selector,
	int population_size,
	float crossover1_probability,
	float crossover2_probability,
	float mutation_probability
):
	rectangles_{rectangles},
	tape_width_{tape_width},
    population_size_{population_size},
    probabilities_{
        crossover1_probability,
        crossover2_probability,
        mutation_probability
    },
    parent_selector_{parent_selector}
{
	// Создание операторов кроссовера и мутации
	crossover1_operator_ = new SeparatorCrossover;
	crossover2_operator_ = new OrderCrossover;
	mutation_operator_ = new OrderMutator(rectangles, tape_width);
	// Генерация начальной популяции
	init_population();
}


Packer::~Packer()
{
	delete crossover1_operator_;
	delete crossover2_operator_;
	delete mutation_operator_;

	delete parent_selector_;
}


void Packer::init_population()
{
	std::random_device rd;
	std::default_random_engine random_generator(rd());
	std::uniform_int_distribution<> rotation_distribution(0, 1);
	// Формирование начальной популяции
	population_.reserve(population_size_);

	for (int i = 0; i < population_size_; ++i)
	{
		// Инициализируем гены новой особи
		std::vector<Gene> genes;
        for (size_t k = 0; k < rectangles_.size(); ++k)
		{
			// Проходим по всем прямоугольникам из условия
			// Случайным образом определяем, будем ли делать поворот на 90 градусов
			bool rotation = rotation_distribution(random_generator) != 0;
			// Определяем координату x нижнего левого угла прямоугольника на ленте
			int rectangle_width = rotation ? rectangles_.at(k).second : rectangles_.at(k).first;
			std::uniform_int_distribution<> coordinate_distribution(
				0, tape_width_ - rectangle_width
			);
			// Записываем ген
			genes.emplace_back(
				coordinate_distribution(random_generator),
				k,
				rotation
			);
		}
		// Изменяем порядок генов у особи
		std::shuffle(genes.begin(), genes.end(), random_generator);
		// Добавляем особь в популяцию
		population_.emplace_back(genes, rectangles_, tape_width_);
	}
}


void Packer::generate_new_breed()
{
	// Используем кроссинговеры и мутацию, после используем отбор
	std::random_device rd;
	std::default_random_engine random_generator(rd());
	std::uniform_real_distribution<> probability_distribution(0, 1);

	for (int index = 0; index < population_size_; ++index)
	{
		const Individual& parent1 = population_.at(index);
		// Случайный выбор второго родителя (панмиксия)
		const Individual& parent2 = parent_selector_->exec(population_, population_size_);
		// Определение оператора (кроссоверы или мутация)
		float operation = probability_distribution(random_generator);
		if (operation <= probabilities_[0])
		{
			// Кроссинговер 1
			population_.emplace_back(
				crossover1_operator_->exec(parent1, parent2),
				rectangles_,
				tape_width_
			);
		} else if (operation <= probabilities_[0] + probabilities_[1])
		{
			// Кроссинговер 2
			population_.emplace_back(
				crossover2_operator_->exec(parent1, parent2),
				rectangles_,
				tape_width_
			);
		} else if (operation <= probabilities_[0] + probabilities_[1] + probabilities_[2])
		{
			// Мутация
			population_.emplace_back(
				mutation_operator_->exec(parent1),
				rectangles_,
				tape_width_
			);
		}
		// Проверка пригодности решения
		if (!population_.back().is_feasible())
			population_.pop_back(); // Если особь непригодна, удаляем ее
	}
	// Сортируем особи по убыванию фитнесса
	std::sort(
		population_.begin(), population_.end(), 
		[](const Individual& individual1, const Individual& individual2){
			return individual1.get_fitness() > individual2.get_fitness();
		}
	);
	// Оставляем population_size_ особей с наивысшим фитнессом
	population_.resize(population_size_, Individual{{}, {}, 0});
}


#include <iostream>
void Packer::print_population() const
{
	for (int i = 0; i < population_size_; ++i)
		std::cout << "fitness: " << population_.at(i).get_fitness() << std::endl;
	std::cout << std::endl;
}
