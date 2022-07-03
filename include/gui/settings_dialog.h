#ifndef SETTINGS_DIALOG_H
#define SETTINGS_DIALOG_H

#include <QDialog>
#include <gui/settings.h>

namespace Ui
{
class SettingsDialog;
}

//! @brief Класс для окна настроек генетического алгоритма и логирования.
class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    //! @brief Конструктор.
    //! @param parent указатель на виджет-родитель.
    //! @param settings объект настроек, сохранённых ранее.
    explicit SettingsDialog(QWidget *parent = nullptr, const Settings& settings = {});
    ~SettingsDialog();

    const Settings& get_settings() const;

private slots:
    void on_pop_spin_box_valueChanged(int arg1);
    void on_save_button_clicked();
    void on_cancel_button_clicked();
    void on_mutation_input_valueChanged(double arg1);
    void on_cross_1_input_valueChanged(double arg1);
    void on_cross_2_input_valueChanged(double arg1);
    void on_panmixing_toggled(bool checked);
    void on_roulette_toggled(bool checked);
    void on_truncation_toggled(bool checked);
    void on_elite_toggled(bool checked);
    void on_fitness_toggled(bool checked);
    void on_step_count_toggled(bool checked);
    void on_distance_toggled(bool checked);
    void on_fitness_spin_box_valueChanged(double arg1);
    void on_step_spin_box_valueChanged(int arg1);
    void on_distance_spin_box_valueChanged(double arg1);
    void on_file_toggled(bool checked);
    void on_console_toggled(bool checked);
    void on_level_select_currentIndexChanged(int index);

    void on_select_button_clicked();

private:
    bool check_validity() const;
    void display_settings();

    Settings settings_;
    Ui::SettingsDialog *ui_;
};

#endif // SETTINGS_DIALOG_H
