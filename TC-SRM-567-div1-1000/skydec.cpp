#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int P=1000000009;
inline void add(int &a,int b){
    a+=b;if(a>=P)a-=P;
}
inline void dec(int &a,int b){
    a-=b;if(a<0)a+=P;
}
const int N=55;
int h[N];
bool see[N][N];
int n,m;
map<vector<int>,int>f[12];
int dfs(int x,vector<int>now){
    //采用搜索的方法计算答案，可以证明复杂度是O(2^n)的
    if(x==0)return 1;
    //用map记忆化，把整个状态用vector存进去
    if(f[x].find(now)!=f[x].end())return f[x][now];
    int ans=0;
    rep(i,1,m){
        //暴力枚举
        bool ok=1;
        rep(j,1,m)ok&=((max(0,h[x]-abs(i-j))>now[j-1])==see[x][j]);
        //可以证明这里ok=1的选项最多只有2个
        if(!ok)continue;
        vector<int> dj=now;
        rep(j,1,m)dj[j-1]=max(dj[j-1],h[x]-abs(i-j));
        add(ans,dfs(x-1,dj));
    }
    //返回答案
    return f[x][now]=ans;
}
int Main(){
    vector<int>s;s.clear();
    rep(i,1,m)s.push_back(0);
    //采用搜索的方法
    return dfs(n,s);
}
class Mountains{
public:
    int countPlacements(vector <int> heights, vector <string> vis){
        //预处理
        n=heights.size();
        rep(i,1,n)h[i]=heights[i-1];
        m=vis[0].size();
        rep(i,1,n)rep(j,1,m)see[i][j]=(vis[i-1][j-1]=='X');
        return Main();
    }
};