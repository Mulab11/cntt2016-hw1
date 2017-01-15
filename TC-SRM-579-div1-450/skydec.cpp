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
int n,m;
int w[N][N];
int st[N],ed[N],ti[N];
void split(string d,int &a,int &b,int &c){
    //将一个形如"a b c"的字符串分裂成数a b c
    a=b=c=0;
    int now=0;
    int cnt=0;
    rep(i,0,d.size()-1){
        if(d[i]==' '){
            if(cnt==0)a=now;
            else if(cnt==1)b=now;
            else c=now;
            ++cnt;
            now=0;
        }
        else{
            now=now*10+(d[i]-'0');
        }
    }
    c=now;
}
int f[1<<16][25];
int Main(){
    //由于商店最多只有16个，考虑状压
    //f[i][j]表示当前购买过的商店为i，当前所在商店是j，最早的时间是啥
    rep(i,1,n)w[i][i]=0;
    //floyd求出两点之间最短路
    rep(k,1,n)rep(i,1,n)rep(j,1,n)w[i][j]=min(w[i][j],w[i][k]+w[k][j]);

    //初始化dp值
    rep(i,0,(1<<m)-1)rep(j,1,m)f[i][j]=(int)1e9;
    rep(i,1,m){
        //预先初始化好从n-1到所有商店的情况
        if(w[n][i]<=ed[i])
        f[(1<<(i-1))][i]=max(w[n][i],st[i])+ti[i];
    }
    rep(i,1,(1<<m)-1)rep(s,1,m){
        rep(j,1,m)if(!(i&(1<<(j-1)))){
            //枚举从商店s到商店j，计算最短路，更新dp值
            if(f[i][s]+w[s][j]<=ed[j])
            f[(1<<(j-1))|i][j]=min(f[(1<<(j-1))|i][j],max(f[i][s]+w[s][j],st[j])+ti[j]);
        }
    }
    int ans=0;
    //统计答案
    rep(i,0,(1<<m)-1)rep(j,1,m)if(f[i][j]<=100000000){
        int res=0;
        rep(k,1,m)if(i&(1<<(k-1)))res++;
        ans=max(ans,res);
    }
    return ans;
}
class TravellingPurchasingMan{
public:
    int maxStores(int N, vector <string> inter, vector <string> roads){
        //预处理
        memset(w,63,sizeof w);
        n=N;
        m=inter.size();
        rep(i,0,m-1){
            split(inter[i],st[i+1],ed[i+1],ti[i+1]);
        }
        rep(i,0,roads.size()-1){
            int a,b,c;
            split(roads[i],a,b,c);
            a++;b++;
            w[a][b]=min(w[a][b],c);
            w[b][a]=min(w[b][a],c);
        }
        return Main();
    }
};





