#include "genetic/individual.h"

#include <stdexcept>

Individual::Individual(
    const std::vector<Gene>& genes,
    const std::vector<std::pair<size_t, size_t>> rectangles,
    size_t tape_width
):
    fitness_{0},
    genes_{genes}
{
    is_feasible_ = check_is_feasible(rectangles, tape_width);
    if (is_feasible())
        fitness_ = calculate_fitness(rectangles, tape_width);
}


size_t Individual::genes_count() const
{
    return genes_.size();
}


const Gene& Individual::get_gene(size_t gene_index) const
{
    if (gene_index >= genes_count())
        throw std::out_of_range{"Gene index out of range"};

    return genes_.at(gene_index);
}


const std::vector<Gene>& Individual::get_genes() const
{
    return genes_;
}


float Individual::get_fitness() const
{
    return fitness_;
}


bool Individual::is_feasible() const
{
    return is_feasible_;
}


const IndividualRepresentation& Individual::representation() const
{
    return representation_;
}


bool Individual::check_is_feasible(
    const std::vector<std::pair<size_t, size_t>> rectangles,
    size_t tape_width
) const
{
    // Проверка особи на пригодность
    for (size_t i = 0; i < rectangles.size(); ++i)
    {
        // Получаем прямоугольник из гена
        int rect_index = get_gene(i).get_index();
        // Получаем ширину прямоугольника
        size_t rect_width = get_gene(i).get_rotation() ?
            rectangles.at(rect_index).second :
            rectangles.at(rect_index).first;
        // Если сумма координата прямоугольника и ширины больше ширины ленты, размещение невозможно
        if (rect_width + get_gene(i).get_coordinate() > tape_width)
            return false;
    }
    return true;
}


float Individual::calculate_fitness(
    const std::vector<std::pair<size_t, size_t>> rectangles,
    size_t tape_width
)
{
    // Создаем ленту
    std::vector<std::vector<size_t>> tape;

    // Проходим по всем генам и раскодируем решение
    for (size_t gene_index = 0; gene_index < rectangles.size(); ++gene_index)
    {
        // Получаем нужный ген
        const Gene& gene = get_gene(gene_index);
        // Получаем высоту и ширину прямоугольника, за который отвечает данный ген
        size_t rectangle_width = gene.get_rotation() ?
            rectangles.at(gene.get_index()).second :
            rectangles.at(gene.get_index()).first;
        size_t rectangle_height = gene.get_rotation() ?
            rectangles.at(gene.get_index()).first :
            rectangles.at(gene.get_index()).second;
        // Вычисляем минимальный y, где можно разместить прямоугольник на ленте
        int place_y = 0;
        int place_x = gene.get_coordinate();

        if (tape.size() != 0)
        {
            // Начинаем с верха ленты
            place_y = tape.size() - 1;
            bool can_move = true;
            while (place_y >= 0 && can_move)
            {
                // Уменьшаем минимальный y, пока не дойдем до начала ленты или не наткнемся на препятствие
                for (size_t x = place_x; x < place_x + rectangle_width; ++x)
                {
                    // Если данная строка уже содержит прямоугольник, минимальный y будет на 1 строку выше
                    if (tape.at(place_y).at(x) > 0)
                    {
                        ++place_y;
                        can_move = false;
                        break;
                    }
                }
                // Уменьшаем y
                if (can_move)
                    --place_y;
            }
            place_y = place_y > 0 ? place_y : 0;
        }
        // Расширяем ленту при необходимости
        size_t extension = place_y + rectangle_height - tape.size();
        for (size_t i = 0; i < extension; ++i)
            tape.emplace_back(tape_width, 0);

        bool can_move = true;
        while (place_x >= 0 && can_move)
        {
            // Уменьшаем минимальный x, пока не дойдем до левого края или не наткнемся на препятствие
            for (size_t y = place_y; y < place_y + rectangle_height; ++y)
            {
                if (tape.at(y).at(place_x) > 0)
                {
                    // Если данный стролбец уже содержит прямоугольник, минимальный x будет на 1 правее
                    ++place_x;
                    can_move = false;
                    break;
                }
            }
            // Уменьшаем x
            if (can_move)
                --place_x;
        }
        place_x = place_x > 0 ? place_x : 0;
        
        // Записываем прямоугольник на ленту
        for (size_t y = place_y; y < place_y + rectangle_height; ++y)
        {
            for (size_t x = place_x; x < place_x + rectangle_width; ++x)
                tape.at(y).at(x) = gene.get_index() + 1;
        }
        // Добавляем прямоугольник в представление решения
        representation_.add_rectangle(gene.get_index(), place_x, place_y, gene.get_rotation());
    }

    return 1.0 / tape.size();
}
