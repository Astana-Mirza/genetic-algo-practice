#include "genetic/packer.h"
#include "genetic/separator_crossover.h"
#include "genetic/order_crossover.h"
#include "genetic/order_mutator.h"
#include "logger/log.h"

#include <random>
#include <algorithm>
#include <QObject>

Packer::Packer(
    const std::vector<std::pair<size_t, size_t>>& rectangles,
    size_t tape_width,
    std::unique_ptr<IParentSelector>&& parent_selection_operator,
    std::unique_ptr<ISelector>&& selection_operator,
    std::unique_ptr<IStopCondition>&& stop_condition,
    size_t population_size,
    double crossover1_probability,
    double crossover2_probability,
    double mutation_probability
):
    rectangles_{rectangles},
    iteration_count_{0},
    tape_width_{tape_width},
    population_size_{population_size},
    probabilities_{
        crossover1_probability,
        crossover2_probability,
        mutation_probability
    },
    // Создание операторов кроссовера и мутации
    stop_condition_{std::move(stop_condition)},
    crossover1_operator_{std::make_unique<SeparatorCrossover>()},
    crossover2_operator_{std::make_unique<OrderCrossover>()},
    mutation_operator_{std::make_unique<OrderMutator>(rectangles, tape_width)},
    parent_selection_operator_{std::move(parent_selection_operator)},
    selection_operator_{std::move(selection_operator)},
    current_state_{Result::State::Start}
{
    Log::get_log().debug(QObject::tr("Algorithm started"));
}


Result Packer::step()
{
    Result result{Result::State::End, {}};
    if (current_state_ == Result::State::End ||
       (current_state_ == Result::State::Selection && stop_condition_->is_stop(*this)))
    {
        Log::get_log().debug(QObject::tr("State: ") + QObject::tr("End"));
        current_state_ = Result::State::End;
        return result;
    }
    switch (current_state_)
    {
        case Result::State::Start:
            result = init_population();
            break;
        case Result::State::InitPopulation:
            result = generate_new_breed();
            break;
        case Result::State::IndividualGeneration:
            result = selection();
            break;
        case Result::State::Selection:
            result = generate_new_breed();
            ++iteration_count_;
            break;
        default:
            break;
    }
    current_state_ = result.state;

    switch (current_state_)
    {
        case Result::State::Start:
            Log::get_log().debug(QObject::tr("State: ") + QObject::tr("Start"));
            break;
        case Result::State::InitPopulation:
            Log::get_log().debug(QObject::tr("State: ") + QObject::tr("Init Population"));
            break;
        case Result::State::IndividualGeneration:
            Log::get_log().debug(QObject::tr("State: ") + QObject::tr("Individual Generation"));
            break;
        case Result::State::Selection:
            Log::get_log().debug(QObject::tr("State: ") + QObject::tr("Selection"));
            break;
        case Result::State::End:
            Log::get_log().debug(QObject::tr("State: ") + QObject::tr("End"));
            break;
    }

    return result;
}


const std::vector<Individual>& Packer::get_population() const
{
    return population_;
}


size_t Packer::get_iteration_count() const
{
    return iteration_count_;
}


Result Packer::init_population()
{
    Log::get_log().info(QObject::tr("Generating initial population"));

    std::random_device rd;
    std::default_random_engine random_generator(rd());
    std::uniform_int_distribution<> rotation_distribution(0, 1);
    // Формирование начальной популяции
    population_.reserve(population_size_);

    for (size_t i = 0; i < population_size_; ++i)
    {
        // Инициализируем гены новой особи
        std::vector<Gene> genes;
        for (size_t k = 0; k < rectangles_.size(); ++k)
        {
            // Проходим по всем прямоугольникам из условия
            // Случайным образом определяем, будем ли делать поворот на 90 градусов
            bool rotation;
            // Проверяем, есть ли возможность повернуть прямоугольник
            if (rectangles_.at(k).first > tape_width_)
                rotation = true;
            else if (rectangles_.at(k).second > tape_width_)
                rotation = false;
            else
                rotation = rotation_distribution(random_generator) != 0;
            // Определяем координату x нижнего левого угла прямоугольника на ленте
            int rectangle_width = rotation ? rectangles_.at(k).second : rectangles_.at(k).first;
            std::uniform_int_distribution<> coordinate_distribution(
                0, tape_width_ - rectangle_width
            );
            // Записываем ген
            genes.emplace_back(
                coordinate_distribution(random_generator),
                k,
                rotation
            );
        }
        // Изменяем порядок генов у особи
        std::shuffle(genes.begin(), genes.end(), random_generator);
        // Добавляем особь в популяцию
        population_.emplace_back(genes, rectangles_, tape_width_);
    }
    return Result{Result::State::InitPopulation, {}};
}


Result Packer::generate_new_breed()
{
    Log::get_log().info(QObject::tr("Starting individual generation (crossovers and mutations)"));

    Result result{Result::State::IndividualGeneration, {}};
    // Используем кроссинговеры и мутацию, после используем отбор
    std::random_device rd;
    std::default_random_engine random_generator(rd());
    std::uniform_real_distribution<> probability_distribution(0, 1);

    for (size_t index = 0; index < population_size_; ++index)
    {
        const Individual& parent1 = population_.at(index);
        // Выбор второго родителя с помощью оператора
        size_t second_index = parent_selection_operator_->exec(population_, population_size_);
        // Определение оператора (кроссоверы или мутация)
        float operation = probability_distribution(random_generator);
        if (operation <= probabilities_[0])
        {
            // Кроссинговер 1
            Log::get_log().info(
                QObject::tr("Crossover of individuals ") + QString::number(index + 1) +
                QObject::tr(" and ") + QString::number(second_index + 1)
            );
            population_.emplace_back(
                crossover1_operator_->exec(parent1, population_.at(second_index)),
                rectangles_,
                tape_width_
            );
            result.changed_individuals.push_back({index, second_index, population_.size() - 1});
        } else if (operation <= probabilities_[0] + probabilities_[1])
        {
            // Кроссинговер 2
            Log::get_log().info(
                QObject::tr("Crossover of individuals ") + QString::number(index + 1) +
                QObject::tr(" and ") + QString::number(second_index + 1)
            );
            population_.emplace_back(
                crossover2_operator_->exec(parent1, population_.at(second_index)),
                rectangles_,
                tape_width_
            );
            result.changed_individuals.push_back({index, second_index, population_.size() - 1});
        } else if (operation <= probabilities_[0] + probabilities_[1] + probabilities_[2])
        {
            // Мутация
            Log::get_log().info(
                QObject::tr("Mutation of individual ") + QString::number(index + 1)
            );
            population_.emplace_back(
                mutation_operator_->exec(parent1),
                rectangles_,
                tape_width_
            );
            result.changed_individuals.push_back({index, static_cast<size_t>(-1), population_.size() - 1});
        }
    }
    return result;
}


Result Packer::selection()
{
    // Отбираем подходящие особи
    Log::get_log().info(QObject::tr("Selection of best individuals"));
    population_ = selection_operator_->exec(population_, population_size_);
    return Result{Result::State::Selection, {}};
}
