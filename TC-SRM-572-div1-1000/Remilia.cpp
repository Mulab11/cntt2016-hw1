// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <cassert>
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

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<PII> VII;

int n,Nc,Pc,Ans,A[88];

void upd(int x){
	// renew the answer
	if(Ans==-1 || x<Ans)Ans=x;
}

bool ok(int l,int r){
	// forall i,j\in[l,r] ,i<j so that A[i]<=A[j]
	int la=0;
	For(i,l,r)if(A[i]){
		if(A[i]<la)return 0;
		la=A[i];
	}
	return 1;
}

void gao1(){
	// do not use a->z & z->a
	int res=0;
	if(!ok(1,26))return;
	For(i,1,26)if(A[i]){
		for(int c=i;c^A[i];){
			if(c<A[i])
				res+=Nc,++c;
			else
				res+=Pc,--c;
			if(A[c]==A[i])break;
		}
	}
	upd(res);
}

void gao2(){
	// a prefix use a->z
	int ma=[](){dto(i,26,1)if(A[i])return A[i];}();
	For(i,1,26)if(A[i]){
		if(A[i]<ma)return;
		if(!ok(1,i))return;
		if(!ok(i+1,26))continue;
		int res=0;
		For(j,i+1,26)if(A[j]){
			for(int c=j;c^A[j];){
				if(c<A[j])
					res+=Nc,++c;
				else
					res+=Pc,--c;
				if(A[c]==A[j])break;
			}
		}
		int k=1;for(;!A[k];++k);
		res+=k*Pc;
		for(int j=26;(j<=k || A[j]^A[k]) && j^A[k];--j)res+=Pc;
		For(j,k+1,i)if(A[j]){
			for(int c=j;c>1;){
				res+=Pc;
				--c;
				if(A[c]==A[j])break;
				if(c==1)res+=Pc*(27-A[j]);
			}
		}
		upd(res);
	}
}

void gao3(){
	// a suffix use z->a
	int mi=[](){For(i,1,26)if(A[i])return A[i];}();
	dto(i,26,1)if(A[i]){
		if(A[i]>mi)return;
		if(!ok(i,26))return;
		if(!ok(1,i-1))continue;
		int res=0;
		For(j,1,i-1)if(A[j]){
			for(int c=j;c^A[j];){
				if(c<A[j])
					res+=Nc,++c;
				else
					res+=Pc,--c;
				if(A[c]==A[j])break;
			}
		}
		int k=26;for(;!A[k];--k);
		res+=Nc*(27-k);
		for(int j=1;(j>=k || A[j]^A[k]) && j^A[k];++j)res+=Nc;
		rep(j,i,k)if(A[j]){
			for(int c=j;c<26;){
				res+=Nc;
				++c;
				if(A[c]==A[j])break;
				if(c==26)res+=A[j]*Nc;
			}
		}
		upd(res);
	}
}

void gao4(){
	// all of them use a->z
	For(i,1,26)A[i+26]=A[i];
	For(i,1,26)if(ok(i,i+25))goto lp1;
	return;
	lp1:;
	int res=0;
	For(j,1,26)if(A[j]){
		bool flag=1,rr=0;
		for(int c=j;;){
			if(c==A[j] && rr)break;
			res+=Pc;
			--c;
			if(c==0)c=26,rr=1;
			if(A[c]==A[j] && flag)break;
			if(A[c])flag=1;
		}
	}
	upd(res);
}

void gao5(){
	// all of them use z->a
	For(i,1,26)A[i+26]=A[i];
	For(i,1,26)if(ok(i,i+25))goto lp2;
	return;
	lp2:;
	int res=0;
	For(j,1,26)if(A[j]){
		bool flag=1,rr=0;
		for(int c=j;;){
			if(c==A[j] && rr)break;
			res+=Nc;
			++c;
			if(c==27)c=1,rr=1;
			if(A[c]==A[j] && flag)break;
			if(A[c])flag=0;
		}
	}
	upd(res);
}

int xjb[27];

int Main(){
	For(i,1,26)xjb[A[i]]=1;
	For(i,1,26)if(!A[i] || !xjb[i])goto loop;
	return -1;
	loop:;
	Ans=-1;
	gao1();
	gao2();
	gao3();
	gao4();
	gao5();
	return Ans;
}

struct NextAndPrev{
	int getMinimum(int nextCost,int prevCost,string start,string goal){
		if(start==goal)return 0;
		Nc=nextCost;
		Pc=prevCost;
		n=SZ(start);
		rep(i,0,n){
			int u=start[i]-'a'+1,v=goal[i]-'a'+1;
			if(A[u] && A[u]^v)return -1;
			A[u]=v;
		}
		return Main();
	}
};