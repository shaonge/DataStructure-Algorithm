//
// Created by 14667 on 2018/2/25.
//

#ifndef LIST_STRING_PATTERN_MATCHING_H
#define LIST_STRING_PATTERN_MATCHING_H

#include <string>

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
    next[0] = -1;
    for (int i = 1; i < pattern.size(); ++i) {
        if (pattern[i] != pattern[0]) {
            
        }
    }
}

static int KMP(const std::string& str, const std::string& pattern) {

}

#endif //LIST_STRING_PATTERN_MATCHING_H
