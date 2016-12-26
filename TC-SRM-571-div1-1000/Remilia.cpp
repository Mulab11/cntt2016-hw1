// by ξ
// program sky  :)

#include <vector>
#include <string>
#include <stdio.h>
#include <cassert>
#include <iostream>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define SZ(A) (int(A.size()))
#define pb push_back
#define mk make_pair
#define x first
#define y second

using namespace std;

typedef __float128 db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

string done="YES",undone="NO";
const db eps=1e-18;

int n,r[55],g[100010];
db L[55],R[55];
bool inq[55],bo[55][55];
struct ww{
	// point
	int x,y;
	db len(){return sqrt(1.*x*x+1.*y*y);}
	ww operator - (ww A){return {x-A.x,y-A.y};}
	bool operator != (ww A){return x^A.x || y^A.y;}
}p[55];

db dis(ww a,ww b){return (a-b).len();}

db ABS(db x){return x<0?-x:x;}

int dcmp(db x,db y){
	// comparison function
	return ABS(x-y)<eps?0:x<y?-1:1;
}

bool renew(int i,int j){
	// renew circle i with circle j
	db ll=dis(p[i],p[j])-r[j],rr=ll+2*r[j];
	ll=max(ll,db(0));rr=min(rr,(db)r[i]);
	if(dcmp(ll,L[i])<0 || dcmp(rr,R[i])>0)return L[i]=min(L[i],ll),R[i]=max(R[i],rr),1;
	return 0;
}

void gao(){
	// spfa to get all intervals
	int l=0,r=0;
	For(i,1,n)if(L[i]>-0.5)g[r++]=i,inq[i]=1;
	for(;l<r;){
		int u=g[l++];
		inq[u]=0;
		For(v,1,n)if(v^u && !bo[u][v] && p[u]!=p[v]){
			db len=dis(p[u],p[v]);
			if(dcmp(len-::r[v],R[u])<=0 && dcmp(len+::r[v],L[u])>=0){
				bo[u][v]=bo[v][u]=1;
				if(renew(v,u) && !inq[v])inq[g[r++]=v]=1;
				if(renew(u,v) && !inq[u])inq[g[r++]=u]=1;
			}
		}
	}
}

string Main(int sx,int sy,int tx,int ty){
	// stay
	if(sx==tx && sy==ty)return done;
	// source
	ww P={sx,sy};
	For(i,1,n)if(dcmp(dis(P,p[i]),r[i])<=0)L[i]=R[i]=dis(P,p[i]);else L[i]=R[i]=-1;
	gao();
	// sink
	P={tx,ty};
	For(i,1,n)if(dcmp(dis(P,p[i]),L[i])>=0 && dcmp(dis(P,p[i]),R[i])<0)return done;
	// 精度问题
	return undone;
}

struct CandyOnDisk{
	string ableToAchieve(VI x,VI y,VI r,int sx,int sy,int tx,int ty){
		n=SZ(x);
		For(i,1,n)p[i]={x[i-1],y[i-1]},::r[i]=r[i-1];
		return Main(sx,sy,tx,ty);
	}
};