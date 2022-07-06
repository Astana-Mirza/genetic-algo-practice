#include "genetic/elite_selector.h"
#include "genetic/individual.h"

#include <algorithm>

std::vector<Individual> EliteSelector::exec(
    const std::vector<Individual>& population, 
    int population_size
)
{
    std::vector<Individual> new_population(population);
    std::sort(
        new_population.begin(), new_population.end(),
        [](const Individual& individual1, const Individual& individual2){
            return individual1.get_fitness() > individual2.get_fitness();
        }
    );
    new_population.resize(population_size, Individual{{}, {}, 0});

    return new_population;
}
