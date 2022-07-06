#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <vector>

#include "gene.h"
#include "common/individual_representation.h"

/**
 * @brief Класс особи
 * @details Класс, содержащий информацию о конкретной особи, такую как:
 * * Гены особи
 * * Является ли особь допустимой (не должны выходить за границу ленты прямоугольники)
 * * Значение приспособленности данной особи (фитнес)
 * 
 * @note Каждая особь отвечает за какое-то размещение прямоугольников
 */
class Individual
{
public:
    /**
     * @brief Конструктор класса особи
     * 
     * @param genes Гены данной особи
     * @param rectangles Прямоугольники, которые необходимо разместить на ленте
     * @param tape_width Ширина ленты
     */
    Individual(
        const std::vector<Gene>& genes,
        const std::vector<std::pair<int, int>> rectangles,
        int tape_width
    );

    /**
     * @brief Метод получения количества генов особи
     * @return Количество генов у особи
     */
    int genes_count() const;
    /**
     * @brief Метод получения конкретного гена особи
     * 
     * @param gene_index Индекс гена, который нужно получить
     * @return Ген с запрошенным индексом
     * 
     * @throws std::out_of_range Выбрасывается в случае, когда индекс выходит за границы массива генов
     */
    const Gene& get_gene(int gene_index) const;
    /**
     * @brief Метод получения всех генов особи
     * @return Массив генов особи
     */
    const std::vector<Gene>& get_genes() const;

    /**
     * @brief Метод получения фитнеса особи
     * @return Значение фитнеса данной особи
     */
    float get_fitness() const;
    /**
     * @brief Метод проверки допустимости решения с данной расстановкой прямоугольников
     * @return Допустимо ли решение
     */
    bool is_feasible() const;

    /**
     * @brief Получение представления решения
     * @return Представление решения
     */
    const IndividualRepresentation& representation() const;
protected:
    /**
     * @brief Метод проверки допустимости решения
     * @details Проверяется, что все все прямоугольники, заданные генами
     * особи, лежат на ленте и не выходят за ее границы
     * 
     * @param rectangles Прямоугольники, располагаемые на ленте
     * @param tape_width Ширина ленты
     * 
     * @return Является ли решение допустимым
     */
    bool check_is_feasible(
        const std::vector<std::pair<int, int>> rectangles,
        int tape_width
    ) const;
    /**
     * @brief Метод вычисления фитнеса особи
     * @details На основе генов особи генерируется замощение ленты прямоугольниками:
     * Прямоугольники добавляются на ленту в порядке следования генов, отвечающих за них,
     * причем размещение происходит следующим образом:
     * * На ленте на максимальном значении Y с заданной геном координатой X размещается прямоугольник, 
     * за который отвечает данный ген (с учетом поворота)
     * * Прямоугольник смещается вниз, пока не достигнет другого прямоугольника либо низа ленты
     * * Прямоугольник сдвигается влево, пока не достигнет другого прямоугольника либо края ленты
     * После размещения всех прямоугольников на ленте оценивается длина использованной ленты,
     * значение фитнеса равняется 1 / длина использованной ленты
     * 
     * @param rectangles Прямоугольники, замощающие ленту
     * @param tape_width Ширина ленты
     * 
     * @return Значение фитнеса особи
     */
    float calculate_fitness(
        const std::vector<std::pair<int, int>> rectangles,
        int tape_width
    );

    /**
     * Флаг, является ли решение допустимым
     */
    bool is_feasible_;
    /**
     * Значение фитнеса особи
     */
    float fitness_;
    /**
     * Гены особи
     */
    std::vector<Gene> genes_;
    /**
      * Представление решения
      */
    IndividualRepresentation representation_;
};

#endif
