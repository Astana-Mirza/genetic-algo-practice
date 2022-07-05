#ifndef PACKER_H
#define PACKER_H

#include <vector>
#include <memory>

#include "individual.h"
#include "abstract/icrossover.h"
#include "abstract/imutator.h"
#include "abstract/iparent_selector.h"
#include "abstract/iselector.h"
#include "abstract/istop_condition.h"

#include "genetic/result.h"

/**
 * @brief Класс, отвечающий за решение задачи раскроя
 * с помощью генетического алгоритма
 */
class Packer
{
public:
	/**
	 * @brief Конструктор класса генетического алгоритма
	 * @details На основе переданных условий задачи (конфигурации прямоугольников и ширина ленты)
	 * инициализируется генетический алгоритм для рещения задачи. Также могут быть заданы параметры алгоритма
	 * 
	 * @param rectangles Конфигурации прямоугольников, которые необходимо разместить на ленте
	 * @param tape_width Ширина замощаемой ленты
	 * @param parent_selection_operator Оператор выбора родителя
	 * @param selection_operator Оператор отбора особей
	 * @param population_size Размер популяции в генетическом алгоритме
	 * @param crossover1_probability Вероятность использования первого оператора кроссовера
	 * @param crossover2_probability Вероятность использования второго оператора кроссовера
	 * @param mutation_probability Вероятность использования оператора мутации
	 */
	Packer(
		const std::vector<std::pair<int, int>>& rectangles,
        size_t tape_width,
        std::unique_ptr<IParentSelector>&& parent_selection_operator,
        std::unique_ptr<ISelector>&& selection_operator,
        std::unique_ptr<IStopCondition>&& stop_condition,
        size_t population_size = 20,
        double crossover1_probability = 0.45,
        double crossover2_probability = 0.45,
        double mutation_probability = 0.1
    );

    //! @brief Выполнить один шаг алгоритма и вернуть результат.
    Result step();

    //! @brief Получить текущую популяцию.
    const std::vector<Individual>& get_population() const;

    //! @brief Получить количество итераций алгоритма.
    size_t get_iteration_count() const;
protected:
    //! @brief Метод генерации начальной популяции
    Result init_population();

    //! @brief Метод генерации нового поколения
    Result generate_new_breed();

    //! @brief Выбор особей в новую популяцию
    Result selection();

    std::vector<std::pair<int, int>> rectangles_;   //! < прямоугольники для замощения ленты
    std::vector<Individual> population_;            //! < текущая популяция
    size_t iteration_count_;                        //! < количество итераций алгоритма
    size_t tape_width_;                             //! < ширина ленты
    size_t population_size_;                        //! < размер популяции
    double probabilities_[3];                       //! < вероятности выбора операторов
    std::unique_ptr<IStopCondition> stop_condition_;                //! < оператор проверки критерия остановки
    std::unique_ptr<ICrossover> crossover1_operator_;               //! < оператор кроссовера 1
    std::unique_ptr<ICrossover> crossover2_operator_;               //! < оператор кроссовера 2
    std::unique_ptr<IMutator> mutation_operator_;                   //! < оператор мутации
    std::unique_ptr<IParentSelector> parent_selection_operator_;    //! < оператор выбора родителей
    std::unique_ptr<ISelector> selection_operator_;                 //! < оператор отбора в популяцию
    Result::State current_state_;                                   //! < текущее состояние алгоритма
};

#endif
