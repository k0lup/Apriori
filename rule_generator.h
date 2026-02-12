// ================ rule_generator.h ================
#ifndef RULE_GENERATOR_H
#define RULE_GENERATOR_H

#include "itemset.h"
#include <vector>

/**
 * Структура AssociationRule - правило ассоциации A → B
 */
struct AssociationRule {
    std::vector<int> antecedent;
    std::vector<int> consequent;
    double confidence;
    int support;

    bool operator<(const AssociationRule& other) const;
};

/**
 * Класс RuleGenerator - генерация правил ассоциации из частых наборов
 */
class RuleGenerator {
private:
    const std::vector<std::vector<Itemset>>& frequent_itemsets;
    double min_confidence;
    int total_transactions;

    int findSupport(const std::vector<int>& itemset) const;
    void generateRulesFromItemset(
        const Itemset& itemset,
        std::vector<int>& antecedent,
        int start,
        std::vector<AssociationRule>& rules) const;

public:
    RuleGenerator(
        const std::vector<std::vector<Itemset>>& freq_itemsets,
        double min_conf,
        int total_trans);

    std::vector<AssociationRule> generateAllRules() const;
    void printRules() const;
};

#endif // RULE_GENERATOR_H
