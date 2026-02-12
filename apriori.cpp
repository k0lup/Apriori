// ================ apriori.cpp ================
#include "apriori.h"
#include "transaction_preprocessor.h"
#include "candidate_generator.h"
#include "support_calculator.h"
#include <iostream>
#include <map>

Apriori::Apriori(const std::vector<std::vector<int>>& trans, int min_sup)
    : transactions(trans), min_support(min_sup) {}

std::vector<Itemset> Apriori::findFrequent1Itemsets() {
    std::map<int, int> count_map;

    for (const auto& trans : transactions) {
        for (int item : trans) {
            count_map[item]++;
        }
    }

    std::vector<Itemset> frequent1;
    for (const auto& pair : count_map) {
        if (pair.second >= min_support) {
            frequent1.push_back({{pair.first}, pair.second});
        }
    }

    return frequent1;
}

void Apriori::run() {
    // Шаг 0: Подготовка данных
    TransactionPreprocessor::preprocess(transactions);
    TransactionPreprocessor::removeEmpty(transactions);

    // Шаг 1: L₁
    auto L1 = findFrequent1Itemsets();
    if (L1.empty()) {
        std::cout << "Нет частых наборов при min_support = "
                  << min_support << std::endl;
        return;
    }
    all_frequent_itemsets.push_back(L1);

    // Шаг 2: Основной цикл
    int k = 1;
    while (!all_frequent_itemsets[k-1].empty()) {
        std::cout << "Итерация k=" << k
                  << ", L_" << k << " содержит "
                  << all_frequent_itemsets[k-1].size()
                  << " наборов" << std::endl;

        auto candidates = CandidateGenerator::generate(all_frequent_itemsets[k-1]);

        if (candidates.empty()) {
            std::cout << "Не удалось сгенерировать кандидатов C_"
                      << k+1 << std::endl;
            break;
        }

        auto valid_candidates = CandidateGenerator::prune(
            candidates, all_frequent_itemsets[k-1]);

        if (valid_candidates.empty()) {
            std::cout << "После pruning не осталось кандидатов C_"
                      << k+1 << std::endl;
            break;
        }

        SupportCalculator calculator(transactions);
        auto L_next = calculator.findFrequentItemsets(valid_candidates, min_support);

        if (!L_next.empty()) {
            all_frequent_itemsets.push_back(L_next);
            std::cout << "Найдено L_" << k+1 << ": "
                      << L_next.size() << " наборов" << std::endl;
        } else {
            std::cout << "Нет частых наборов размера " << k+1 << std::endl;
            break;
        }

        k++;
    }

    std::cout << "Алгоритм завершен. Найдено уровней: "
              << all_frequent_itemsets.size() << std::endl;
}

void Apriori::printResults() const {
    std::cout << "\n========== ЧАСТЫЕ НАБОРЫ ТОВАРОВ ==========\n";
    std::cout << "Минимальная поддержка: " << min_support
              << " транзакций\n";
    std::cout << "Всего транзакций: " << transactions.size() << "\n";
    std::cout << "============================================\n";

    for (int k = 0; k < all_frequent_itemsets.size(); k++) {
        std::cout << "\n--- L" << k + 1 << " (размер " << k + 1 << ") ---\n";
        std::cout << "Найдено наборов: " << all_frequent_itemsets[k].size() << "\n";
        std::cout << "----------------------------------------\n";

        for (const auto& itemset : all_frequent_itemsets[k]) {
            std::cout << "{";
            for (int i = 0; i < itemset.items.size(); i++) {
                std::cout << itemset.items[i];
                if (i < itemset.items.size() - 1) std::cout << ", ";
            }
            std::cout << "} поддержка: " << itemset.support
                     << " (" << (100.0 * itemset.support / transactions.size())
                     << "%)\n";
        }
    }
}

const std::vector<std::vector<Itemset>>& Apriori::getResults() const {
    return all_frequent_itemsets;
}
