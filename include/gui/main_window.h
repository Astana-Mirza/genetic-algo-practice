#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <gui/settings.h>
#include <gui/enter_data.h>
#include <gui/data.h>

#include <genetic/packer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//! @brief Класс главного окна программы.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! @brief Конструктор, в нём происходит подключение раскладки main_window.ui.
    //! @param parent указатель на виджет-родитель.
    MainWindow(QWidget *parent = nullptr);

    //! @brief Деструктор, в нём происходит удаление раскладки.
    ~MainWindow();

private slots:
    //! @brief Слот кнопки "Настройки".
    void on_action_settings_triggered();

    //! @brief Слот кнопки "Ввести данные".
    void on_action_enter_data_triggered();

    //! @brief Слот кнопки "Шаг".
    void on_action_step_triggered();

    //! @brief Слот кнопки "Стоп".
    void on_action_stop_triggered();

    //! @brief Слот изменения выбранного элемента в таблице.
    void on_table_widget_itemSelectionChanged();

private:
    void apply_settings();
    void display_population();
    void advance_parent_display();

    Settings algo_settings_;                        //! < настройки приложения.
    Data data_;                                     //! < входные данные алгоритма.
    Result::CrossoverResult parents_;               //! < список родственных связей после кроссинговера или мутации.
    Result::CrossoverResult::const_iterator iter_;  //! < итератор на текущую запись о кроссовере
    std::unique_ptr<Packer> packer_;                //! < объект генетического алгоритма.
    Ui::MainWindow *ui_;                            //! < указатель на раскладку.
};

#endif // #ifndef MAINWINDOW_H
