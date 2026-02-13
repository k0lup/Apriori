// ================ candidate_generator.cpp ================
#include "candidate_generator.h"

std::vector<std::vector<int>> CandidateGenerator::generate(
    const std::vector<Itemset>& frequent_itemsets) {

    std::vector<std::vector<int>> candidates;

    if (frequent_itemsets.empty()) {
        return candidates;
    }

    int k = frequent_itemsets[0].items.size();

    for (int i = 0; i < frequent_itemsets.size(); i++) {
        for (int j = i + 1; j < frequent_itemsets.size(); j++) {
            const auto& a = frequent_itemsets[i].items;
            const auto& b = frequent_itemsets[j].items;

            bool equal_prefix = true;
            for (int m = 0; m < k - 1; m++) {
                if (a[m] != b[m]) {
                    equal_prefix = false;
                    break;
                }
            }

            if (equal_prefix) {
                std::vector<int> candidate = a;
                candidate.push_back(b.back());
                candidates.push_back(candidate);
            }
        }
    }

    return candidates;
}

bool CandidateGenerator::isSubsetFrequent(const std::vector<int>& subset,
                                        const std::vector<Itemset>& frequent_itemsets) {
    for (const auto& freq_set : frequent_itemsets) {
        if (freq_set.items == subset) {
            return true;
        }
    }
    return false;
}

std::vector<std::vector<int>> CandidateGenerator::prune(
    const std::vector<std::vector<int>>& candidates,
    const std::vector<Itemset>& frequent_itemsets) {

    std::vector<std::vector<int>> valid_candidates;

    if (frequent_itemsets.empty()) {
        return valid_candidates;
    }

    int k = frequent_itemsets[0].items.size();

    for (const auto& candidate : candidates) {
        bool valid = true;

        for (int i = 0; i < candidate.size(); i++) {
            std::vector<int> subset = candidate;
            subset.erase(subset.begin() + i);

            if (!isSubsetFrequent(subset, frequent_itemsets)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            valid_candidates.push_back(candidate);
        }
    }

    return valid_candidates;
}
