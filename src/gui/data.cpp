#include "gui/data.h"

QString Data::get_file_name() const
{
    return file_name_;
}


int Data::get_tape_width() const
{
    return tape_width_;
}


const pair_vector& Data::get_rectangles_info() const
{
    return rectangles_info_;
}


void Data::set_file_name(QString name)
{
    file_name_ = name;
}


void Data::set_tape_width(int width)
{
    tape_width_ = width;
}


void Data::set_rectangles_info(const pair_vector& info)
{
    rectangles_info_ = info;
}
