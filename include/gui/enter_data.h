#ifndef ENTER_DATA_H
#define ENTER_DATA_H

#include <QDialog>
#include "gui/data.h"

namespace Ui
{
class EnterData;
}


//! @brief Класс для окна ввода данных.
class EnterData : public QDialog
{
    Q_OBJECT

public:
    //! @brief Конструктор.
    //! @param parent указатель на виджет-родитель.
    //! @param data объект входных данных для алгоритма.
    explicit EnterData(QWidget *parent = nullptr, const Data& data = {});
    ~EnterData();
    const Data& get_data();
    void display_data();

private slots:
    void on_ok_button_clicked();
    void on_cancel_button_clicked();
    void on_open_file_button_clicked();
    void on_add_rectangle_button_clicked();
    void on_delete_rectangle_button_clicked();

private:
    Data data_;
    Ui::EnterData *ui;
};

#endif // ENTER_DATA_H
