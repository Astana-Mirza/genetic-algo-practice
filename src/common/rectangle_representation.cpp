#include "common/rectangle_representation.h"

RectangleRepresentation::RectangleRepresentation(
    size_t index,
    size_t x,
    size_t y,
    bool rotation
):
    index_{index},
    x_{x},
    y_{y},
    rotation_{rotation}
{}


size_t RectangleRepresentation::get_index() const
{
    return index_;
}


size_t RectangleRepresentation::get_x() const
{
    return x_;
}


size_t RectangleRepresentation::get_y() const
{
    return y_;
}


bool RectangleRepresentation::get_rotation() const
{
    return rotation_;
}
