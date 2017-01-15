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
int head[N],np[N],p[N],need[N],init[N],tot;
int n;
int du[N];
int fa[N];
int get(int x){
    if(x==fa[x])return x;
    return fa[x]=get(fa[x]);
}
int Main(){
    rep(i,1,n)fa[i]=i;
    rep(i,1,n)for(int u=head[i];u;u=np[u])if(!need[u]){
        fa[get(i)]=get(p[u]);
    }


    rep(i,1,n)for(int u=head[i];u;u=np[u])if(need[u]){
        if(init[u]==0){
            du[get(p[u])]^=1;
            du[get(i)]^=1;
        }
    }
    int ans=0;
    rep(i,1,n)if(du[i])ans++;
    return ans/2;
}
class TurnOnLamps{
public:
    int minimize(vector<int> roads,string S,string T){
        n=roads.size()+1;
        rep(i,1,n-1){
            int a=roads[i-1]+1;int b=i+1;
            ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;
            need[tot]=T[i-1]-'0';
            init[tot]=S[i-1]-'0';
        }
        return Main();
    }
};