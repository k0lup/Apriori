// ================ main.cpp ================
#include "apriori.h"
#include "rule_generator.h"
#include <iostream>

int main() {
    std::vector<std::vector<int>> transactions = {
        {1, 2, 3},
        {1, 4},
        {1, 2, 4},
        {2, 3},
        {1, 2, 3, 4}
    };

    std::cout << "========================================\n";
    std::cout << "      АЛГОРИТМ APRIORI НА C++\n";
    std::cout << "========================================\n\n";

    std::cout << "Исходные транзакции:\n";
    for (int i = 0; i < transactions.size(); i++) {
        std::cout << "Чек " << i + 1 << ": {";
        for (int j = 0; j < transactions[i].size(); j++) {
            std::cout << transactions[i][j];
            if (j < transactions[i].size() - 1) std::cout << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "\n";

    int min_support = 3;
    double min_confidence = 0.7;

    std::cout << "Параметры:\n";
    std::cout << "  Минимальная поддержка: " << min_support
              << " транзакций\n";
    std::cout << "  Минимальная достоверность: " << min_confidence * 100 << "%\n\n";

    std::cout << "--------- ЗАПУСК APRIORI ---------\n\n";

    Apriori apriori(transactions, min_support);
    apriori.run();
    apriori.printResults();

    std::cout << "\n--------- ГЕНЕРАЦИЯ ПРАВИЛ ---------\n";

    RuleGenerator rule_gen(
        apriori.getResults(),
        min_confidence,
        transactions.size()
    );
    rule_gen.printRules();

    std::cout << "\n========================================\n";
    std::cout << "            РАБОТА ЗАВЕРШЕНА\n";
    std::cout << "========================================\n";

    return 0;
}
