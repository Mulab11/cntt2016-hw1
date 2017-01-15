#include<bits/stdc++.h>
#define eps (1e-6)
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=55;
//-----------------------------------------
//计算几何向量模板
struct po{
    DB x,y;
    inline po(DB _x=0,DB _y=0){x=_x;y=_y;}
};
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
inline DB operator ^(const po &a,const po &b){return a.x*b.y-a.y*b.x;}
inline DB operator *(const po &a,const po &b){return a.x*b.x+a.y*b.y;}
//-----------------------------------------
po cir[N];
DB r[N];
int n;
//struct mes表示一个弧度的区间
struct mes{
    DB l,r;
    inline mes(DB _l=0,DB _r=0){l=_l;r=_r;}
}q[N*N];
inline bool operator <(const mes &a,const mes &b){if(a.l==b.l)return a.r<b.r;return a.l<b.l;}
int t;
void addseg(DB l,DB r){
    q[++t]=mes(l,r);
}
void add(DB l,DB r){
    //添加弧度l~r
    if(l<0){
        //把l,r都变成非负数
        l+=2*pi;
        r+=2*pi;
    }
    if(r>2*pi){
        //如果r太大，那么分两段来加
        addseg(0,r-2*pi);
        r=2*pi;
    }
    addseg(l,r);
}
bool ok(){
    //相当于给定一堆区间问是否被覆盖
    sort(q+1,q+1+t);
    DB pre=0;
    rep(i,1,t){
        if(q[i].l>pre+(1e-9))return 0;
        pre=max(pre,q[i].r);
    }
    //当没有全部被覆盖时有解
    if(pre<2*pi)return 0;
    return 1;
}
bool check(DB D){
    t=0;
    rep(i,2,n){
        DB dis=sqrt((cir[i]-cir[1])*(cir[i]-cir[1]));
        if(dis>r[1]+r[i]+D)continue;
        DB L=0;DB R=pi;
        DB theta=acos(r[1]/dis);
        DB fu=sqrt(dis*dis-r[1]*r[1])-r[i];
        //二分求出可行区间的幅度大小
        rep(t,1,100){
            DB mid=(L+R)/2;
            DB dd=0;
            if(mid<=theta){
                DB tmp=dis-cos(mid)*r[1];
                DB tt2=sin(mid)*r[1];
                dd=sqrt(tt2*tt2+tmp*tmp)-r[i];
            }
            else{
                dd=fu+(mid-theta)*r[1];
            }
            if(dd<=D)L=mid;
            else R=mid;
        }
        DB ji=atan2((cir[i]-cir[1]).y,(cir[i]-cir[1]).x);
        //添加该区间
        add(ji-L,ji+L);
    }
    return !ok();
}
DB Main(){
    DB L=0;DB R=1e9;
    //考虑二分答案，这里采用固定迭代次数来保证精度
    rep(i,1,1000){
        DB mid=(L+R)/2.;
        if(check(mid))L=mid;
        else R=mid;
    }
    return L;
}
class CircusTents{
public:
    DB findMaximumDistance(vector<int> x,vector<int> y,vector<int> r){
        //预处理
        n=x.size();
        rep(i,1,n){
            cir[i]=po(x[i-1],y[i-1]);
            ::r[i]=r[i-1];
        }
        return Main();
    }
}gt;



