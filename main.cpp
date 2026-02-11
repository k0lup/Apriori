#include <iostream>

#include <vector>
#include <map>
#include <string>

void aprioriAlg(const std::vector<std::vector<int>>& transactions, int minimum) {
    std::vector<std::vector<int>> results;

    for (int i = 0; i < transactions.size(); ++i) {
        std::vector<int> temp_result;
        for (int j = 0; j < transactions.size(); ++j) {
            std::map<int, int> count;
            for (int k = 0; k < transactions[j].size(); ++k) {
                if (count.find(transactions[j][k]) == count.end()) {
                    count.insert(transactions[j][k], 1);
                } else {
                    count[transactions[j][k]]++;
                }
            }
            for (const auto& pair : count) {
                if (pair.second >= minimum) {
                    temp_result.push_back(pair.first);
                }
            }
        }
        results.push_back(temp_result);
    }
}

int main(int argc, char** argv) {

    std::vector<std::vector<int>> transactions;

    return 0;
}
