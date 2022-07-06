#include "genetic/roulette_parent_selector.h"
#include "genetic/individual.h"

#include <stdexcept>

RouletteParentSelector::RouletteParentSelector():
    random_generator_{rd_()}
{}


size_t RouletteParentSelector::exec(
    const std::vector<Individual>& population,
    size_t population_size
)
{
    std::uniform_real_distribution<> parent_distribution(0, 1);
    float random_value = parent_distribution(random_generator_);
    float fitnesses_sum = 0;
    for (size_t i = 0; i < population_size; ++i)
        fitnesses_sum += population.at(i).get_fitness();

    for (size_t i = 0; i < population_size; ++i)
    {
        float probability = population.at(i).get_fitness() / fitnesses_sum;
        if (probability >= random_value)
            return i;
        random_value -= probability;
    }

    throw std::out_of_range{"Cannot generate new parent"};
}
