#include "StringGenerator.h"
#include "StringSortTester.h"
#include "StringAlgos.h"
#include <fstream>
template<typename Comp>
void quickWrap(vector<string>& v,Comp cmp){sort(v.begin(),v.end(),cmp);}
template<typename Comp>
void mergeWrap(vector<string>& v,Comp cmp){stable_sort(v.begin(),v.end(),cmp);}
int main(){
    StringGenerator gen(42);
    StringSortTester tester(7);
    ofstream out("all_algos.csv");
    out<<"algo,type,n,time_ms,char_cmp\n";
    vector<pair<string,vector<string>>> pools{
            {"random",gen.randomPool()},
            {"reverse",gen.reversePool()},
            {"almost",gen.nearlySortedPool()}
    };
    auto rec=[&](const vector<string>& sample,const string& algo,const string& type,auto sorter){
        auto r=tester.measure(sample,sorter,algo,type);
        out<<r.algo<<','<<r.type<<','<<r.n<<','<<r.ms<<','<<r.cmp<<'\n';
    };
    for(auto& [kind,pool]:pools){
        for(int n=100;n<=3000;n+=100){
            vector<string> sample(pool.begin(),pool.begin()+n);
            rec(sample,"std::sort",kind,quickWrap<SymCmp>);
            rec(sample,"std::stable_sort",kind,mergeWrap<SymCmp>);
            rec(sample,"StringQS",kind,[](auto& v,auto){stringQS(v);});
            rec(sample,"StringMS",kind,[](auto& v,auto){stringMerge(v);});
            rec(sample,"MSD",kind,[](auto& v,auto){msdRadix(v);});
            rec(sample,"MSD+QS",kind,[](auto& v,auto){msdRadixQS(v);});
        }
    }
    return 0;
}
