#ifndef PACKER_H
#define PACKER_H

#include <vector>

#include "individual.h"
#include "abstract/icrossover.h"
#include "abstract/imutator.h"


class Packer
{
public:
	Packer(
		const std::vector<std::pair<int, int>>& rectangles,
		int tape_width,
		int population_size = 20,
		float crossover1_probability = 0.45,
		float crossover2_probability = 0.45,
		float mutation_probability = 0.1
	);
	~Packer();

	void print_population() const;

	void generate_new_breed();
protected:
	void init_population();

	std::vector<std::pair<int, int>> rectangles_;
	int tape_width_;
	int population_size_;
	std::vector<Individual> population_;

	float probabilities_[3];

	ICrossover* crossover1_operator_;
	ICrossover* crossover2_operator_;
	IMutator* mutation_operator_;
};

#endif
