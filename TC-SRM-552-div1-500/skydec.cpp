#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=35;
int w[N][N];
int n,m;
int D;
int sumD[N][N];
int num[N][N];
int get(int a[N][N],int l,int r,int x,int y){
    if(l>r)return 0;
    if(x>y)return 0;
    return a[r][y]-a[l-1][y]-a[r][x-1]+a[l-1][x-1];
}
int gd[N*N*2];
int gd2[N*N*2];
int Main(){
    //预处理二维前缀和
    
    
    //sumD[i][j]表示L-P的和，即花的数量差
    rep(i,1,n)rep(j,1,m)
    sumD[i][j]=w[i][j]+sumD[i-1][j]+sumD[i][j-1]-sumD[i-1][j-1];
    //num[i][j]表示L+P的和，即花的个数
    rep(i,1,n)rep(j,1,m)
    num[i][j]=abs(w[i][j])+num[i-1][j]+num[i][j-1]-num[i-1][j-1];
    
    //显然两个矩形不相交的话肯定有一条水平的或者竖直的线分离他们
    

    //考虑分割线是水平的
    int ans=-1;
    rep(sp,1,n-1){
        //枚举分割线
        rep(i,0,2*n*m)gd[i]=gd2[i]=-(1e9);
        rep(i,1,sp)rep(j,1,m){
            rep(k,1,sp-i+1)rep(l,1,m-j+1){
                //枚举分割线上的矩形，根据L-P统计答案
                int r1=get(num,i,i+k-1,j,j+l-1);
                int r2=get(sumD,i,i+k-1,j,j+l-1);
                gd[r2+n*m]=max(gd[r2+n*m],r1);
            }
        }
        rep(i,sp+1,n)rep(j,1,m){
            rep(k,1,n-i+1)rep(l,1,m-j+1){
                //枚举分割线下的矩形，根据L-P统计答案
                int r1=get(num,i,i+k-1,j,j+l-1);
                int r2=get(sumD,i,i+k-1,j,j+l-1);
                gd2[r2+n*m]=max(gd2[r2+n*m],r1);
            }
        }
        //枚举两边的L-P的值，统计答案
        rep(i,0,2*n*m)if(gd[i]>=0)rep(j,0,2*n*m)
        if(abs(i+j-2*n*m)<=D){
            ans=max(ans,gd[i]+gd2[j]);
        }
    }
    //考虑分割线是垂直的，和水平同理
    rep(sp,1,m-1){
        rep(i,0,2*n*m)gd[i]=gd2[i]=-(1e9);
        rep(i,1,n)rep(j,1,sp-1){
            //枚举分割线左的矩形，根据L-P统计答案
            rep(k,1,n-i+1)rep(l,1,sp-j+1){
                int r1=get(num,i,i+k-1,j,j+l-1);
                int r2=get(sumD,i,i+k-1,j,j+l-1);
                gd[r2+n*m]=max(gd[r2+n*m],r1);
            }
        }
        rep(i,1,n)rep(j,sp+1,m){
            rep(k,1,n-i+1)rep(l,1,m-j+1){
                //枚举分割线右的矩形，根据L-P统计答案
                int r1=get(num,i,i+k-1,j,j+l-1);
                int r2=get(sumD,i,i+k-1,j,j+l-1);
                gd2[r2+n*m]=max(gd2[r2+n*m],r1);
            }
        }
        //枚举两边的L-P的值，统计答案
        rep(i,0,2*n*m)if(gd[i]>=0)rep(j,0,2*n*m)
        if(abs(i+j-2*n*m)<=D)ans=max(ans,gd[i]+gd2[j]);
    }
    return ans;
}
class FoxAndFlowerShopDivOne{
    public:
    int theMaxFlowers(vector<string> a,int D){
        //预处理
        n=a.size();
        m=a[0].size();
        rep(i,1,n)rep(j,1,m){
            if(a[i-1][j-1]=='L')w[i][j]=1;
            else if(a[i-1][j-1]=='P')w[i][j]=-1;
        }
        ::D=D;
        return Main();
    }
};



