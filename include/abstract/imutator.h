#ifndef IMUTATOR_H
#define IMUTATOR_H

#include <vector>

class Individual;
class Gene;

class IMutator
{
public:
	virtual std::vector<Gene> operator() (const Individual&) = 0;
};

#endif
