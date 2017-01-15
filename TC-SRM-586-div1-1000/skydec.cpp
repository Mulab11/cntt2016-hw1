#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int A=27;
const int N=55;
int f[N][A][A];
bool vis[N][A][A];
int L[N];
int n;
int dfs(int i,int rest,int have){
    if(i==n+1){
        if(have==0)return 0;
        return 1e7;
    }
    if(vis[i][rest][have])return f[i][rest][have];
    int val=(1e9);
    int m=26;if(L[i]<m)m=L[i];
    int s=0;rep(j,1,i-1)s+=L[j];
    for(int only=0;only<=rest;only++)
    for(int fr=0;fr<=rest-only&&fr<=m-only;fr++)
    for(int last=0;last<=have&&last<=m-only-fr;last++){
        int mid=m-only-fr-last;
        if(mid+last>have)continue;
        
        int ret=-s*fr;
        ret-=((2*L[i]-fr+1)*fr)/2;
        ret+=last*s;
        ret+=((last+1)*last)/2;
        if(!mid){
            ret+=(L[i]-last-fr-only);
        }
        ret+=dfs(i+1,rest-only-fr,have-last+fr);
        if(ret<val)val=ret;
    }
    vis[i][rest][have]=1;
    return f[i][rest][have]=val;
}
class StringWeight{
    public:
    int getMinimum(vector<int> _L){
        n=_L.size();
        rep(i,1,n)L[i]=_L[i-1];
        return dfs(1,26,0);
    }
}gt;