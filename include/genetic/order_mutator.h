#ifndef ORDER_MUTATOR_H
#define ORDER_MUTATOR_H

#include <vector>
#include <random>

#include "abstract/imutator.h"
#include "gene.h"

class Individual;

class OrderMutator: public IMutator
{
public:
	OrderMutator(
		const std::vector<std::pair<int, int>> rectangles,
		int tape_width
	);
	std::vector<Gene> operator() (const Individual& parent);
protected:
	int generate_new_coordinate(
		const Individual& parent,
		int gene_index
	);

	std::vector<std::pair<int, int>> rectangles_;
	int tape_width_;

	std::random_device rd_;
	std::default_random_engine random_generator_;
};

#endif
