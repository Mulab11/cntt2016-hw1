#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=55;
string a[N];
inline bool cmp(const string &a,const string &b){
    //字符串排序
    int l=min(a.size(),b.size());
    rep(i,0,l-1)if(a[i]!=b[i])return a[i]<b[i];
    return a.size()<b.size();
}
inline int lcp(const string &a,const string &b){
    //求两个字符串的lcp
    int l=min(a.size(),b.size());
    rep(i,0,l-1)if(a[i]!=b[i])return i;
    return l;
}
int n;
int Main(){
    int ans=a[1].size()+1;
    rep(i,2,n){
        int dj=0;
        //贪心计算答案，每次找一个和当前lcp最大的历史版本，然后通过它计算出答案
        rep(j,1,i-1)if(lcp(a[j],a[i])>dj)dj=lcp(a[j],a[i]);

        int ret=2+a[i].size()-dj+1;
        //特判完全相同的情况
        if(lcp(a[i-1],a[i])==a[i-1].size())
        ret=min(ret,(int)(a[i].size()-a[i-1].size()+1));
        ans+=ret;
    }   
    return ans;
}
class UndoHistory{
public:
    int minPresses(vector <string> lines){
        //预处理
        n=lines.size();
        rep(i,1,n){
            a[i]=lines[i-1];
        }
        return Main();
    }
};



