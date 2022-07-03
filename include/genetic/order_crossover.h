#ifndef ORDER_CROSSOVER_H
#define ORDER_CROSSOVER_H

#include "abstract/icrossover.h"

class OrderCrossover: public ICrossover
{
public:
	std::vector<Gene> operator() (const Individual& parent1, const Individual& parent2);
};

#endif
