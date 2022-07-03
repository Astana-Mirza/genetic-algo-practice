#include "genetic/order_mutator.h"
#include "genetic/individual.h"

#include <random>


OrderMutator::OrderMutator(
	const std::vector<std::pair<int, int>> rectangles,
	int tape_width
):
	rectangles_{rectangles},
	tape_width_{tape_width},
	random_generator_{rd_()}
{
}


std::vector<Gene> OrderMutator::exec(const Individual& parent)
{
	// Гены потомка
	std::vector<Gene> genes;

	std::uniform_int_distribution<> positions_distribution(0, parent.get_genes().size() - 1);
	std::uniform_int_distribution<> rotation_distribution(0, 1);
	std::uniform_int_distribution<> coordinate_distribution(0, 3);

	// Генерация двух различных индексов генов
	int position1 = positions_distribution(random_generator_);
	int position2 = positions_distribution(random_generator_);
	while (position1 == position2)
		position2 = positions_distribution(random_generator_);
	// Будет ли измененен поворот в генах
	bool change_rotation = rotation_distribution(random_generator_) != 0;

	// Координаты прямоугольников из генов с выбранными генами
	int item1_coordinate = parent.get_genes().at(position1).get_coordinate();
	int item2_coordinate = parent.get_genes().at(position2).get_coordinate();

	switch (coordinate_distribution(random_generator_))
	{
		case 1:
			// Случайное изменение координаты в гене 1
			item1_coordinate = generate_new_coordinate(parent, position1, change_rotation);
			break;
		case 2:
			// Случайное изменение координаты в гене 2
			item2_coordinate = generate_new_coordinate(parent, position2, change_rotation);
			break;
		case 3:
			// Случайное изменение координаты в обоих генах
			item1_coordinate = generate_new_coordinate(parent, position1, change_rotation);
			item2_coordinate = generate_new_coordinate(parent, position2, change_rotation);
			break;
	}
	
	// Проход по всем генам родителя
	for (int i = 0; i < parent.get_genes().size(); ++i)
	{
		// Меняем порядок генов с выбранными индексами, записываем изменения по этим генам
		// Гены с другими индексами не изменяем и копируем от родителя
		if (i == position1)
		{
			genes.emplace_back(
				item2_coordinate,
				parent.get_genes().at(position2).get_index(),
				change_rotation ? 
					!parent.get_genes().at(position2).get_rotation() :
					parent.get_genes().at(position2).get_rotation()
			);
		} else if (i == position2)
		{
			genes.emplace_back(
				item1_coordinate,
				parent.get_genes().at(position1).get_index(),
				change_rotation ? 
					!parent.get_genes().at(position1).get_rotation() :
					parent.get_genes().at(position1).get_rotation()
			);
		} else
		{
			genes.emplace_back(
				parent.get_genes().at(i).get_coordinate(),
				parent.get_genes().at(i).get_index(),
				parent.get_genes().at(i).get_rotation()
			);
		}
	}
	return genes;
}


int OrderMutator::generate_new_coordinate(
	const Individual& parent,
	int gene_index,
	bool change_rotation
)
{
	const Gene& gene = parent.get_gene(gene_index);

	int rectangle_index = gene.get_index();
	bool condition = gene.get_rotation();
	if (change_rotation)
		condition = !gene.get_rotation();
	int rectangle_width = condition ?
		rectangles_.at(rectangle_index).second :
		rectangles_.at(rectangle_index).first;
	std::uniform_int_distribution<> item_distribution(
		0, tape_width_ - rectangle_width
	);

	return item_distribution(random_generator_);
}
