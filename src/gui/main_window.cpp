#include <gui/main_window.h>
#include <ui_main_window.h>

#include <QTableWidgetItem>

#include <gui/settings_dialog.h>
#include <logger/log.h>

#include <logger/console_logger.h>
#include <logger/file_logger.h>
#include <logger/tab_logger.h>

#include <genetic/elite_selector.h>
#include <genetic/truncation_selector.h>
#include <genetic/panmixing_parent_selector.h>
#include <genetic/roulette_parent_selector.h>
#include <genetic/distance_stop_condition.h>
#include <genetic/fitness_stop_condition.h>
#include <genetic/iter_stop_condition.h>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), iter_(parents_.cend()), packer_(nullptr), ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::on_action_settings_triggered()
{
    SettingsDialog dialog(nullptr, algo_settings_);
    if (dialog.exec() == QDialog::Accepted)
    {
        algo_settings_ = dialog.get_settings();
        apply_settings();
    }
}


void MainWindow::on_action_enter_data_triggered()
{
    EnterData dialog(nullptr, data_);
    if (dialog.exec() == QDialog::Accepted)
    {
        data_.update(dialog.get_data());
        data_.read_from_file();          // @TODO убрать отсюда, занести в enter_data
        apply_settings();
    }
}


void MainWindow::on_action_step_triggered()
{
    if (!packer_)
    {
        return;
    }
    ui_->action_enter_data->setDisabled(true);
    ui_->action_settings->setDisabled(true);
    /*if (iter_ != parents_.cend())
    {
        advance_parent_display();
        return;
    }*/
    Result result = packer_->step();
    switch (result.state)
    {
        case Result::State::InitPopulation:
            display_population();
            break;
        case Result::State::IndividualGeneration:
            parents_ = result.changed_individuals;
            iter_ = parents_.cbegin();
            display_population();
            advance_parent_display();
            break;
        case Result::State::Selection:
            display_population();
            break;
        default:
            return;
    }
}


void MainWindow::on_action_stop_triggered()
{
    ui_->table_widget->setRowCount(0);
    ui_->action_enter_data->setDisabled(false);
    ui_->action_settings->setDisabled(false);
    apply_settings();
}


void MainWindow::on_table_widget_itemSelectionChanged()
{
    ui_->text_edit_indiv->clear();
    if (ui_->table_widget->selectedItems().isEmpty() || !packer_)
    {
        return;
    }
    QTableWidgetItem *current = ui_->table_widget->selectedItems()[0];
    double fitness = packer_->get_population().at(current->row()).get_fitness();
    const auto& rectangles = packer_->get_population().at(current->row()).representation().get_configuration();
    ui_->text_edit_indiv->insertPlainText(tr("Fitness: %1\n\n").arg(fitness, 0, 'f', 4));
    for (const RectangleRepresentation& rect : rectangles)
    {
        ui_->text_edit_indiv->insertPlainText(tr("Rectangle №") + QString::number(rect.get_index() + 1) + ": "
                                              + "X = " + QString::number(rect.get_x()) + ", Y = "
                                              + QString::number(rect.get_y()));
        if (rect.get_rotation())
        {
            ui_->text_edit_indiv->insertPlainText(tr(", rotated 90 deg"));
        }
        ui_->text_edit_indiv->insertPlainText("\n");
    }
}


void MainWindow::apply_settings()
{
    std::unique_ptr<IParentSelector> parent_select;
    std::unique_ptr<ISelector> population_select;
    std::unique_ptr<IStopCondition> stop_condition;
    switch (algo_settings_.indiv_select_type)
    {
        case Settings::IndividualSelectionType::Elite:
            population_select = std::make_unique<EliteSelector>();
            break;
        case Settings::IndividualSelectionType::Truncation:
            population_select = std::make_unique<TruncationSelector>(algo_settings_.bad_part);
            break;
    }
    switch (algo_settings_.pair_select_type)
    {
        case Settings::PairSelectionType::Panmixing:
            parent_select = std::make_unique<PanmixingParentSelector>();
            break;
        case Settings::PairSelectionType::Roulette:
            parent_select = std::make_unique<RouletteParentSelector>();
            break;
    }
    switch (algo_settings_.stop_condition)
    {
        case Settings::StopCondition::Distance:
            stop_condition = std::make_unique<DistanceStopCondition>(algo_settings_.distance);
            break;
        case Settings::StopCondition::Fitness:
            stop_condition = std::make_unique<FitnessStopCondition>(algo_settings_.fitness);
            break;
        case Settings::StopCondition::StepCount:
            stop_condition = std::make_unique<IterStopCondition>(algo_settings_.step_count);
            break;
    }
    packer_ = std::make_unique<Packer>(data_.get_rectangles_info(), data_.get_tape_width(),
                                       std::move(parent_select), std::move(population_select),
                                       std::move(stop_condition), algo_settings_.population_size,
                                       algo_settings_.p_crossover1, algo_settings_.p_crossover2,
                                       algo_settings_.p_mutation);
}


void MainWindow::display_population()
{
    if (!packer_)
    {
        return;
    }
    const auto& population = packer_->get_population();
    size_t max_fitness_index = 0;
    double max_fitness = 0;
    ui_->table_widget->clearContents();
    ui_->text_edit_indiv->clear();
    ui_->table_widget->setRowCount(population.size());
    for (size_t i = 0; i < population.size(); i++)
    {
        double fitness = population.at(i).get_fitness();
        if (fitness > max_fitness)
        {
            max_fitness = fitness;
            max_fitness_index = i;
        }
        QTableWidgetItem *item = new QTableWidgetItem(tr("Individual ") +
                                                      QString::number(i+1) + ": " +
                                                      QString("%1").arg(fitness, 0, 'f', 4));
        ui_->table_widget->setItem(i, 0, item);
    }
    ui_->table_widget->item(max_fitness_index, 0)->setBackgroundColor(QColor(162, 84, 203));
}


void MainWindow::advance_parent_display()
{

}
