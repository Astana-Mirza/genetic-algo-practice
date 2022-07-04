#ifndef TRUNCATION_SELECTOR_H
#define TRUNCATION_SELECTOR_H

#include "abstract/iselector.h"
#include <random>

/**
 * @brief Оператор отбора особей в новом поколении методом отсечения
 * @details Имеется 2N особей после генерации нового поколения,
 * нужно отсеять N особей, чтобы размер популяции стал составлять N.
 * Для этого задается параметр unsuitables_part, который определеяет
 * долю непригодных особей. Далее, из особей, не попавших в долю непригодных,
 * выбирается одна. Процесс отбора повторяется N раз
 */
class TruncationSelector: public ISelector
{
public:
	/**
	 * @brief Конструктор оператора отбора особей методом отсечения
	 * 
	 * @param unsuitables_part Доля непригодных особей
	 */
	TruncationSelector(float unsuitables_part = 0.25);

	/**
	 * @brief Отбор особей в новое поколение методом отсечения
	 * @details Метод выбирает заданное количество особей в новое поколение
	 * 
	 * @param population Популяция, из которой будет происходить выбор особей
	 * @param population_size Желаемый размер популяции
	 * 
	 * @return Новое поколение
	 */
	std::vector<Individual> exec(
		const std::vector<Individual>& population, 
		int population_size
	);
protected:
	/**
	 * Доля непригодных особей
	 */
	float unsuitables_part_;
	/**
	 * Генератор случайных чисел
	 */
	std::random_device rd_;
	std::default_random_engine random_generator_;
};

#endif
