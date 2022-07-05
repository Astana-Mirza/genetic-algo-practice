#include "common/individual_representation.h"

void IndividualRepresentation::add_rectangle(size_t index, size_t x, size_t y, bool rotation)
{
    configutation_.emplace_back(index, x, y, rotation);
}


const std::vector<RectangleRepresentation>& IndividualRepresentation::get_configuration() const
{
    return configutation_;
}
