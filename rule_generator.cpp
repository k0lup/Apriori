// ================ rule_generator.cpp ================
#include "rule_generator.h"
#include "support_calculator.h"
#include <algorithm>
#include <iostream>

bool AssociationRule::operator<(const AssociationRule& other) const {
    return confidence > other.confidence;
}

RuleGenerator::RuleGenerator(
    const std::vector<std::vector<Itemset>>& freq_itemsets,
    double min_conf,
    int total_trans)
    : frequent_itemsets(freq_itemsets)
    , min_confidence(min_conf)
    , total_transactions(total_trans) {}

int RuleGenerator::findSupport(const std::vector<int>& itemset) const {
    for (const auto& level : frequent_itemsets) {
        for (const auto& set : level) {
            if (set.items == itemset) {
                return set.support;
            }
        }
    }
    return 0;
}

void RuleGenerator::generateRulesFromItemset(
    const Itemset& itemset,
    std::vector<int>& antecedent,
    int start,
    std::vector<AssociationRule>& rules) const {

    if (!antecedent.empty() && antecedent.size() < itemset.items.size()) {
        std::vector<int> consequent;
        for (int item : itemset.items) {
            if (std::find(antecedent.begin(), antecedent.end(), item)
                == antecedent.end()) {
                consequent.push_back(item);
            }
        }

        int support_union = itemset.support;
        int support_antecedent = findSupport(antecedent);

        if (support_antecedent > 0) {
            double confidence = static_cast<double>(support_union)
                              / support_antecedent;

            if (confidence >= min_confidence) {
                rules.push_back({antecedent, consequent, confidence, support_union});
            }
        }
    }

    for (int i = start; i < itemset.items.size(); i++) {
        antecedent.push_back(itemset.items[i]);
        generateRulesFromItemset(itemset, antecedent, i + 1, rules);
        antecedent.pop_back();
    }
}

std::vector<AssociationRule> RuleGenerator::generateAllRules() const {
    std::vector<AssociationRule> all_rules;

    for (int k = 1; k < frequent_itemsets.size(); k++) {
        for (const auto& itemset : frequent_itemsets[k]) {
            std::vector<int> antecedent;
            generateRulesFromItemset(itemset, antecedent, 0, all_rules);
        }
    }

    std::sort(all_rules.begin(), all_rules.end());
    return all_rules;
}

void RuleGenerator::printRules() const {
    auto rules = generateAllRules();

    std::cout << "\n========== ПРАВИЛА АССОЦИАЦИИ ==========\n";
    std::cout << "Минимальная достоверность: " << min_confidence * 100 << "%\n";
    std::cout << "Всего найдено правил: " << rules.size() << "\n";
    std::cout << "========================================\n\n";

    for (const auto& rule : rules) {
        std::cout << "{";
        for (int i = 0; i < rule.antecedent.size(); i++) {
            std::cout << rule.antecedent[i];
            if (i < rule.antecedent.size() - 1) std::cout << ", ";
        }
        std::cout << "} -> {";

        for (int i = 0; i < rule.consequent.size(); i++) {
            std::cout << rule.consequent[i];
            if (i < rule.consequent.size() - 1) std::cout << ", ";
        }

        std::cout << "}  ";
        std::cout << "достоверность: " << rule.confidence * 100 << "%, ";
        std::cout << "поддержка: " << rule.support << "/"
                 << total_transactions << " (";
        std::cout << (100.0 * rule.support / total_transactions) << "%)";
        std::cout << "\n";
    }
}
