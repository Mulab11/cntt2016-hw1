#include<stdio.h>
#include<string>
#include<vector>
#include<cstring>
#include<stdlib.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int n;
namespace flow{
    //网络流模板
    int head[N],np[N*N*10],p[N*N*10],fl[N*N*10],tot;
    int S,T;
    void init(int n){
        memset(head,0,sizeof head);
        rep(i,1,tot){
            np[i]=p[i]=fl[i]=0;
        }
        tot=1;
        S=n+1;T=S+1;
    }
    void add(int a,int b,int c){
        ++tot;p[tot]=b;np[tot]=head[a];head[a]=tot;fl[tot]=c;
        ++tot;p[tot]=a;np[tot]=head[b];head[b]=tot;fl[tot]=0;
    }
    int q[N],dis[N];
    int bfs(){
        memset(dis,-1,sizeof dis);
        q[q[0]=1]=S;
        dis[S]=0;
        rep(i,1,q[0]){
            int x=q[i];
            for(int u=head[x];u;u=np[u])if(fl[u])if(dis[p[u]]==-1){
                dis[p[u]]=dis[x]+1;
                q[++q[0]]=p[u];
            }
        }
        return dis[T];
    }
    int dinic(int x,int ff){
        if(x==T)return ff;
        int ret=0;
        for(int u=head[x];u;u=np[u])if(fl[u])if(dis[p[u]]==dis[x]+1){
            int tmp=dinic(p[u],min(fl[u],ff));
            fl[u]-=tmp;fl[u^1]+=tmp;
            ret+=tmp;ff-=tmp;
            if(!ff)break;
        }
        if(!ret)dis[x]=-1;
        return ret;
    }
    int maxflow(){
        int ans=0;
        while(bfs()!=-1){
            ans+=dinic(S,1e9);
        }   
        printf("%d\n",ans);
        return ans;
    }
};
class OldBridges{
public:
    string isPossible(vector <string> w, int a1, int a2, int an, int b1, int b2, int bn){
        n=w.size();
        a1++;a2++;b1++;b2++;
        an*=2;bn*=2;
        flow::init(n);
        //预处理
        rep(i,1,n)rep(j,1,n)if(w[i-1][j-1]!='X'){
            if(w[i-1][j-1]=='O')flow::add(i,j,2);
            else flow::add(i,j,1e9);
        }

        //我们从(a1,b1)->(a2,b2)流一遍
        //再从(a1,b2)->(a2,b1)流一遍
        //就可以通过每条边在这两次流的两个流量来构造解
        //具体就是，第一个人走(A+B)/2，第二个人走(A-B)/2

        //第一遍，(a1,b1)->(a2,b2)
        flow::add(flow::S,a1,an);
        flow::add(flow::S,b1,bn);
        flow::add(a2,flow::T,an);
        flow::add(b2,flow::T,bn);
        //如果最大流比(an+bn)小，肯定不合法
        if(flow::maxflow()<(an+bn))return "No";

        flow::init(n);
        rep(i,1,n)rep(j,1,n)if(w[i-1][j-1]!='X'){
            if(w[i-1][j-1]=='O')flow::add(i,j,2);
            else flow::add(i,j,1e9);
        }
        //第二遍(a1,b2)->(a2,b1)
        swap(b1,b2);
        flow::add(flow::S,a1,an);
        flow::add(flow::S,b1,bn);
        flow::add(a2,flow::T,an);
        flow::add(b2,flow::T,bn);
        //如果最大流比(an+bn)小，肯定不合法
        if(flow::maxflow()<(an+bn))return "No";
        return "Yes";
    }
};


