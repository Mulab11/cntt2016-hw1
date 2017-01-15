#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
bitset<N> a[N];
bitset<N> b[N];
int val[N];
int n,m;
int ans=-1;
int id[N];
int reid[N];
inline bool cmp(int x,int y){return val[x]>val[y];}
void dfs(int x,bitset<N> can,int s,int sum){
    //dfs爆搜
    //如果点数已经不够了则剪枝剪掉
    if(s+can.count()<m)return;

    //点数够了更新答案
    if(s>=m){
        ans=max(ans,sum);
    }
    if(x==n+1)return;
    int rs=0;

    //rs估计后面的全选的答案
    rep(i,x,n)if(can[i])rs+=val[i];
    
    //最优性剪枝
    if(rs+sum<=ans)return;

    if(!can[x]){
        dfs(x+1,can,s,sum);
        return;
    } 

    dfs(x+1,can&a[x],s+1,sum+val[x]);
    
    bitset<N>gt=can;gt[x]=0;
    dfs(x+1,gt,s,sum);
}
int Main(){
    while(3*m<2*n)m++;

    rep(i,1,n)id[i]=i;
    //按val大小排序，并重编号
    sort(id+1,id+1+n,cmp);
    rep(i,1,n)reid[id[i]]=i;
    rep(i,1,n)b[i]=a[i];
    rep(i,1,n)a[i].reset();
    rep(i,1,n)rep(j,1,n)a[reid[i]][reid[j]]=b[i][j];
    sort(val+1,val+1+n);
    reverse(val+1,val+1+n);

    //开一个bitset记录哪些点可以加入
    bitset<N> pre;pre.reset();
    rep(i,1,n)if(a[i].count()+1>=m)pre[i]=1;
    dfs(1,pre,0,0);
    return ans;
}
class MagicMolecule{
public:
    int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
        //预处理
        n=magicPower.size();
        rep(i,1,n)::val[i]=magicPower[i-1];
        rep(i,1,n)rep(j,1,n)if(magicBond[i-1][j-1]=='Y')a[i][j]=1;
        return Main();
    }
}gt;

