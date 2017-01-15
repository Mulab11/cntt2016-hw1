#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
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
map<pii,bool> go;
//注意要开set达到去重的目的
set<int> rx,lx,ry,ly;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
//吐槽：垃圾英语题毁我青春
class RotatingBot{
    public:
    int minArea(vector <int> moves){
        int x=0;int y=0;
        int k=0;
        int maX,maY,miX,miY;
        maX=maY=0;
        miX=miY=0;
        go[pii(0,0)]=1;
        rep(i,0,moves.size()-1){
            //先判断一个格子是否会被经过两次
            int d=moves[i];
            while(d--){
                x+=dx[k];
                y+=dy[k];
                if(go[pii(x,y)])return -1;
                go[pii(x,y)]=1;
                maX=max(maX,x);
                miX=min(miX,x);
                maY=max(maY,y);
                miY=min(miY,y);
            }
            if(i!=moves.size()-1)
            if(!go[pii(x+dx[k],y+dy[k])]){
                //注意每次转弯时把点记下来
                if(dx[k]==1)rx.insert(x);
                if(dx[k]==-1)lx.insert(x);
                if(dy[k]==1)ry.insert(y);
                if(dy[k]==-1)ly.insert(y);
            }
            k=(k+1)%4;
        }
        //如果转弯时的坐标不一样，说明边界不唯一，不合法
        if(rx.size()>1)return -1;
        if(lx.size()>1)return -1;
        if(ry.size()>1)return -1;
        if(ly.size()>1)return -1;
        
        //同时转弯的坐标也必须是极值
        if(lx.size()&&((*lx.begin())!=miX))return -1;
        if(ly.size()&&((*ly.begin())!=miY))return -1;
        if(rx.size()&&((*rx.begin())!=maX))return -1;
        if(ry.size()&&((*ry.begin())!=maY))return -1;
        
        //面积其实是唯一确定的，直接返回即可
        return (maX-miX+1)*(maY-miY+1);
    }
};


