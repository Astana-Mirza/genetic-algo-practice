#include "genetic/gene.h"

Gene::Gene(size_t coordinate, size_t index, bool rotate):
    coordinate_{coordinate},
    index_{index},
    rotate_{rotate}
{}


size_t Gene::get_coordinate() const
{
    return coordinate_;
}


size_t Gene::get_index() const
{
    return index_;
}


bool Gene::get_rotation() const
{
    return rotate_;
}
