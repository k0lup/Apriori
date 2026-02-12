// ================ apriori.h ================
#ifndef APRIORI_H
#define APRIORI_H

#include "itemset.h"
#include <vector>

/**
 * Класс Apriori - главный класс алгоритма
 */
class Apriori {
private:
    std::vector<std::vector<int>> transactions;
    int min_support;
    std::vector<std::vector<Itemset>> all_frequent_itemsets;

    std::vector<Itemset> findFrequent1Itemsets();

public:
    Apriori(const std::vector<std::vector<int>>& trans, int min_sup);

    void run();
    void printResults() const;
    const std::vector<std::vector<Itemset>>& getResults() const;
};

#endif // APRIORI_H
