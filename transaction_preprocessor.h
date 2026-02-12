// ================ transaction_preprocessor.h ================
#ifndef TRANSACTION_PREPROCESSOR_H
#define TRANSACTION_PREPROCESSOR_H

#include <vector>

/**
 * Класс TransactionPreprocessor - подготовка транзакций к обработке
 *
 * Занимается очисткой и нормализацией входных данных:
 * 1. Удаление дубликатов товаров в одной транзакции
 * 2. Сортировка товаров для быстрого поиска
 */
class TransactionPreprocessor {
public:
    static void preprocess(std::vector<std::vector<int>>& transactions);
    static void removeEmpty(std::vector<std::vector<int>>& transactions);
};

#endif // TRANSACTION_PREPROCESSOR_H
