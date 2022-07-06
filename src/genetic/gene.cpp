#include "genetic/gene.h"

Gene::Gene(int coordinate, int index, bool rotate):
    coordinate_{coordinate},
    index_{index},
    rotate_{rotate}
{}


int Gene::get_coordinate() const
{
    return coordinate_;
}


int Gene::get_index() const
{
    return index_;
}


bool Gene::get_rotation() const
{
    return rotate_;
}
