// ================ support_calculator.cpp ================
#include "support_calculator.h"

SupportCalculator::SupportCalculator(const std::vector<std::vector<int>>& trans)
    : transactions(trans) {}

bool SupportCalculator::contains(const std::vector<int>& transaction,
                                const std::vector<int>& itemset) {
    int i = 0, j = 0;

    while (i < transaction.size() && j < itemset.size()) {
        if (transaction[i] == itemset[j]) {
            i++;
            j++;
        } else if (transaction[i] < itemset[j]) {
            i++;
        } else {
            return false;
        }
    }

    return j == itemset.size();
}

int SupportCalculator::countSupportForItemset(const std::vector<int>& candidate) const {
    int count = 0;

    for (const auto& transaction : transactions) {
        if (contains(transaction, candidate)) {
            count++;
        }
    }

    return count;
}

std::vector<Itemset> SupportCalculator::findFrequentItemsets(
    const std::vector<std::vector<int>>& candidates,
    int min_support) const {

    std::vector<Itemset> frequent_itemsets;

    for (const auto& candidate : candidates) {
        int support = countSupportForItemset(candidate);

        if (support >= min_support) {
            frequent_itemsets.push_back({candidate, support});
        }
    }

    return frequent_itemsets;
}
