#include "gui/data.h"
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>

void Data::read_from_file()
{
    if (file_name_.isEmpty())
    {
        return;
    }
    QFile file(file_name_);
    if (!file.open(QFile::OpenModeFlag::ReadOnly))
    {
        throw std::runtime_error{QObject::tr("Cannot open file").toStdString()};
    }

    QTextStream stream(&file);
    if (stream.atEnd())
    {
        throw std::runtime_error{QObject::tr("No tape width in file").toStdString()};
    }
    size_t new_tape_width = 0;
    pair_vector new_info;
    stream >> new_tape_width;
    if (new_tape_width == 0)
    {
        throw std::runtime_error{QObject::tr("Tape width cannot be zero").toStdString()};
    }
    while (!stream.atEnd())
    {
        size_t width = 0, height = 0;
        stream >> width >> height;
        if (stream.status() != QTextStream::Ok)
        {
            throw std::runtime_error{QObject::tr("Invalid file").toStdString()};
        }
        if (width == 0 || height == 0)
        {
            throw std::runtime_error{QObject::tr("Read rectangle with zero square").toStdString()};
        }
        stream.skipWhiteSpace();
        new_info.push_back({width, height});
    }
    tape_width_ = new_tape_width;
    rectangles_info_ = new_info;
    update_palette();
}


void Data::update(const Data& other)
{
    file_name_ = other.get_file_name();
    tape_width_ = other.get_tape_width();
    rectangles_info_ = other.get_rectangles_info();
    update_palette();
}


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


void Data::set_tape_width(size_t width)
{
    tape_width_ = width;
}


void Data::set_rectangles_info(const pair_vector& info)
{
    rectangles_info_ = info;
}


void Data::update_palette()
{
    if (color_palette_.size() > rectangles_info_.size())
    {
        color_palette_.resize(rectangles_info_.size(), QColor{});
    } else
    {
        for (size_t i = color_palette_.size(); i < rectangles_info_.size(); ++i)
            color_palette_.emplace_back(
                QRandomGenerator::system()->bounded(0, 255),
                QRandomGenerator::system()->bounded(0, 255),
                QRandomGenerator::system()->bounded(0, 255)
            );
    }
}


QColor Data::get_color(size_t index) const
{
    return color_palette_.at(index);
}
