// ================ support_calculator.h ================
#ifndef SUPPORT_CALCULATOR_H
#define SUPPORT_CALCULATOR_H

#include "itemset.h"
#include <vector>

/**
 * Класс SupportCalculator - подсчет поддержки кандидатов
 */
class SupportCalculator {
private:
    const std::vector<std::vector<int>>& transactions;

public:
    SupportCalculator(const std::vector<std::vector<int>>& trans);

    static bool contains(const std::vector<int>& transaction,
                        const std::vector<int>& itemset);

    int countSupportForItemset(const std::vector<int>& candidate) const;

    std::vector<Itemset> findFrequentItemsets(
        const std::vector<std::vector<int>>& candidates,
        int min_support) const;
};

#endif // SUPPORT_CALCULATOR_H
