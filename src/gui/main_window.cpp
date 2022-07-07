#include <gui/main_window.h>
#include <ui_main_window.h>

#include <QTableWidgetItem>
#include <QMessageBox>

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
    Log::get_log().add_logger("tab", std::make_unique<TabLogger>(ui_->text_edit_log));
    Log::get_log().debug(tr("Starting program"));
    scene_ = new QGraphicsScene();
    ui_->graphics_view->setScene(scene_);
    ui_->graphics_view->setMinimumHeight(350);
    ui_->graphics_view->setMinimumWidth(450);
    ui_->graphics_view->setStyleSheet("padding: 20px 0;");
}


MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::on_action_settings_triggered()
{
    Log::get_log().debug(tr("Opening settings dialog"));
    SettingsDialog dialog(nullptr, algo_settings_);
    if (dialog.exec() == QDialog::Accepted)
    {
        algo_settings_ = dialog.get_settings();
        apply_settings();
        apply_log_settings();
    }
}


void MainWindow::on_action_enter_data_triggered()
{
    Log::get_log().debug(tr("Opening data input dialog"));
    EnterData dialog(nullptr, data_);
    if (dialog.exec() == QDialog::Accepted)
    {
        data_.update(dialog.get_data());
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
    if (iter_ != parents_.cend())
    {
        advance_parent_display();
        return;
    }
    Result result = packer_->step();
    switch (result.state)
    {
        case Result::State::InitPopulation:
            Log::get_log().info(tr("Generating initial population"));
            display_population();
            break;
        case Result::State::IndividualGeneration:
            Log::get_log().info(tr("Starting individual generation (crossovers and mutations)"));
            parents_ = result.changed_individuals;
            iter_ = parents_.cbegin();
            display_population();
            advance_parent_display();
            break;
        case Result::State::Selection:
            Log::get_log().info(tr("Selection of best individuals"));
            display_population();
            break;
        default:
            return;
    }
}


void MainWindow::on_action_run_triggered()
{
    if (!packer_)
    {
        return;
    }
    ui_->action_enter_data->setDisabled(true);
    ui_->action_settings->setDisabled(true);
    for (Result res = packer_->step(); res.state != Result::State::End; res = packer_->step())
        ;
    display_population();
}


void MainWindow::on_action_stop_triggered()
{
    Log::get_log().debug(tr("Algorithm stopped"));
    ui_->table_widget->setRowCount(0);
    ui_->action_enter_data->setDisabled(false);
    ui_->action_settings->setDisabled(false);
    ui_->text_edit_log->clear();
    parents_.clear();
    iter_ = parents_.cbegin();
    apply_settings();
}


void MainWindow::on_table_widget_itemSelectionChanged()
{
    ui_->text_edit_indiv->clear();
    scene_->clear();
    if (ui_->table_widget->selectedItems().isEmpty() || !packer_)
    {
        return;
    }
    QTableWidgetItem *current = ui_->table_widget->selectedItems()[0];
    double fitness = packer_->get_population().at(current->row()).get_fitness();
    const auto& rectangles = packer_->get_population().at(current->row()).representation().get_configuration();
    if(fitness == 0)
    {
        scene_->addText("Individual is unsuitable");
    } else
    {
        paint_individual(rectangles);
    }
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


void MainWindow::apply_log_settings()
{
    Log::get_log().set_log_level(algo_settings_.log_level);
    if (algo_settings_.log_to_file)
    {
        try
        {
            Log::get_log().add_logger("file",
                                      std::make_unique<FileLogger>(algo_settings_.log_file));
        }
        catch (const std::runtime_error& e)
        {
            algo_settings_.log_file = "";
            algo_settings_.log_to_file = false;
            QMessageBox msg;
            msg.critical(nullptr, tr("Error"), e.what());
        }
    }
    else
    {
        Log::get_log().delete_logger("file");
    }

    if (algo_settings_.log_to_console)
    {
        Log::get_log().add_logger("console", std::make_unique<ConsoleLogger>());
    }
    else
    {
        Log::get_log().delete_logger("console");
    }
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
    ui_->table_widget->item(max_fitness_index, 0)->setBackgroundColor(Qt::yellow);
}


void MainWindow::advance_parent_display()
{
    if (iter_ != parents_.cbegin()) // убрать раскраску прошлой пары родителей
    {
        auto it = iter_ - 1;
        ui_->table_widget->item(it->at(0), 0)->setBackgroundColor(QColor(Qt::white));
        if (it->at(1) != static_cast<size_t>(-1))
        {
            ui_->table_widget->item(it->at(1), 0)->setBackgroundColor(QColor(Qt::white));
        }
        ui_->table_widget->item(it->at(2), 0)->setBackgroundColor(QColor(Qt::white));
    }
    if (iter_ == parents_.cend())
    {
        return;
    }
    ui_->table_widget->item(iter_->at(0), 0)->setBackgroundColor(QColor(Qt::green));
    if (iter_->at(1) != static_cast<size_t>(-1))
    {
        ui_->table_widget->item(iter_->at(1), 0)->setBackgroundColor(QColor(Qt::green));
        Log::get_log().info(tr("Crossover of individuals ") +
                            QString::number(iter_->at(0) + 1) + tr(" and ") +
                            QString::number(iter_->at(1) + 1));
    }
    else
    {
        Log::get_log().info(tr("Mutation of individual ") + QString::number(iter_->at(0) + 1));
    }
    int child_index = iter_->at(2); // добавление новой строки в таблицу
    double fitness = packer_->get_population().at(child_index).get_fitness();
    QTableWidgetItem *item = new QTableWidgetItem(tr("Individual ") +
                                                  QString::number(child_index+1) + ": " +
                                                  QString("%1").arg(fitness, 0, 'f', 4));
    item->setBackgroundColor(QColor(Qt::cyan));
    ui_->table_widget->setRowCount(child_index + 1);
    ui_->table_widget->setItem(child_index, 0, item);
    ++iter_;
}

void MainWindow::paint_individual(const std::vector<RectangleRepresentation>& rectangles)
{
    double coeff = 300.0 / data_.get_tape_width();
    double tape_lenght = 0;

    for (const RectangleRepresentation& rect : rectangles)
    {
        size_t width = 0;
        size_t height = 0;
        size_t x = rect.get_x();
        size_t y = rect.get_y();

        if(rect.get_rotation())
        {
            height = data_.get_rectangles_info()[rect.get_index()].first;
            width = data_.get_rectangles_info()[rect.get_index()].second;
        } else
        {
            width = data_.get_rectangles_info()[rect.get_index()].first;
            height = data_.get_rectangles_info()[rect.get_index()].second;
        }

        scene_->addRect(x * coeff, y * coeff, width * coeff, height * coeff, QPen(), QBrush(data_.get_color(rect.get_index())));

        if(tape_lenght < y + height)
            tape_lenght = y + height;
    }
    scene_->addRect(0, 0, 300, tape_lenght * coeff);
}

