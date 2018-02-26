#include "trie.h"

int main() {
    Trie trie;
    trie.insert("leet");
    trie.insert("leetcode");
    trie.search("leet");
    trie.search("lett");
    trie.startsWith("leet");
}