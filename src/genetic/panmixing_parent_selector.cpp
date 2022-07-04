#include "genetic/panmixing_parent_selector.h"
#include "genetic/individual.h"

#include <stdexcept>

PanmixingParentSelector::PanmixingParentSelector():
	random_generator_{rd_()}
{}


const Individual& PanmixingParentSelector::exec(
	const std::vector<Individual>& population,
	int population_size
)
{
	std::uniform_int_distribution<> parent_distribution(0, population_size - 1);

	return population.at(
		parent_distribution(random_generator_)
	);
}
