#include "StringGenerator.h"
#include "StringSortTester.h"
#include <fstream>
#include <algorithm>
#include <chrono>

template<typename Comp>
void quick(vector<string>& v, Comp cmp) { sort(v.begin(), v.end(), cmp); }

template<typename Comp>
void merge(vector<string>& v, Comp cmp) { stable_sort(v.begin(), v.end(), cmp); }

int main() {
    StringGenerator gen(42);
    StringSortTester tester(7);

    ofstream out("baseline.csv");
    out << "algo,type,n,time_ms,char_cmp\n";

    vector<pair<string, vector<string>>> pools{
            {"random",  gen.randomPool()},
            {"reverse", gen.reversePool()},
            {"almost",  gen.nearlySortedPool()}
    };

    for (auto& [kind, pool] : pools) {
        for (int n = 100; n <= 3000; n += 100) {
            vector<string> sample(pool.begin(), pool.begin() + n);

            auto r1 = tester.measure(sample,
                        quick<SymCmp>,  "std::sort",        kind);
            auto r2 = tester.measure(sample,
                        merge<SymCmp>,  "std::stable_sort", kind);

            out << r1.algo << ',' << r1.type << ',' << r1.n << ','
                << r1.ms   << ',' << r1.cmp  << '\n';
            out << r2.algo << ',' << r2.type << ',' << r2.n << ','
                << r2.ms   << ',' << r2.cmp  << '\n';
        }
    }
    return 0;
}
