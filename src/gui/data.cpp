#include "gui/data.h"
#include <QFile>
#include <QTextStream>

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
