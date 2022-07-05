#include <genetic/distance_stop_condition.h>
#include <genetic/packer.h>
#include <cmath>

DistanceStopCondition::DistanceStopCondition(double distance):
    distance_{distance} {}


bool DistanceStopCondition::is_stop(const Packer &packer) const
{
    const auto& population = packer.get_population();
    for (size_t i = 0; i < population.size()-1; i++)
    {
        for (size_t j = i + 1; j < population.size(); j++)
        {
            if (std::fabs(population[i].get_fitness() - population[j].get_fitness()) > distance_)
            {
                return false;
            }
        }
    }
    return true;
}
