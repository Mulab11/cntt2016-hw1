#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=55;
double x[N],y[N],r[N];
double sx,sy,tx,ty;
double low[N],high[N];
bool nonzero[N];
int n;
int q[N*N*N*N];
double dis(double x1,double y1,double x2,double y2){
    //(x1,y1)和(x2,y2)的距离
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
void renew(int x,double l,double r){
    //用[l,r]对x进行更新
    if(::r[x]<r)r=::r[x];
    if(l<0)l=0;
    if(l>r)return;
    if(!nonzero[x]){
        nonzero[x]=1;
        low[x]=l;high[x]=r;
        q[++q[0]]=x;
        return;
    }
    if(low[x]<=l&&r<=high[x])return;
    if(l<low[x])low[x]=l;
    if(r>high[x])high[x]=r;
    q[++q[0]]=x;
}
int Main(){
    //一开始的值
    rep(i,1,n){
        if(dis(sx,sy,x[i],y[i])<=r[i]){
            renew(i,dis(sx,sy,x[i],y[i]),dis(sx,sy,x[i],y[i]));
        }
    }

    //采取最短路的方法来更新
    rep(i,1,q[0]){
        int d=q[i];
        rep(j,1,n)if(d^j){
            double Dis=dis(x[d],y[d],x[j],y[j]);
            if(Dis>=r[d]+r[j])continue;
            if(min(high[d],Dis+r[j])>=max(Dis-r[j],low[d])){
                renew(j,Dis-r[d],Dis+r[d]);
                renew(d,Dis-r[j],Dis+r[j]);
            }
        }
    }

    //统计答案
    rep(i,1,n)if(nonzero[i]){
        if(dis(tx,ty,x[i],y[i])>low[i]&&dis(tx,ty,x[i],y[i])<high[i])
        return 1;
    }
    return 0;
}
class CandyOnDisk{
public:
    string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
        //预处理
        //当起点和重点重合时直接返回Yes
        if(sx==tx&&sy==ty)return "YES";
        n=0;
        map<pair<int,int>,int>gt;
        rep(i,0,x.size()-1){
            if(!gt[pair<int,int>(x[i],y[i])]){
                //去重
                gt[pair<int,int>(x[i],y[i])]=++n;
                ::x[n]=x[i];
                ::y[n]=y[i];
                ::r[n]=r[i];
            }
            else{
                //圆心相同的点选一个半径最大的
                int d=gt[pair<int,int>(x[i],y[i])];
                if(::r[d]<r[i])::r[d]=r[i];
            }
        }
        ::sx=sx;
        ::sy=sy;
        ::tx=tx;
        ::ty=ty;
        return Main()?"YES":"NO";
    }
}gt;





