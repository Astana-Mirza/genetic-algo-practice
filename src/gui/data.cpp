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
    stream >> tape_width_;
    rectangles_info_.clear();
    while (!stream.atEnd())
    {
        size_t width, height;
        stream >> width >> height;
        if (stream.status() != QTextStream::Ok)
        {
            throw std::runtime_error{QObject::tr("Invalid file").toStdString()};
        }
        stream.skipWhiteSpace();
        rectangles_info_.push_back({width, height});
    }
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


void Data::set_tape_width(int width)
{
    tape_width_ = width;
}


void Data::set_rectangles_info(const pair_vector& info)
{
    rectangles_info_ = info;
}
