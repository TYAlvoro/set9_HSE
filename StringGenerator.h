#pragma once
#include <iostream>
#include <random>
#include <string>

using namespace std;

class StringGenerator {
    static inline const string ALPHABET =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789"
        "!@#%:;^&*()-.";
    mt19937_64 rng;
    uniform_int_distribution<int> lenDist{10, 200};
    uniform_int_distribution<int> charDist{0, 73};

    string randomString() {
        int len = lenDist(rng);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) s.push_back(ALPHABET[charDist(rng)]);
        return s;
    }

public:
    explicit StringGenerator(uint64_t seed = random_device{}()) : rng(seed) {}

    vector<string> randomPool(size_t n = 3000) {
        vector<string> v(n);
        for (auto& s : v) s = randomString();
        return v;
    }

    vector<string> reversePool(size_t n = 3000) {
        auto v = randomPool(n);
        sort(v.begin(), v.end());
        reverse(v.begin(), v.end());
        return v;
    }

    vector<string> nearlySortedPool(size_t n = 3000, double perc = 5.0) {
        auto v = randomPool(n);
        sort(v.begin(), v.end());
        uniform_int_distribution<int> idx(0, (int)n - 1);
        size_t swaps = size_t(n * perc / 100.0);
        for (size_t i = 0; i < swaps; ++i) swap(v[idx(rng)], v[idx(rng)]);
        return v;
    }

    vector<string> commonPrefixPool(size_t n = 3000, size_t pLen = 20) {
        string pref;
        pref.reserve(pLen);
        for (size_t i = 0; i < pLen; ++i) pref.push_back(ALPHABET[charDist(rng)]);
        vector<string> v(n);
        for (auto& s : v) s = pref + randomString();
        return v;
    }
};
