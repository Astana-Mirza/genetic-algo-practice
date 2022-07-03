#ifndef SEPARATOR_CROSSOVER_H
#define SEPARATOR_CROSSOVER_H

#include "abstract/icrossover.h"

class SeparatorCrossover: public ICrossover
{
public:
	std::vector<Gene> operator() (const Individual& parent1, const Individual& parent2);
};

#endif
