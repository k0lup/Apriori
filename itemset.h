// ================ itemset.h ================
#ifndef ITEMSET_H
#define ITEMSET_H

#include <vector>
#include <algorithm>

/**
 * Структура Itemset - представляет набор товаров и его поддержку
 *
 * Это основная единица данных в алгоритме Apriori.
 * Хранит отсортированный вектор товаров и количество транзакций,
 * в которых этот набор встречается.
 */
struct Itemset {
    std::vector<int> items;     // товары в наборе (всегда отсортированы!)
    int support;                // сколько транзакций содержат этот набор

    /**
     * Оператор сравнения для возможности сортировки и поиска
     * Сравниваем сначала по размеру, потом по содержимому
     */
    bool operator<(const Itemset& other) const {
        if (items.size() != other.items.size())
            return items.size() < other.items.size();
        return items < other.items;
    }

    /**
     * Оператор равенства для поиска наборов
     */
    bool operator==(const Itemset& other) const {
        return items == other.items;
    }
};

#endif // ITEMSET_H
