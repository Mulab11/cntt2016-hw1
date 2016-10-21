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
typedef vector<int> VI;
const DB pi=acos(-1.0);
const int N=15;
inline pii operator +(pii a,pii b){return pii(a.fi+b.fi,a.se+b.se);}
pii need[N];
pii give[N];
int white[N];
int R,G,W;
int n;
int f[1<<12][135];
pii sumneed[1<<12],sumgive[1<<12];
int sumwhite[1<<12];
int Main(){
	//printf("%d\n",N);
	memset(f,-1,sizeof f);
	rep(i,0,(1<<n)-1){
		rep(j,0,n-1)if(i&(1<<j)){
			sumneed[i]=sumneed[i]+need[j];
			sumgive[i]=sumgive[i]+give[j];
			sumwhite[i]+=white[j];
			//预处理所需要的钥匙数和提供的钥匙数的和
		}
	}
	f[0][R]=W;
	//f[S][RS]表示开了集合S的门，用了颜色R的钥匙刚好RS把，最多剩下的W钥匙有几把。
	rep(S,0,(1<<n)-1)rep(R,0,130)if(f[S][R]>=0){
		int W=f[S][R];
		int G=0;
		int all=sumgive[S].fi+sumgive[S].se+sumwhite[S]-(sumneed[S].fi+sumneed[S].se)+::R+::G+::W;//计算一共有多少钥匙
		G=all-W-R;//并通过总钥匙数计算出颜色为G的钥匙有几个
		rep(i,0,n-1)if(!(S&(1<<i))){
			if(R+G+W<need[i].fi+need[i].se)continue;
			if(R+W<need[i].fi)continue;
			if(G+W<need[i].se)continue;
			int nW=W+white[i];
			int nR=R-min(R,need[i].fi);
			if(need[i].fi>R)nW-=need[i].fi-R;
			if(need[i].se>G)nW-=need[i].se-G;
			nR+=give[i].fi;
			f[S+(1<<i)][nR]=max(f[S+(1<<i)][nR],nW);
			//枚举下个开的门，并转移。
		}
	}
	int ans=0;
	rep(S,0,(1<<n)-1)rep(R,0,130)if(f[S][R]>=0){
		int W=f[S][R];
		int G=0;
		int all=sumgive[S].fi+sumgive[S].se+sumwhite[S]-(sumneed[S].fi+sumneed[S].se)+::R+::G+::W;
		//printf("%d %d\n",S,all);
		G=all-W-R;
		ans=max(ans,R+G+W);
		//统计答案
	}
	return ans;
}
class KeyDungeonDiv1{
	public:
	int maxKeys(VI dr,VI dg,VI rr,VI rg,VI rw,VI keys){
		R=keys[0];
		G=keys[1];
		W=keys[2];
		n=dr.size();
		rep(i,0,n-1){
			need[i]=pii(dr[i],dg[i]);
			give[i]=pii(rr[i],rg[i]);
			white[i]=rw[i];
		}
		return Main();
	}
}gt;
int main(){
	printf("%d\n",gt.maxKeys(VI{1, 3, 9, 8, 10, 5, 9, 7, 1, 10},VI{9, 6, 9, 0, 3, 3, 10, 8, 4, 9},VI{0, 3, 3, 4, 6, 2, 1, 1, 2, 0},VI{1, 3, 2, 2, 5, 3, 4, 0, 0, 5},VI{6, 2, 1, 5, 2, 0, 6, 0, 2, 4}, VI{0, 4, 5}));
	return 0;
}


