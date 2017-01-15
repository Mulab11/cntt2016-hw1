#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
namespace flow{
    //费用流模板
    const int N=1500;
    int head[N],np[N*30],p[N*30],cost[N*30],fl[N*30],tot;
    int S,T;
    int nSout=0;
    int nTout=0;
    inline void init(int xx){
        rep(i,1,T)head[i]=0;
        rep(i,1,tot)np[i]=p[i]=cost[i]=fl[i]=0;
        tot=1;
        S=xx+1;
        T=S+1;
        nSout=0;
        nTout=0;
    }
    inline void add(int a,int b,int f,int cc){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;cost[tot]=cc;fl[tot]=f;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;cost[tot]=-cc;fl[tot]=0;
        if(a==S)nSout+=f;
        if(b==T)nTout+=f;
    }
    int q[N*N];bool inq[N];
    int dis[N],pre[N],preu[N];
    int spfa(){
        q[q[0]=1]=S;
        rep(i,1,T){
            inq[i]=0;
            dis[i]=1e9;
            pre[i]=preu[i]=-1;
        }
        inq[S]=1;dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(fl[u])if(dis[x]+cost[u]<dis[p[u]]){
                dis[p[u]]=dis[x]+cost[u];
                preu[p[u]]=u;pre[p[u]]=x;
                if(!inq[p[u]]){
                    inq[p[u]]=1;
                    q[++q[0]]=p[u];
                }
            }
            inq[x]=0;
        }
        return pre[T];
    }
    int costflow(){
        if(nSout!=nTout)return -1;
        int ans=0;
        while(spfa()!=-1){
            ans+=dis[T];
            for(int x=T;x!=S;x=pre[x]){
                fl[preu[x]]--;
                fl[preu[x]^1]++;
            }
            nSout--;
        }
        if(nSout!=0)return -1;
        return ans;
    }
};
int kd[35][35];
int n,m;
int id[35][35];
int t;
int Main(){
    rep(i,1,n)rep(j,1,m)if(kd[i][j])id[i][j]=++t;
    flow::init(2*t);
    rep(i,1,n)rep(j,1,m)if(id[i][j]){
        //奇偶染色
        if((i+j)&1){
            flow::add(flow::S,id[i][j]*2-1,1,0);
            flow::add(flow::S,id[i][j]*2,1,0);
            //奇数向四个方向分别连边
            if(id[i-1][j])flow::add(id[i][j]*2-1,id[i-1][j]*2-1,1,0);
            if(id[i+1][j])flow::add(id[i][j]*2-1,id[i+1][j]*2-1,1,0);
            if(id[i][j-1])flow::add(id[i][j]*2,id[i][j-1]*2,1,0);
            if(id[i][j+1])flow::add(id[i][j]*2,id[i][j+1]*2,1,0);

            //题目里要求有直的的话代价就为1
            //那么一开始S分配给水平竖直流量都为1
            //连一条费用为1的边让他们流量交换
            flow::add(id[i][j]*2,id[i][j]*2-1,1,kd[i][j]-1);
            flow::add(id[i][j]*2-1,id[i][j]*2,1,kd[i][j]-1);
        }
        else{
            flow::add(id[i][j]*2-1,flow::T,1,0);
            flow::add(id[i][j]*2,flow::T,1,0);
            flow::add(id[i][j]*2,id[i][j]*2-1,1,kd[i][j]-1);
            flow::add(id[i][j]*2-1,id[i][j]*2,1,kd[i][j]-1);
        }
    }
    return flow::costflow();
}
class CurvyonRails{
public:
    int getmin(vector<string> field){
        //预处理
        n=field.size();
        m=field[0].size();
        rep(i,1,n)rep(j,1,m){
            if(field[i-1][j-1]=='C')kd[i][j]=2;
            if(field[i-1][j-1]=='.')kd[i][j]=1;
            if(field[i-1][j-1]=='w')kd[i][j]=0;
        }
        return Main();
    }
};


