#include "genetic/truncation_selector.h"
#include "genetic/individual.h"

#include <algorithm>

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
    std::vector<Individual> copy(population);

    std::sort(
        copy.begin(), copy.end(), 
        [](const Individual& individual1, const Individual& individual2){
            return individual1.get_fitness() > individual2.get_fitness();
        }
    );
    copy.resize(population.size() - population_size * unsuitables_part_, Individual{{}, {}, 0});

    std::uniform_int_distribution<> individual_distribution(0, population_size - 1);
    for (int i = 0; i < population_size; ++i)
    {
        new_population.push_back(
            copy.at(individual_distribution(random_generator_))
        );
    }

    return new_population;
}
