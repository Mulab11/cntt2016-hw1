#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class InducedSubgraphs{
	private:
		static const int mod=1e9+9,maxn=48,inf=10000000;
		long long inv[maxn],fac[maxn];
		int n,head[maxn],nxt[maxn<<1],list[maxn<<1],tot;
		int dis[maxn][maxn];
		long long dp2[maxn][maxn][maxn][maxn],use[maxn][maxn];
		long long dp[maxn][maxn],siz[maxn][maxn];
		bool vis[maxn][maxn];
		
		void add(int a,int b){
			tot++;
			nxt[tot]=head[a];
			head[a]=tot;
			list[tot]=b;
			return;
		}
		
		long long power (long long a,int b){
			long long ret=1;
			while(b){
				if (b&1) ret=ret*a%mod;
				b>>=1;
				a=a*a%mod;
			}
			return ret;
		}
		
		void dfs1(int p,int fa){
			if (dp[fa][p]) return;
			dp[fa][p]=1;
			siz[fa][p]=1;
			for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa){
				int v=list[i];
				dfs1(v,p);
				dp[fa][p]=dp[fa][p]*dp[p][v]%mod*inv[siz[p][v]]%mod;
				siz[fa][p]+=siz[p][v];
			}
			dp[fa][p]=dp[fa][p]*fac[siz[fa][p]-1]%mod;
			return;
		}
		
		void dfs2(int p,int fa){
			if(vis[fa][p])return;
			vis[fa][p]=true;
			dp2[fa][p][0][0]=1;
			int sz=0;
			for(int i=head[p];i;i=nxt[i])if(list[i]!=fa){
				int v=list[i];
				dfs2(v,p);
				memset(use,0,sizeof(use));
				for(int a=0;a<=sz;++a)
				for(int b=0;b<=sz;++b)
				for(int c=0;c<=siz[p][v];++c)
				for(int d=0;d<=siz[p][v];++d)
				(use[a+c][b+d]+=dp2[fa][p][a][b]*dp2[p][v][c][d]%mod*inv[c]%mod*inv[d])%=mod;
				sz+=siz[p][v];
				for(int a=0;a<=sz;++a)
				for(int b=0;b<=sz;++b) dp2[fa][p][a][b]=use[a][b];
			}
			
			for(int i=0;i<=siz[fa][p];++i)
			for(int j=0;j<=siz[fa][p];++j)
			dp2[fa][p][i][j]=dp2[fa][p][i][j]*fac[i]%mod*fac[j]%mod;
			
			dp2[fa][p][0][siz[fa][p]]=dp2[fa][p][siz[fa][p]][0]=dp[fa][p];
			return;
		}
	
	public:
		int getCount(vector<int> edge1,vector<int> edge2,int K){
			fac[0]=1;
			for (int i=1;i<maxn;++i) fac[i]=fac[i-1]*i%mod;
			for (int i=0;i<maxn;++i) inv[i]=power(fac[i],mod-2);
			n=edge1.size()+1;
			if(K==1)return fac[n];
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) if (i!=j) dis[i][j]=inf;
			
			for (int i=0;i<edge1.size();++i){
				add(edge1[i],edge2[i]);
				add(edge2[i],edge1[i]);
				dis[edge1[i]][edge2[i]]=dis[edge2[i]][edge1[i]]=1;
			}
			for (int k=0;k<n;++k)
			for (int i=0;i<n;++i)
			for (int j=0;j<n;++j) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			
			for (int i=0;i<n;++i) dfs1(i,n);
			long long ans=0;
			if (K*2<=n){
				for (int i=0;i<n;++i)
				for (int j=0;j<n;++j) if(dis[i][j]==n-2*K+1){
					int st,ed;
					for (int k=head[i];k;k=nxt[k]) if (dis[list[k]][j]<dis[i][j]){
						st=list[k];
						break;
					}
					for (int k=head[j];k;k=nxt[k]) if (dis[list[k]][i]<dis[i][j]){
						ed=list[k];
						break;
					}
					if (siz[st][i]==K&&siz[ed][j]==K) (ans+=dp[st][i]*dp[ed][j])%=mod;
				}
			}
			else{
				for (int i=0;i<n;++i) dfs2(i,n);
				for (int i=0;i<n;++i) (ans+=dp2[n][i][n-K][n-K])%=mod;
				(ans*=fac[2*K-n-1])%=mod;
			}
			return ans;
		}
};
