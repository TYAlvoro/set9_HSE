#pragma once
#include <chrono>
#include <algorithm>
#include <numeric>
#include <limits>

using namespace std;

struct Result {
    string algo, type;
    int    n;
    double ms;
    size_t cmp;
};

inline size_t gCmp = 0;

struct SymCmp {
    bool operator()(const string& a, const string& b) const {
        size_t i = 0, m = min(a.size(), b.size());
        for (; i < m; ++i) {
            ++gCmp;
            if (a[i] != b[i]) return a[i] < b[i];
        }
        ++gCmp;
        return a.size() < b.size();
    }
};

class StringSortTester {
    int reps;
public:
    explicit StringSortTester(int r = 5) : reps(r) {}

    template<class SortFun>
    Result measure(const vector<string>& src,
                   SortFun sorter,
                   const string& name,
                   const string& type)
    {
        double tSum = 0;
        size_t cSum = 0;
        for (int i = 0; i < reps; ++i) {
            auto v = src;
            gCmp = 0;
            auto t0 = chrono::high_resolution_clock::now();
            sorter(v, SymCmp{});
            auto t1 = chrono::high_resolution_clock::now();
            tSum += chrono::duration<double, milli>(t1 - t0).count();
            cSum += gCmp;
        }
        return {name, type, (int)src.size(), tSum / reps, cSum / reps};
    }
};
