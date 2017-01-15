#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=305;
int a[N];
//计算几何的向量struct
struct po{
    int x,y;
    inline po(int _x=0,int _y=0){
        x=_x;y=_y;
    }
}b[N],c[N];
int n,m,k;
//向量加法
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
//向量减法
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
//向量叉积
inline int operator ^(const po &a,const po &b){return a.x*b.y-a.y*b.x;}
int sum[10005];
po S;
//顺时针排序
inline bool cmp(const po &x,const po &y){
    return ((x-S)^(y-S))>0;
}
LL Main(){
    sort(a+1,a+1+n);
    rep(i,1,n)sum[a[i]]++;
    rep(i,1,10000)sum[i]+=sum[i-1];
    LL ans=0;
    rep(i,1,m){
        //暴力枚举第一个点
        k=0;S=b[i];
        rep(j,1,m)if(b[j].y<S.y)c[++k]=b[j];

        sort(c+1,c+1+k,cmp);

        rep(j,1,n)if(a[j]<S.x){
            //枚举第二个点
            int st=j;
            while((st<=n)&&(a[st]<=S.x))st++;
            //根据之前按顺时针排序的向量，找出下界
            rep(d,1,k)if(((c[d]-S)^(po(a[j],0)-S))<0){
                //枚举第一个第二类点
                //更新下界
                while((st<=n)&&(((po(a[st],0)-S)^(c[d]-S))>=0))st++;

                //用下界更新答案
                int L=n-st+1;
                int G=st-sum[c[d].x]-1;
                if(!L)continue;
                int D=sum[c[d].x-1]-j;
                ans+=D*1ll*(L*G+((L-1)*L/2));
            }
        }
    }
    return ans;
}
class Ear{
public:
    LL getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
        //预处理，将一堆vector<string>转成vector<int>
        string s="";
        rep(i,0,redX.size()-1)s=s+redX[i];
        int now=0;int l=s.size();
        rep(i,0,l-1){
            if(s[i]==' '){a[++n]=now;now=0;}
            else{now=now*10+(s[i]-'0');}
        }
        a[++n]=now;now=0;

        s="";
        rep(i,0,blueX.size()-1)s=s+blueX[i];
        l=s.size();now=0;
        
        rep(i,0,l-1){
            if(s[i]==' '){b[++m].x=now;now=0;}
            else{now=now*10+(s[i]-'0');}
        }
        b[++m].x=now;now=0;

        s="";
        rep(i,0,blueY.size()-1)s=s+blueY[i];
        l=s.size();now=0;
        m=0;

        rep(i,0,l-1){
            if(s[i]==' '){b[++m].y=now;now=0;}
            else{now=now*10+(s[i]-'0');}
        }
        b[++m].y=now;now=0;

        return Main();
    }
};




