#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=305;
int n;
bool tr1[N][N];
int dis1[N][N],dis2[N][N];
bool tr2[N][N];
int K;
double cnt1[N],cnt2[N];
double Main(){
    //初始化
    memset(dis1,63,sizeof dis1);
    memset(dis2,63,sizeof dis2);
    rep(i,1,n)dis1[i][i]=dis2[i][i]=0;

    rep(i,1,n)rep(j,1,n){
        if(tr1[i][j])dis1[i][j]=min(dis1[i][j],1);
        if(tr2[i][j])dis2[i][j]=min(dis2[i][j],1);
    }

    //对于每棵树，求出每两个点的路径长度
    //由于本题数据范围比较小，所以采用floyd计算
    rep(k,1,n){
        rep(i,1,n)rep(j,1,n){
            dis1[i][j]=min(dis1[i][j],dis1[i][k]+dis1[k][j]);
            dis2[i][j]=min(dis2[i][j],dis2[i][k]+dis2[k][j]);
        }
    }


    //统计每棵树长度为x的链各有多少
    rep(i,1,n)rep(j,i+1,n)cnt1[dis1[i][j]]++;
    rep(i,1,n)rep(j,i+1,n)cnt2[dis2[i][j]]++;

    //暴力卷积一下
    double ans=0;
    rep(i,1,K)rep(j,1,K)if(i+j+2==K){
        ans=ans+(cnt1[i]*cnt2[j])/(n*(n-1));
    }
    ans=ans*2;
    return ans;
}
class TreeUnion{
public:
    double expectedCycles(vector<string> tree1,vector<string> tree2,int K){
        //将复杂的格式转化成树
        ::K=K;
        string gt="";
        rep(i,0,tree1.size()-1)gt=gt+tree1[i];
        n=0;
        int now=0;
        rep(i,0,gt.size()-1)if(gt[i]==' '){
            ++n;
            tr1[n+1][now+1]=tr1[now+1][n+1]=1;
            now=0;
        }
        else{
            now=now*10+(gt[i]-'0');
        }
        ++n;
        tr1[n+1][now+1]=tr1[now+1][n+1]=1;
        now=0;


        gt="";
        rep(i,0,tree2.size()-1)gt=gt+tree2[i];
        n=0;
        now=0;
        rep(i,0,gt.size()-1)if(gt[i]==' '){
            ++n;
            tr2[n+1][now+1]=tr2[now+1][n+1]=1;
            now=0;
        }
        else{
            now=now*10+(gt[i]-'0');
        }
        ++n;
        tr2[n+1][now+1]=tr2[now+1][n+1]=1;
        now=0;
        n++;
        return Main();
    }
};





