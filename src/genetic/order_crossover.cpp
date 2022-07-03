#include "genetic/order_crossover.h"
#include "genetic/individual.h"

#include <random>
#include <map>

std::vector<Gene> OrderCrossover::exec(const Individual& parent1, const Individual& parent2)
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
	// Ассоциативный массив соответствий "ген i у родителя 1" - "ген i у родителя 2"
	std::map<int, int> indeces_map;
	for (int i = position_left; i <= position_right; ++i)
		indeces_map[parent1_genes.at(i).get_index()] = parent2_genes.at(i).get_index();
	// Формируем гены потомка
	for (int i = 0; i < parent1_genes.size(); ++i)
	{
		// Гены с индексами из промежутка [position_left; position_right] 
		// будут копиями генов родителя 1
		if (i >= position_left && i <= position_right)
		{
			genes.emplace_back(
				parent1_genes.at(i).get_coordinate(),
				parent1_genes.at(i).get_index(),
				parent1_genes.at(i).get_rotation()
			);
			continue;
		}
		// Гены не из промежутка будут копиями генов родителя 2
		// Берем индекс прямоугольника из гена родителя 2
		int rectangle_index = parent2_genes.at(i).get_index();
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
		// По индексу прямоугольника находим индекс гена родителя 2, отвечающего за прямоугольник
		int gene_index = 0;
		for (; gene_index < parent2_genes.size(); ++gene_index)
		{
			if (rectangle_index == parent2_genes.at(gene_index).get_index())
				break;
		}
		// Записываем ген потомка
		genes.emplace_back(
			parent2_genes.at(gene_index).get_coordinate(),
			parent2_genes.at(gene_index).get_index(),
			parent2_genes.at(gene_index).get_rotation()
		);
	}

	return genes;
}
