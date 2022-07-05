#include <genetic/fitness_stop_condition.h>
#include <genetic/packer.h>
#include <cmath>

FitnessStopCondition::FitnessStopCondition(double fitness):
    fitness_{fitness} {}


bool FitnessStopCondition::is_stop(const Packer &packer) const
{
    for (const auto& individual : packer.get_population())
    {
        if (std::fabs(individual.get_fitness() - fitness_) < 0.0001)
        {
            return true;
        }
    }
    return false;
}
