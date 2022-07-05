#ifndef DATA_H
#define DATA_H

#include <vector>
#include <QString>
#include <QColor>

using pair_vector = std::vector<std::pair<size_t, size_t>>;

//! @brief Класс входных данных для алгоритма.
class Data
{
public:
    //! @brief Считать данные из файла file_name_, если он задан.
    void read_from_file();

    QString get_file_name() const;
    int get_tape_width() const;
    const pair_vector& get_rectangles_info() const;

    void set_file_name(QString name);
    void set_tape_width(size_t width);
    void set_rectangles_info(const pair_vector& info);

    void update(const Data& other);
private:
    void update_palette();

    QString file_name_;
    size_t tape_width_ = 0;
    pair_vector rectangles_info_;
    std::vector<QColor> color_palette_;
};

#endif // DATA_H
