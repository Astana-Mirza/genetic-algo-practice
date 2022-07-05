#ifndef IPARENT_SELECTOR_H
#define IPARENT_SELECTOR_H

#include <vector>

class Individual;

/**
 * @brief Интерфейс оператора выбора родителя
 */
class IParentSelector
{
public:
	/**
	 * @brief Выбор родительской особи
	 * 
	 * @param population Текушая популяция
	 * @param population_size Размер популяции
	 * 
	 * @return Родительская особь
	 */
    virtual size_t exec(
		const std::vector<Individual>& population,
        size_t population_size
	) = 0;
	virtual ~IParentSelector() = default;
};

#endif
