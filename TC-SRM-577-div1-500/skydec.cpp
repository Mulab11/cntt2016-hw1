#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
const int N=105;
int x[N],y[N],n;
struct state{
    //矩阵((xl,yl),(xr,yr))
    int xl,xr,yl,yr;
    inline state(int _xl=0,int _xr=0,int _yl=0,int _yr=0){
        xl=_xl;xr=_xr;yl=_yl;yr=_yr;
    }
};
inline bool operator <(const state &a,const state &b){
    //重载矩阵<，为了能用map
    if(a.xl!=b.xl)return a.xl<b.xl;
    if(a.xr!=b.xr)return a.xr<b.xr;
    if(a.yl!=b.yl)return a.yl<b.yl;
    return a.yr<b.yr;
}
map<state,int>f;
bool inside(int x,int y,int xl,int xr,int yl,int yr){
    //判断点(x,y)是否在矩阵(xl,xr,yl,yr)内
    return (x<=xr)&&(x>=xl)&&(y<=yr)&&(y>=yl);
}
int dp(int xl,int xr,int yl,int yr){
    state S=state(xl,xr,yl,yr);
    //记忆化搜索
    if(f.find(S)!=f.end())return f[S];

    int ret=(int)1e9;
    bool all=1;
    rep(i,1,n)if(!inside(x[i],y[i],xl,xr,yl,yr)){
        //枚举下一个点选哪个
        all=0;

        int ans=0;
        //计算代价
        ans+=max(max(abs(x[i]-xl),abs(x[i]-xr)),max(abs(y[i]-yl),abs(y[i]-yr)));

        //因为旋转矩阵后距离变成max(|x1-x2|,|y1-y2|)
        //计算新边界
        int _xl=min(xl,x[i]);
        int _yl=min(yl,y[i]);
        int _xr=max(xr,x[i]);
        int _yr=max(yr,y[i]);

        rep(j,1,n)if(j^i)if(inside(x[j],y[j],_xl,_xr,_yl,_yr))
        if(!inside(x[j],y[j],xl,xr,yl,yr)){
            //所以边界肯定越小越好
            //在边界内的肯定现在就要选
            //直接处理掉
            ans+=max(max(abs(x[j]-_xl),abs(x[j]-_xr)),max(abs(y[j]-_yl),abs(y[j]-_yr)));
        }

        ret=min(ret,dp(_xl,_xr,_yl,_yr)+ans);
    }
    //返回答案
    //all表示是否所有点都在矩阵内，是的话返回0
    if(all)return f[S]=0;
    else return f[S]=ret;
}
int Main(){
    if(!n)return 0;
    int ans=(int)1e9;
    rep(i,1,n){
        //选一个点开始扩展
        ans=min(ans,dp(x[i],x[i],y[i],y[i]));
    }
    return ans;
}
class EllysChessboard{
public:
    int minCost(vector <string> board){
        //预处理
        rep(i,0,board.size()-1)rep(j,0,board[i].size()-1)if(board[i][j]=='#'){
            //旋转坐标，(x,y)->(x+y,x-y)
            ++n;x[n]=i+j;y[n]=i-j;
        }
        return Main();
    }
};



