// ================ transaction_preprocessor.cpp ================
#include "transaction_preprocessor.h"
#include <algorithm>

void TransactionPreprocessor::preprocess(std::vector<std::vector<int>>& transactions) {
    for (auto& transaction : transactions) {
        std::sort(transaction.begin(), transaction.end());
        transaction.erase(
            std::unique(transaction.begin(), transaction.end()),
            transaction.end()
        );
    }
}

void TransactionPreprocessor::removeEmpty(std::vector<std::vector<int>>& transactions) {
    transactions.erase(
        std::remove_if(transactions.begin(), transactions.end(),
            [](const std::vector<int>& t) { return t.empty(); }),
        transactions.end()
    );
}
