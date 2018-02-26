//
// Created by 14667 on 2018/2/25.
//

#ifndef LIST_STRING_PATTERN_MATCHING_H
#define LIST_STRING_PATTERN_MATCHING_H

#include <string>
#include <vector>

static int BruteForce(const std::string& str, const std::string& pattern) {
    int end = str.size() - pattern.size();
    for (int i = 0; i <= end; ++i) {
        int j = 0, k = i;
        for (; j < pattern.size() && str[k] == pattern[j]; ++j, ++k) {}
        if (j == pattern.size()) {
            return i;
        }
    }
    return -1;
}

static void _next(std::vector<int>& next, const std::string& pattern) {
    if (pattern.empty()) {
        return;
    }
    next.resize(pattern.size());
    next[0] = -1;
    for(int i = 1; i < pattern.size(); ++i) {
        int j = next[i - 1];
        while (j != -1 && pattern[j] != pattern[i - 1]) {
            j = next[j];
        }
        next[i] = j + 1;
    }
}

static int KnuthMorrisPratt(const std::string& str, const std::string& pattern) {
    std::vector<int> next;
    _next(next, pattern);
    int end = str.size() - pattern.size();
    for (int i = 0; i <= end; ) {
        int j = 0, k = i;
        for (; j < pattern.size() && str[k] == pattern[j]; ++j, ++k) {}
        if (j == pattern.size()) {
            return i;
        } else {
            i = k - next[j];
        }
    }

    return -1;
}

static int Sunday(const std::string& str, const std::string& pattern) {
    std::vector<int> back(256, -1);
    for (int i = 0; i < pattern.size(); ++i) {
        back[pattern[i]] = i;
    }

    int end = str.size() - pattern.size();
    for (int i = 0; i <= end; ) {
        int j = 0, k = i;
        for (; j < pattern.size() && str[k] == pattern[j]; ++j, ++k) {}
        if (j == pattern.size()) {
            return i;
        }
        auto m = i + pattern.size();
        if (m == str.size()) {
            return -1;
        }
        i = m - back[str[m]];
    }

    return -1;
}

static int BoyerMoore(const std::string& str, const std::string& pattern) {

}

#endif //LIST_STRING_PATTERN_MATCHING_H
