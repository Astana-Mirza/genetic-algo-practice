#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

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

    //! @brief Слот кнопки "Запуск".
    void on_action_run_triggered();

    //! @brief Слот кнопки "Стоп".
    void on_action_stop_triggered();

    //! @brief Слот изменения выбранного элемента в таблице.
    void on_table_widget_itemSelectionChanged();

private:
    //! @brief Применение настроек алгоритма и занесение входных данных в алгоритм.
    void apply_settings();

    //! @brief Применение настроек логирования.
    void apply_log_settings();

    //! @brief Отобразить выбранную популяцию на экране.
    void display_population();

    //! @brief Отобразить следующую пару родителей и ребёнка (кроссинговер или мутация).
    void advance_parent_display();

    //! @brief Отобразить особь.
    void paint_individual(const std::vector<RectangleRepresentation>& rectangles);

    Settings algo_settings_;                        //! < настройки приложения.
    Data data_;                                     //! < входные данные алгоритма.
    Result::CrossoverResult parents_;               //! < список родственных связей после кроссинговера или мутации.
    Result::CrossoverResult::const_iterator iter_;  //! < итератор на текущую запись о кроссовере
    std::unique_ptr<Packer> packer_;                //! < объект генетического алгоритма.
    Ui::MainWindow *ui_;                            //! < указатель на раскладку.
    QGraphicsScene *scene_;                         //! < указатель на сцену.
};

#endif // #ifndef MAINWINDOW_H
