// by ξ
// program sky  :)

#include <stdio.h>
#include <algorithm>
#include <functional>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)

using namespace std;

typedef long long LL;

const int mo=1e9+7;

inline void inc(int &x,int y){if((x+=y)>=mo)x-=mo;}
inline void dec(int &x,int y){if((x-=y)<0)x+=mo;}

inline int Pow(int x,int y,int mo){
	int z=1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}

int n,m,K,Ans,a[55],F[55],sky[55][55],binom[55][55],g[21][200000],q[21][200000],cnt[1100000],Q[1100000],lg[1100000];

// 行列式
inline int Gauss(int n){
	int res=1;
	For(i,1,n){
		if(!sky[i][i]){
			For(j,1,n)if(sky[j][i]){
				For(k,i,n)swap(sky[i][k],sky[j][k]);
				if(res)res=mo-res;
				break;
			}
		}
		if(!sky[i][i])return 0;
		int re=Pow(sky[i][i],mo-2,mo);
		res=1ll*res*sky[i][i]%mo;
		For(j,i,n)sky[i][j]=1ll*sky[i][j]*re%mo;
		For(j,i+1,n){
			int p=sky[j][i];
			For(k,i,n)dec(sky[j][k],1ll*p*sky[i][k]%mo);
		}
	}
	return res;
}

// 矩阵树定理
inline void suan(int k){
	For(i,1,n)For(j,1,n)sky[i][j]=0;
	For(i,1,n){
		if(i<=k){
			sky[i][i]=n-(m-k)-1;
			For(j,1,k)if(j^i)sky[i][j]=mo-1;
			For(j,m+1,n)sky[i][j]=mo-1;
		}else if(i<=m){
			sky[i][i]=n-m;
			For(j,m+1,n)sky[i][j]=mo-1;
		}else{
			sky[i][i]=n-1;
			For(j,1,n)if(j^i)sky[i][j]=mo-1;
		}
	}
	F[k]=Gauss(n-1);
	// 容斥
	rep(i,0,k)dec(F[k],1ll*binom[k][i]*F[i]%mo);
}

inline void gao(){
	// meet in the middle
	int s=m/2;
	For(i,0,m-s)lg[1<<i]=i;
	rep(i,0,1<<s){
		int &_=cnt[i],&t=Q[i];
		if(i==0)_=t=0;else{
			_=cnt[i-(i&-i)]+(a[lg[i&-i]+1]!=-1);
			t=Q[i-(i&-i)]+max(a[lg[i&-i]+1],0);
		}
		if(t<=K)g[_][++*g[_]]=t;
	}
	For(_,0,s)sort(g[_]+1,g[_]+*g[_]+1);

	// 前一半
	
	rep(i,0,1<<(m-s)){
		int &_=cnt[i],&t=Q[i];
		if(i==0)_=t=0;else{
			_=cnt[i-(i&-i)]+(a[lg[i&-i]+s+1]!=-1);
			t=Q[i-(i&-i)]+max(a[lg[i&-i]+s+1],0);
		}
		if(t<=K)q[_][++*q[_]]=t;
	}
	For(_,0,m-s)sort(q[_]+1,q[_]+*q[_]+1);
	
	// 后一半
	
	For(i,0,s){
		For(j,0,m-s){
			int p=*q[j];
			For(k,1,*g[i]){
				for(;p>0 && q[j][p]+g[i][k]>K;--p);
				inc(Ans,1ll*F[i+j]*p%mo);
				if(!p)break;
			}
		}
	}
	// 排序后拿指针单调扫合并答案
}

int Main(){
	For(i,1,n)if(~a[i])++m;
	sort(a+1,a+n+1,greater<int>());
	For(i,0,n){
		*binom[i]=1;
		For(j,1,i)binom[i][j]=(binom[i-1][j-1]+binom[i-1][j])%mo;
	}
	For(i,0,m)suan(i);
	gao();
	return Ans;
}

struct SweetFruits{
	int countTrees(vector <int> sweetness, int maxSweetness){
		n=sweetness.size();
		rep(i,0,n)a[i+1]=sweetness[i];
		K=maxSweetness;
		return Main();
	}
};