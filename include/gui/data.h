#ifndef DATA_H
#define DATA_H

#include <vector>
#include <QString>

using pair_vector = std::vector<std::pair<int, int>>;

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
    void set_tape_width(int width);
    void set_rectangles_info(const pair_vector& info);

private:
    QString file_name_;
    int tape_width_ = 0;
    pair_vector rectangles_info_;
};

#endif // DATA_H
