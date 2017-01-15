#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
int n,a[N],T;
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
LL Main(){
    int d=0;
    LL x=0;
    LL y=0;
    //先暴力模拟n步
    rep(i,1,n){
        x+=dx[d]*a[i];
        y+=dy[d]*a[i];
        d=(d+a[i])%4;
    }
    LL nowx=0;
    LL nowy=0;
    int nowd=0;
    int rest=0;
    rep(i,1,T){
        if(nowd==0){
            nowx+=x;
            nowy+=y;
        }
        else
        if(nowd==1){
            nowx+=y;
            nowy-=x;
        }
        else
        if(nowd==2){
            nowx-=x;
            nowy-=y;
        }
        else
        if(nowd==3){
            nowx-=y;
            nowy+=x;
        }
        nowd=(nowd+d)%4;

        //暴力模拟，当方向归0时，剩下几步都是同一个方向的增量
        //可以直接累加答案
        if(!nowd){
            nowx*=(T/i);
            nowy*=(T/i);
            rest=T%i;
            break;
        }
    }
    //剩下的部分也走一下
    rep(i,1,rest){
        if(nowd==0){
            nowx+=x;
            nowy+=y;
        }
        else
        if(nowd==1){
            nowx+=y;
            nowy-=x;
        }
        else
        if(nowd==2){
            nowx-=x;
            nowy-=y;
        }
        else
        if(nowd==3){
            nowx-=y;
            nowy+=x;
        }
        nowd=(nowd+d)%4;
    }
    if(nowx<0)nowx=-nowx;
    if(nowy<0)nowy=-nowy;
    return nowx+nowy;
};
class RobotHerb{
public:
    LL getdist(int T, vector <int> a){
        //预处理
        n=a.size();
        rep(i,1,n)::a[i]=a[i-1];
        ::T=T;
        return Main();
    };
}gt;



