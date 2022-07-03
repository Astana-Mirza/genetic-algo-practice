#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>

#include "gene.h"

class Individual
{
public:
	Individual(
		const std::vector<Gene>& genes,
		const std::vector<std::pair<int, int>> rectangles,
		int tape_width
	);

	int genes_count() const;
	const Gene& get_gene(int gene_index) const;
	const std::vector<Gene>& get_genes() const;

	float get_fitness() const;
	bool is_feasible() const;
protected:
	bool check_is_feasible(
		const std::vector<std::pair<int, int>> rectangles,
		int tape_width
	) const;
	float calculate_fitness(
		const std::vector<std::pair<int, int>> rectangles,
		int tape_width
	) const;

	bool is_feasible_;
	float fitness_;
	std::vector<Gene> genes_;
};

#endif
