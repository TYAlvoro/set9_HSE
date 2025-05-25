#pragma once
#include <vector>
#include <string>
using namespace std;
extern size_t gCmp;
inline bool charLess(int a,int b){++gCmp;return a<b;}
inline bool charGreater(int a,int b){++gCmp;return a>b;}
inline int charAt(const string& s,int d){return d<(int)s.size()?(unsigned char)s[d]:-1;}
void stringQSRec(vector<string>& a,int l,int r,int d){
    if(r-l<=1) return;
    int lt=l,gt=r-1,v=charAt(a[l],d),i=l+1;
    while(i<=gt){
        int t=charAt(a[i],d);
        if(charLess(t,v)) swap(a[lt++],a[i++]);
        else if(charGreater(t,v)) swap(a[i],a[gt--]);
        else ++i;
    }
    stringQSRec(a,l,lt,d);
    if(v>=0) stringQSRec(a,lt,gt+1,d+1);
    stringQSRec(a,gt+1,r,d);
}
inline void stringQS(vector<string>& v,int l,int r,int d){stringQSRec(v,l,r,d);}
inline void stringQS(vector<string>& v){stringQSRec(v,0,(int)v.size(),0);}
struct LcpCmp{
    const string* A=nullptr;const string* B=nullptr;int lcp=0;
    bool operator()(const string& a,const string& b){
        int i=0;
        if(&a==A&&&b==B) i=lcp;else{A=&a;B=&b;lcp=0;}
        for(;i<(int)a.size()&&i<(int)b.size();++i){++gCmp;if(a[i]!=b[i]){lcp=i;return a[i]<b[i];}}
        ++gCmp;
        lcp=i;
        return a.size()<b.size();
    }
};
void mergeRec(vector<string>& a,vector<string>& buf,int l,int r,LcpCmp& cmp){
    if(r-l<=1) return;
    int m=(l+r)>>1;
    mergeRec(a,buf,l,m,cmp);
    mergeRec(a,buf,m,r,cmp);
    int i=l,j=m,k=l;
    while(i<m&&j<r){
        if(cmp(a[i],a[j])) buf[k++]=move(a[i++]); else buf[k++]=move(a[j++]);
    }
    while(i<m) buf[k++]=move(a[i++]);
    while(j<r) buf[k++]=move(a[j++]);
    move(buf.begin()+l,buf.begin()+r,a.begin()+l);
}
inline void stringMerge(vector<string>& v){
    vector<string> buf(v.size());
    LcpCmp cmp;
    mergeRec(v,buf,0,(int)v.size(),cmp);
}
const int R=128;
inline int chr(const string& s,int d){return d<(int)s.size()?(unsigned char)s[d]:-1;}
void msdRec(vector<string>& a,vector<string>& aux,int l,int r,int d){
    if(r-l<=1) return;
    int cnt[R+2]={0};
    for(int i=l;i<r;++i) ++cnt[chr(a[i],d)+2];
    for(int i=1;i<R+2;++i) cnt[i]+=cnt[i-1];
    for(int i=l;i<r;++i) aux[l+cnt[chr(a[i],d)+1]++]=move(a[i]);
    for(int i=l;i<r;++i) a[i]=move(aux[i]);
    int start=l;
    for(int c=0;c<=R;++c){
        int end=l+cnt[c+1];
        if(end-start>1&&c) msdRec(a,aux,start,end,d+1);
        start=end;
    }
}
inline void msdRadix(vector<string>& v){
    vector<string> aux(v.size());
    msdRec(v,aux,0,(int)v.size(),0);
}
void msdRecQS(vector<string>& a,vector<string>& aux,int l,int r,int d){
    if(r-l<=1) return;
    if(r-l<74){stringQS(a,l,r,d);return;}
    int cnt[R+2]={0};
    for(int i=l;i<r;++i) ++cnt[chr(a[i],d)+2];
    for(int i=1;i<R+2;++i) cnt[i]+=cnt[i-1];
    for(int i=l;i<r;++i) aux[l+cnt[chr(a[i],d)+1]++]=move(a[i]);
    for(int i=l;i<r;++i) a[i]=move(aux[i]);
    int start=l;
    for(int c=0;c<=R;++c){
        int end=l+cnt[c+1];
        if(end-start>1&&c) msdRecQS(a,aux,start,end,d+1);
        start=end;
    }
}
inline void msdRadixQS(vector<string>& v){
    vector<string> aux(v.size());
    msdRecQS(v,aux,0,(int)v.size(),0);
}
