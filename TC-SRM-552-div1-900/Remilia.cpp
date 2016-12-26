// by ξ
// program sky  :)

#include <vector>
#include <stdio.h>
#include <algorithm>

#define Rin register int
#define oo (c=getchar())
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define ALL(V) V.begin(),V.end()
#define pb push_back
#define mk make_pair
#define x first
#define y second
#define SZ(V) (int(V.size()))

using namespace std;

typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef pair<db ,db> cpx;
typedef vector<int> VI;
typedef vector<LL> VL;
typedef vector<PII> VII;

int S,pr[200010],pos[200010],smi[200010];
LL NP,N,f[200010],F[200010];
VL li;
inline void init(){
	rep(i,1,SZ(li))F[i]=pos[i]=0;
	For(i,1,S)smi[i]=0;*pr=0;
	li.resize(0);
	//初始化
}
inline int id(LL x){
	return x<=S?x:SZ(li)-N/x;
	//离散
}
inline LL Cnt(LL x){
	x=id(x);return F[x]+pos[x]-1;
	//质数个数
}
inline void sieve(){
	for(S=2;1ll*S*S<=N;++S){
		if(!smi[S])pr[++*pr]=smi[S]=S;
		for(int j=1;j<=*pr && pr[j]<=smi[S] && 1ll*pr[j]*pr[j]*S*S<=N;++j)
			smi[pr[j]*S]=pr[j];
	}--S;
	//欧拉筛
	li.pb(0);For(i,1,S)li.pb(i);
	dto(i,S-(S==N/S),1)li.pb(N/i);
	//合法状态
	rep(i,1,SZ(li)){
		F[i]=li[i];
		for(int &j=pos[i]=pos[i-1];j<*pr && 1ll*pr[j+1]*pr[j+1]<=li[i];++j);
	}
	//开根
	For(i,1,*pr){
		for(int j=SZ(li)-1;pos[j]>=i;--j){
			int k=id(li[j]/pr[i]);
			if(i-1>pos[k])F[j]-=F[k]-i+1+pos[k];
			else F[j]-=F[k];
			//DP筛质数
		}
	}
	//O(N^0.75/log N)
}

LL Main(){
	rep(i,1,SZ(li))f[i]=1;LL tmp=NP<*pr?NP:*pr;
	dto(i,tmp,0){
		for(int j=SZ(li)-1;j && pos[j]>=i;--j){
			if(i+1>pos[j])f[j]=max(0ll,min(Cnt(li[j]),tmp)-i)+1;//初始化f[j]=f'[j]
			if(!i)continue;
			LL pc=1ll*pr[i]*pr[i];
			for(LL jj=li[j]/pr[i];jj;jj/=pc){
				int k=id(jj);
				if(i+1>pos[k])f[j]+=max(0ll,min(Cnt(jj),tmp)-i)+1;
				else f[j]+=f[k];
				//背包合法的个数
			}
		}
	}
	LL res=f[SZ(li)-1];
	if(Cnt(S)<NP)
	for(LL i=S+1,j;i<=N;i=j+1){
		j=N/(N/i);
		if(Cnt(j)<=NP)
			res+=(Cnt(j)-Cnt(i-1))*f[id(N/i)];
		else{
			res+=(NP-Cnt(i-1))*f[id(N/i)];
			break;
		}
		//<=sqrt n的质数拼出的数配上一个>sqrt n的质数统计答案
	}
	return res;
}

struct HolyNumbers{
	LL count(LL upTo, int mp){
		if(upTo<mp)mp=upTo;
		N=mp;sieve();NP=Cnt(N);//求出mp以内的质数个数
		init();N=upTo;sieve();//求出所有floor(n/x)以内的质数个数
		return Main();
	}
};