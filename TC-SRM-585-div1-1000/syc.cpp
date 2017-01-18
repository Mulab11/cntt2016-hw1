#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define For(i,x,y)  for(int i=(int)x;i<=(int)y;i++)
#define Rep(i,x,y)  for(int i=(int)x;i< (int)y;i++)
#define Forn(i,x,y) for(int i=(int)x;i>=(int)y;i--)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
const	int P=1e9+7;
const	int inf=1e9;
const	ll Inf=1e15;
const	int N=500005;

int n,m,sz,f[N];
struct po{
	int x,y;
	po operator -(const po &a)const{
		return (po){x-a.x,y-a.y};
	}
	ll operator *(const po &a)const{
		return (ll)x*a.y-(ll)y*a.x;
	}
}A[N],B[N];
int l,r,que[N];
ll sum,tag,val[N];

#define REP(i, x, y) for(int i = x; i <= y; i ++)
#define VI vector<int>
struct EnclosingTriangle{
	long long getNumber(int SZ, VI x, VI y){
		sz = SZ;
		m = x.size();
		For(i,1,m) B[i].x = x[i - 1], B[i].y = y[i - 1];
		For(i,0,sz) A[++n]=(po){i,0};
		For(i,1,sz) A[++n]=(po){sz,i};
		Forn(i,sz-1,0) A[++n]=(po){i,sz};
		Forn(i,sz-1,1) A[++n]=(po){0,i};
		int rr=0;
		For(i,1,n){
			if(rr<i+1) rr=i+1;
			while(1){
				int ok=1;
				int rid=(rr>n)?(rr-n):rr;
				For(j,1,m)
				if((A[rid]-A[i])*(B[j]-A[i])<0){
					ok=0;
					break;
				}
				if(ok){
					rr++;
				}else{
					rr--;
					break;
				}
			}
			f[i]=rr;
		}
		ll ans=0;
		int nowz=n,nowy=1;
		while((nowz-1>1)&&(f[nowz-1]>=n+1)) nowz--;
		l=1;r=0;
		For(x,1,n-2){
			for(;l<=r&&que[l]<=x;l++) sum -= val[l]+ tag;
			int D=0;
			for(;nowz+1<=n&&f[nowz]<x+n;nowz++,D++);
			if(f[nowz]<x+n) break;
			tag-=D; sum-=(ll)D*(r-l+1);
			for(;l<=r&&val[l]+tag<0;l++) sum-=val[l]+tag;
			while(f[x]>=nowy+1){
				nowy++;
				int tval=min(n,f[nowy])-nowz+1;
				if(tval>0){
					++r;
					que[r]=nowy;
					val[r]=tval-tag;
					sum+=tval;
				}
			}
			if(nowy==nowz) ans--;
			ans+=sum;
		}
		return ans;
	}
}s;