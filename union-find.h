//
// Created by 14667 on 2018/2/25.
//

#ifndef LIST_UNION_FIND_H
#define LIST_UNION_FIND_H

class UnionFind {
public:
    UnionFind(int size) {
        father_.resize(size, -1);
        rank_.resize(size, 0);
    }

    void Union(int x, int y) {
        int fx = Find(x);
        int fy = Find(y);
        if (fx == fy) {
            return;;
        }
        if (rank_[fx] < rank_[fy]) {
            father_[fx] = fy;
        } else {
            father_[fy] = fx;
            if (rank_[fx] == rank_[fy]) {
                ++rank_[fx];
            }
        }
    }

    int Find(int x) {
        if (father_[x] == -1) {
            return x;
        }
        return father_[x] = Find(father_[x]);
    }

private:
    std::vector<int> father_;
    std::vector<int> rank_;
};

#endif //LIST_UNION_FIND_H
