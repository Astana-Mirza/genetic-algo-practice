#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <gui/settings.h>
#include <gui/enter_data.h>
#include <gui/data.h>

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

private:
    Settings algo_settings_;        //! < настройки приложения.
    Data data_;                     //! < входные данные алгоритма.
    Ui::MainWindow *ui_;            //! < указатель на раскладку.
};

#endif // #ifndef MAINWINDOW_H
