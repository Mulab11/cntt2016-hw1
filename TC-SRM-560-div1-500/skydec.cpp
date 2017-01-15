#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
using namespace std;
const int N=55;
int x[N],y[N],n;
const int S=300;
int ti[S*2+10][S*2+10];
int sum[S*2+10][S*2+10];
bool ok[S*2+10][S*2+10];
int GetS(int lx,int ly,int rx,int ry){
    //求矩阵[lx,rx][ly,ry]的和
    return sum[rx][ry]-sum[lx-1][ry]-sum[rx][ly-1]+sum[lx-1][ly-1];
}
int Main(){
    rep(i,1,n)x[i]+=S,y[i]+=S;
    rep(i,1,n)ti[x[i]][y[i]]=1;
    rep(k,2,140){
        //模拟扩散k次之后的形状
        rep(i,1,2*S)rep(j,1,2*S)if(ti[i][j]==k-1){
            //往4个方向进行扩散
            ti[i-1][j-1]=k;
            ti[i-1][j+1]=k;
            ti[i+1][j+1]=k;
            ti[i+1][j-1]=k;
        }
        //预处理二维矩阵前缀和
        rep(i,1,2*S)rep(j,1,2*S){
            sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+(ti[i][j]==k);
        }
        memset(ok,0,sizeof ok);
        int cnt=0;
        //计算出哪些位置是可以在初始位置的
        rep(i,-70,70)rep(j,-70,70){
            if(GetS(i*2+S-(k-1),j*2+S-(k-1),i*2+S+(k-1),j*2+S+(k-1))==k*k){
                ok[i*2+S][j*2+S]=1;
                //cnt表示个数
                ++cnt;
            }
        }
        //个数不对直接返回
        if(cnt!=n)return k-2;
        //如果有给定的初始位置不合法的话也直接返回
        rep(i,1,n)if(!ok[x[i]][y[i]])return k-2;
    }
    //达到上界还没返回，视作答案为无限大
    return -1;
}
class DrawingPointsDivOne{
public:
    int maxSteps(vector <int> x, vector <int> y){
        //预处理
        n=x.size();
        rep(i,1,n){
            //为了防止出现小数，先将坐标*2
            ::x[i]=x[i-1]*2;
            ::y[i]=y[i-1]*2;
        }
        return Main();
    }
}gt;

