#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=15;
int a[N][N];
int l[N],r[N];
int n,S;
double ans=0;
int v[N];//1:max 2:min 0:other
double be[N];
int xi[N];
void check(){
    //最优性剪枝
    //v[i]=0表示第i个变量没限制
    //v[i]=1表示第i个变量限制取下界
    //v[2]=2表示第i个变量限制取上界
    rep(i,1,n)if(!v[i])rep(j,1,n)if(i!=j)if(!v[j])if(!a[i][j])return;
    int k=0;
    int rest=S;
    //减去已经固定的变量的值
    rep(i,1,n)if(v[i]==1){rest-=r[i];be[i]=r[i];}
    else if(v[i]==2){rest-=l[i];be[i]=l[i];}

    //如果已经不够用则返回
    if(rest<0)return;

    double ret=0;
    double sum=0;
    rep(i,1,n)if(!v[i]){
        k++;
        xi[i]=0;
        //预处理出变量的系数
        rep(j,1,n)if(v[j])if(a[i][j])xi[i]+=be[j];
        be[i]=rest/2+xi[i];
        sum+=be[i];
    }
    if(k){
        //均分更新
        double c=(rest-sum)/k;
        rep(i,1,n)if(!v[i]){
            be[i]+=c;
            if(be[i]+(1e-9)<l[i])return;
            if(be[i]-(1e-9)>r[i])return;
        }
    }
    //更新答案
    rep(i,1,n)rep(j,i+1,n)if(a[i][j])ret+=be[i]*be[j];
    if(ret>ans)ans=ret;
}
void dfs(int x){
    if(x==n+1){
        check();
        return;
    }
    rep(i,0,2){
        //枚举3种状态
        v[x]=i;
        dfs(x+1);
    }
}
double Main(){
    //搜出所有变量的状态，状态数最多3^n
    dfs(1);
    return ans;
}
class BoundedOptimization{
public:
    double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
        //预处理
        n=lowerBound.size();
        rep(i,1,n){
            l[i]=lowerBound[i-1];
            r[i]=upperBound[i-1];
        }
        S=maxSum;
        string all="";
        rep(i,0,expr.size()-1)all=all+expr[i];
        for(int i=0;i<all.size();i+=3){
            int xx=all[i]-'a'+1;
            int yy=all[i+1]-'a'+1;
            a[xx][yy]=a[yy][xx]=1;
        }
        return Main();
    }
}gt;





