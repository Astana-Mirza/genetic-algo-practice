#include <gui/settings_dialog.h>
#include <ui_settings_dialog.h>
#include <QFileDialog>
#include <QMessageBox>
#include <cmath>

SettingsDialog::SettingsDialog(QWidget *parent, const Settings& settings):
    QDialog(parent), settings_(settings), ui_(new Ui::SettingsDialog)
{
    ui_->setupUi(this);
    display_settings();
}


SettingsDialog::~SettingsDialog()
{
    delete ui_;
}


const Settings& SettingsDialog::get_settings() const
{
    return settings_;
}


void SettingsDialog::display_settings()
{
    ui_->pop_spin_box->setValue(settings_.population_size);
    ui_->mutation_input->setValue(settings_.p_mutation);
    ui_->cross_1_input->setValue(settings_.p_crossover1);
    ui_->cross_2_input->setValue(settings_.p_crossover2);
    ui_->trunc_part->setValue(settings_.bad_part);
    ui_->fitness_spin_box->setValue(settings_.fitness);
    ui_->step_spin_box->setValue(settings_.step_count);
    ui_->distance_spin_box->setValue(settings_.distance);
    switch (settings_.pair_select_type)
    {
    case Settings::PairSelectionType::Panmixing:
        ui_->panmixing->toggle();
        break;
    case Settings::PairSelectionType::Roulette:
        ui_->roulette->toggle();
        break;
    }
    switch (settings_.indiv_select_type)
    {
    case Settings::IndividualSelectionType::Truncation:
        ui_->truncation->toggle();
        ui_->trunc_part->setDisabled(false);
        break;
    case Settings::IndividualSelectionType::Elite:
        ui_->elite->toggle();
        ui_->trunc_part->setDisabled(true);
        break;
    }
    switch (settings_.stop_condition)
    {
    case Settings::StopCondition::Fitness:
        ui_->fitness->toggle();
        ui_->fitness_spin_box->setDisabled(false);
        ui_->step_spin_box->setDisabled(true);
        ui_->distance_spin_box->setDisabled(true);
        break;
    case Settings::StopCondition::StepCount:
        ui_->step_count->toggle();
        ui_->step_spin_box->setDisabled(false);
        ui_->fitness_spin_box->setDisabled(true);
        ui_->distance_spin_box->setDisabled(true);
        break;
    case Settings::StopCondition::Distance:
        ui_->distance->toggle();
        ui_->distance_spin_box->setDisabled(false);
        ui_->step_spin_box->setDisabled(true);
        ui_->fitness_spin_box->setDisabled(true);
        break;
    }
    ui_->file->setChecked(settings_.log_to_file);
    ui_->select_button->setDisabled(!settings_.log_to_file);
    ui_->select_button->setText(settings_.log_file.isEmpty() ? tr("Select file") : settings_.log_file);
    ui_->console->setChecked(settings_.log_to_console);
}


bool SettingsDialog::check_validity() const
{
    if (std::fabs(settings_.p_crossover1 + settings_.p_crossover2 + settings_.p_mutation - 1) >= 0.01)
    {
        QMessageBox msg;
        msg.critical(nullptr, tr("Error"), tr("Sum of probabilities must be 1"));
        return false;
    }
    if (settings_.log_to_file && settings_.log_file.isEmpty())
    {
        QMessageBox msg;
        msg.critical(nullptr, tr("Error"), tr("Log file was not selected"));
        return false;
    }
    return true;
}


void SettingsDialog::on_pop_spin_box_valueChanged(int arg1)
{
    settings_.population_size = arg1;
}


void SettingsDialog::on_save_button_clicked()
{
    if (check_validity())
    {
        accept();
    }
}


void SettingsDialog::on_cancel_button_clicked()
{
    reject();
}


void SettingsDialog::on_mutation_input_valueChanged(double arg1)
{
    settings_.p_mutation = arg1;
}


void SettingsDialog::on_cross_1_input_valueChanged(double arg1)
{
    settings_.p_crossover1 = arg1;
}


void SettingsDialog::on_cross_2_input_valueChanged(double arg1)
{
    settings_.p_crossover2 = arg1;
}


void SettingsDialog::on_panmixing_toggled(bool checked)
{
    if (checked)
    {
        settings_.pair_select_type = Settings::PairSelectionType::Panmixing;
    }
}


void SettingsDialog::on_roulette_toggled(bool checked)
{
    if (checked)
    {
        settings_.pair_select_type = Settings::PairSelectionType::Roulette;
    }
}


void SettingsDialog::on_truncation_toggled(bool checked)
{
    if (checked)
    {
        settings_.indiv_select_type = Settings::IndividualSelectionType::Truncation;
        ui_->trunc_part->setDisabled(false);
    }
    else
    {
        ui_->trunc_part->setDisabled(true);
    }
}


void SettingsDialog::on_elite_toggled(bool checked)
{
    if (checked)
    {
        settings_.indiv_select_type = Settings::IndividualSelectionType::Elite;
    }
}


void SettingsDialog::on_fitness_toggled(bool checked)
{
    if (checked)
    {
        settings_.stop_condition = Settings::StopCondition::Fitness;
        ui_->fitness_spin_box->setDisabled(false);
    }
    else
    {
        ui_->fitness_spin_box->setDisabled(true);
    }
}


void SettingsDialog::on_step_count_toggled(bool checked)
{
    if (checked)
    {
        settings_.stop_condition = Settings::StopCondition::StepCount;
        ui_->step_spin_box->setDisabled(false);
    }
    else
    {
        ui_->step_spin_box->setDisabled(true);
    }
}


void SettingsDialog::on_distance_toggled(bool checked)
{
    if (checked)
    {
        settings_.stop_condition = Settings::StopCondition::Distance;
        ui_->distance_spin_box->setDisabled(false);
    }
    else
    {
        ui_->distance_spin_box->setDisabled(true);
    }
}


void SettingsDialog::on_fitness_spin_box_valueChanged(double arg1)
{
    settings_.fitness = arg1;
}


void SettingsDialog::on_step_spin_box_valueChanged(int arg1)
{
    settings_.step_count = arg1;
}


void SettingsDialog::on_distance_spin_box_valueChanged(double arg1)
{
    settings_.distance = arg1;
}


void SettingsDialog::on_file_toggled(bool checked)
{
    settings_.log_to_file = checked;
    ui_->select_button->setDisabled(!checked);
}


void SettingsDialog::on_console_toggled(bool checked)
{
    settings_.log_to_console = checked;
}


void SettingsDialog::on_level_select_currentIndexChanged(int index)
{

}


void SettingsDialog::on_select_button_clicked()
{
    settings_.log_file = QFileDialog::getSaveFileName(nullptr, tr("Select file"));
}
