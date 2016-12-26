#include <map>
#include <cmath>
#include <stdio.h>
#include <algorithm>

#define x first
#define y second
#define pb push_back
#define cp const ww&
#define Rin register int
#define oo (c=getchar())
#define SZ(V) (int(V.size()))
#define ALL(V) V.begin(),V.end()
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)

using namespace std;

typedef double db;
typedef long long LL;
typedef vector<int> VI;
typedef pair<int ,int> PII;
typedef vector<PII> VII;
// typedef __int128 bigint;

const db pi=acos(-1);
const int mo=100007;

struct ww{
	db x,y;
	ww(db x=0,db y=0):x(x),y(y){}
	ww operator - (cp A)	{return {x-A.x,y-A.y};}
	ww operator + (cp A)	{return {x+A.x,y+A.y};}
	db operator ^ (cp A)	{return x*A.y-y*A.x;}
}p[222],q[55];

int n,m,idx,f[222][222][2],g[222][222],col[55],na[222][222],se[222][222][55];
bool ok[222][222];

void inc(int &x,int y)	{if((x+=y)>=mo)x-=mo;}
bool check(int i,int j)	{return i+1==j || na[j][i]==na[j-1][i+1];}//判带状区域有没有点
int G(int i,int j)	{return i+3>=j?1:g[i+1][j-1];}
int cnt(int i,int j,int k)	{return m-na[j][i]-na[k][j]-na[i][k];}//三角形内部的点数

int Main(){
	rep(i,0,n)rep(j,0,n)if(i^j)For(k,1,m)se[i][j][col[k]]+=((p[j]-p[i])^(q[k]-p[i]))>0;//求每个向量一侧某种颜色的点数
	rep(i,0,n)For(k,1,idx)if(se[(i+1)%n][i][k])return 0;//如果凸包外面有点就狗带
	rep(i,0,n)rep(j,0,n)if(i^j){
		ok[i][j]=1;
		For(k,1,m){
			if(se[i][j][k] && se[j][i][k])ok[i][j]=0;
			na[i][j]+=se[i][j][k];//每个向量一侧的点数
		}
	}
	//判每条对角线能不能存在
	//g表示con[i,j]的答案，f表示i,j是一条对角线的答案，最后一维表示内部有没有点
	rep(j,0,n)dto(i,j-1,0){
		if(i+1==j){
			f[i][j][0]=1;
			g[i][j]=1;
			continue;
		}
		//边界
		rep(k,i+1,j)if(ok[i][k] && check(i,k)){
			bool op=!!cnt(i,k,j);
			rep(_,0,2)inc(f[i][j][op || _],1ll*f[k][j][_]*G(i,k)%mo);
		}
		//枚举i毗邻的点更新f的答案
		if(!na[j][i])g[i][j]=1,inc(f[i][j][0],1);else{
			if(ok[i][j] && check(i,j))inc(f[i][j][0],G(i,j));//凸包的第一条边出现
			if(!cnt(i,i+1,j))inc(g[i][j],g[i+1][j]);//i不在凸包上
			if(ok[i][j])inc(g[i][j],f[i][j][1]);
			if(i+2==j)continue;
			if(ok[i][j-1] && cnt(i,j-1,j)==0)inc(g[i][j],f[i][j-1][1]);
			For(k,i+2,j-2)if(ok[i][k] && cnt(i,k,j)+cnt(k,k+1,j)==0)inc(g[i][j],1ll*f[i][k][1]*g[k+1][j]%mo);
			//枚举i顺时针方向下一个点
		}
	}
	return g[0][n-1];
}

struct FencingPenguins{
	int countWays(int numPosts,int radius,VI x,VI y,string color){
		map<char ,int> Maps;Maps.clear();
		n=numPosts;
		rep(i,0,n)p[i]=ww(radius*cos(2*pi/n*i),radius*sin(2*pi/n*i));
		// 计算凸包的点坐标
		m=x.size();
		For(i,1,m){
			q[i]=ww(x[i-1],y[i-1]);
			int &xx=Maps[color[i-1]];
			if(!xx)xx=++idx;
			col[i]=xx;
		}
		// 离散颜色
		return Main();
	}
};