#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
const int inf=1000000000;
int col[N][3];
int n;
int f[N][8];
inline void Min(int &x,int y){if(y<x)x=y;}
int Main(){
    int need=0;
    rep(i,1,n)rep(j,0,2)if(col[i][j])need|=(1<<j);
    rep(i,0,n)rep(j,0,7)f[i][j]=inf;
    f[0][0]=0;
    //f[i][j]表示考虑了前i个，当前有哪些颜色的球有自己的盒子
    rep(i,0,n-1)rep(j,0,7){
        //枚举这个盒子保留哪种颜色
        //注意这个盒子如果没有那种颜色的球的话，保留这个颜色是不优的
        if(col[i+1][0])Min(f[i+1][j|1],f[i][j]+col[i+1][1]+col[i+1][2]);
        if(col[i+1][2])Min(f[i+1][j|4],f[i][j]+col[i+1][1]+col[i+1][0]);
        if(col[i+1][1])Min(f[i+1][j|2],f[i][j]+col[i+1][0]+col[i+1][2]);
    }
    //注意是need，不是7
    if(f[n][need]<inf)return f[n][need];
    else return -1;
}
class BallsSeparating{
public:
    int minOperations(vector <int> red, vector <int> green, vector <int> blue){
        //预处理
        n=red.size();
        rep(i,1,n){
            col[i][0]=red[i-1];
            col[i][1]=green[i-1];
            col[i][2]=blue[i-1];
        }
        return Main();
    }
};



