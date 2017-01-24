#include <vector>
#define ll long long
#define MOD 1000000009
using namespace std;
class InducedSubgraphs{
public:
	int n,k;
	struct edge{int to;edge*next;}E[100],*ne,*first[50];
	void link(int a,int b){*ne=(edge){b,first[a]};first[a]=ne++;}
	// fac[i]=i! ifac[i]=1/fac[i] inv[i]=1/i
	ll fac[50],ifac[50],inv[50];
	ll get_inv(int a,int p){return a==1?1:(1+p*(a-get_inv(p%a,a)))/a%p;}
	void init(){ // 预处理阶乘及逆元
		for(int i=*fac=1;i<=n;i++)fac[i]=fac[i-1]*i%MOD;
		ifac[n]=get_inv(fac[n],MOD);
		for(int i=n;i;i--)ifac[i-1]=ifac[i]*i%MOD,inv[i]=fac[i-1]*ifac[i]%MOD;
	}
	// siz[i]:i子树大小
	// f[i]:i子树满足任何点祖先在其前面的合法遍历序数/siz[i]!，fv[i]=1/f[i]
	// g[i][a][b]:i子树内不相交点集对(A,B)(i属于A,不经过A连通的点对同时属于或不属于B,|A|=a,|B|=b)A补集中遍历序个数和/(n-k)!^2
	// h[a][b]:用于转移的数组
	int siz[50];
	ll f[50],fv[50],g[50][50][50],h[50][50],ans;
	void init(int i,int fa){ // 预处理树形DP
		siz[i]=f[i]=fv[i]=1;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			init(e->to,i);
			siz[i]+=siz[e->to];
			(f[i]*=f[e->to])%=MOD;
			(fv[i]*=fv[e->to])%=MOD;
		}
		(f[i]*=inv[siz[i]])%=MOD;
		(fv[i]*=siz[i])%=MOD;
	}
	// 对于2k>n的情况，树形DP求出答案
	void dfs1(int i,int fa,ll ff){ // 树形DP求出g，ff为i的上方部分遍历序数/(n-siz[i])!
		siz[i]=g[i][1][0]=1;
		ll tmp=ff;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa)(tmp*=f[e->to])%=MOD;
		for(edge*e=first[i];e;e=e->next)if(e->to!=fa){
			dfs1(e->to,i,tmp*fv[e->to]%MOD*inv[n-siz[e->to]]%MOD);
			// A包含to，将g[to]方案数转移给g[i]
			for(int a1=1;a1<=siz[i];a1++)
				for(int a2=1;a2<=siz[e->to]&&a1+a2<=2*k-n;a2++)
					for(int b1=0;a1+b1<=siz[i]&&b1<=n-k;b1++)
						for(int b2=0;a2+b2<=siz[e->to]&&b2<=n-k;b2++)
							(h[a1+a2][b1+b2]+=g[i][a1][b1]*g[e->to][a2][b2])%=MOD;
			// A不包含to，将g[i]乘上f[to]转移给g[i]
			for(int a=1;a<=siz[i];a++)
				for(int b=0;a+b<=siz[i]&&b+siz[e->to]<=n-k;b++)
					(h[a][b+siz[e->to]]+=g[i][a][b]*f[e->to])%=MOD;
			for(int a=1;a<=siz[i]+siz[e->to]&&a<=2*k-n;a++)
				for(int b=0;a+b<=siz[i]+siz[e->to]&&b<=n-k;b++)
					((g[i][a][b]*=f[e->to])+=h[a][b])%=MOD,h[a][b]=0;
			siz[i]+=siz[e->to];
		}
		// 更新答案
		(ans+=g[i][2*k-n][n-k]*ff)%=MOD;
		if(i&&siz[i]>=k)(ans+=g[i][2*k-n][siz[i]-k]*ff)%=MOD;
	}
	// 对于2k<=n的情况，枚举[0,k)[n-k,n)的连通块更新答案
	void dfs2(int i,int fa,int dep,ll ff){
		if(siz[i]<k)return;
		if(dep==n-2*k+1){
			if(siz[i]>k)return;
			(ans+=ff*f[i])%=MOD;
		}
		else if(fa==-1){
			for(edge*e=first[i];e;e=e->next)(ff*=f[e->to])%=MOD;
			for(edge*e=first[i];e;e=e->next){
				if(siz[e->to]==n-k)dfs2(e->to,i,dep+1,ff*fv[e->to]%MOD);
			}
		}
		else for(edge*e=first[i];e;e=e->next)
			if(e->to!=fa)dfs2(e->to,i,dep+1,ff);
	}
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		this->n=edge1.size()+1;this->k=k;ne=E;ans=0;
		for(int i=0;i<edge1.size();i++)link(edge1[i],edge2[i]),link(edge2[i],edge1[i]);
		init();
		if(k==1)return fac[n];
		if(2*k>n){
			init(0,-1);
			dfs1(0,-1,1);
			return ans*fac[2*k-n]%MOD*fac[n-k]%MOD*fac[n-k]%MOD;
		}
		for(int i=0;i<n;i++){
			init(i,-1);
			dfs2(i,-1,0,inv[k]);
		}
		return ans*fac[k]%MOD*fac[k]%MOD;
	}
};
