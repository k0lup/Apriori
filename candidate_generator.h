// ================ candidate_generator.h ================
#ifndef CANDIDATE_GENERATOR_H
#define CANDIDATE_GENERATOR_H

#include "itemset.h"
#include <vector>

/**
 * Класс CandidateGenerator - генерация кандидатов из частых наборов
 *
 * Реализует ключевую идею Apriori:
 * НОВЫЕ НАБОРЫ СОЗДАЮТСЯ ТОЛЬКО ИЗ ЧАСТЫХ НАБОРОВ!
 */
class CandidateGenerator {
public:
    static std::vector<std::vector<int>> generate(
        const std::vector<Itemset>& frequent_itemsets);

    static bool isSubsetFrequent(const std::vector<int>& subset,
                                const std::vector<Itemset>& frequent_itemsets);

    static std::vector<std::vector<int>> prune(
        const std::vector<std::vector<int>>& candidates,
        const std::vector<Itemset>& frequent_itemsets);
};

#endif // CANDIDATE_GENERATOR_H
