#ifndef ICROSSOVER_H
#define ICROSSOVER_H

#include <vector>

class Individual;
class Gene;

class ICrossover
{
public:
	virtual std::vector<Gene> operator() (const Individual&, const Individual&) = 0;
};

#endif
