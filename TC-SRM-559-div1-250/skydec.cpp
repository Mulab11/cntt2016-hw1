#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
LL f[1<<8];
int dx[8],dy[8];
int lx,rx,ly,ry;
int cnt[1<<8];
int n,m;
void gaoX(int x){
    if(x<0)lx=max(lx,-x+1);
    if(x>0)rx=min(rx,n-x);
}
void gaoY(int y){
    if(y<0)ly=max(ly,-y+1);
    if(y>0)ry=min(ry,m-y);
}
class HyperKnight{
public:
    LL countCells(int a, int b, int n, int m, int k){
        rep(i,0,255)cnt[i]=cnt[i/2]+(i&1);
        ::n=n;::m=m;
        int dj=0;
        rep(i,-1,1)if(i!=0)rep(j,-1,1)if(j!=0){
            //预处理方向
            dx[dj]=i*a;
            dy[dj]=j*b;
            dj++;
            dx[dj]=i*b;
            dy[dj]=j*a;
            dj++;
        }
        rep(i,0,255){
            //2^8-1枚举哪些方向的移动合法
            //列出不等式
            //显然满足的点在一个矩阵内，求一下即可
            lx=1;rx=n;
            ly=1;ry=m;
            rep(j,0,7)if(i&(1<<j)){
                gaoX(dx[j]);
                gaoY(dy[j]);
            }
            f[i]=(rx-lx+1)*1ll*(ry-ly+1);
        }
        //考虑容斥原理，枚举超集，减去超集的情况
        LL ans=0;
        per(i,255,0){
            rep(j,i+1,255)if((i&j)==i)f[i]-=f[j];
            if(cnt[i]==k)ans+=f[i];
        }
        return ans;
    }
};





