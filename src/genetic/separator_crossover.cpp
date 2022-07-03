#include "genetic/separator_crossover.h"
#include "genetic/individual.h"

#include <random>
#include <map>

std::vector<Gene> SeparatorCrossover::operator() (const Individual& parent1, const Individual& parent2)
{
	// Получаем гены родителей
	const std::vector<Gene>& parent1_genes = parent1.get_genes();
	const std::vector<Gene>& parent2_genes = parent2.get_genes();
	// Создаем гены потомка
	std::vector<Gene> genes;
	genes.reserve(parent1_genes.size());

	std::random_device rd;
	std::default_random_engine random_generator(rd());
	std::uniform_int_distribution<> positions_distribution(0, parent1_genes.size() - 1);
	// Случайным образом выбираем отрезок 0 <= position_left <= position_right <= parent1_genes.size()-1
	int position_left = positions_distribution(random_generator);
	int position_right = positions_distribution(random_generator);
	// Если position_right < position_left, меняем их местами
	if (position_right < position_left)
		std::swap(position_left, position_right);
	// Ассоциативный массив соответствий "ген i у родителя 2" - "ген i у родителя 1"
	std::map<int, int> indeces_map;
	for (int i = position_left; i <= position_right; ++i)
		indeces_map[parent2_genes.at(i).get_index()] = parent1_genes.at(i).get_index();
	// Формируем гены потомка
	for (int i = 0; i < parent1_genes.size(); ++i)
	{
		// В гены с индексами из промежутка [position_left; position_right] 
		// записываем индексы из генов родителя 2, координату и поворот не изменяем
		if (i >= position_left && i <= position_right)
		{
			genes.emplace_back(
				parent2_genes.at(i).get_coordinate(),
				parent2_genes.at(i).get_index(),
				parent2_genes.at(i).get_rotation()
			);
			continue;
		}
		// В гены не из промежутка записываем индексы из генов родителя 1
		int rectangle_index = parent1_genes.at(i).get_index();
		bool has_collision = true;
		// Если данный индекс уже встречается у потомка, то используем
		// ассоциативный массив indeces_map для нахождения индекса, которого еще нет у потомка
		while (has_collision)
		{
			auto collision_item = indeces_map.find(rectangle_index);
			if (collision_item != indeces_map.end())
			{
				rectangle_index = collision_item->second;
			} else
			{
				has_collision = false;
			}
		}
		// Записываем ген потомка
		genes.emplace_back(
			parent2_genes.at(i).get_coordinate(),
			rectangle_index,
			parent2_genes.at(i).get_rotation()
		);
	}

	return genes;
}
