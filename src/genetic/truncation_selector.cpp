#include "genetic/truncation_selector.h"
#include "genetic/individual.h"

TruncationSelector::TruncationSelector(float unsuitables_part):
	unsuitables_part_{unsuitables_part},
	random_generator_{rd_()}
{}


std::vector<Individual> TruncationSelector::exec(
	const std::vector<Individual>& population, 
	int population_size
)
{
    std::vector<Individual> new_population;
    return new_population;
}
