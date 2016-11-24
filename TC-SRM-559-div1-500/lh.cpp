#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class HatRack{
	static const int maxn=55;
	int head[maxn],list[maxn<<1],nxt[maxn<<1],tot;
	bool check[maxn];
	long long dp[maxn];
	int dep[maxn];
	
	inline void add(int a,int b){
		tot++;
		nxt[tot]=head[a];
		head[a]=tot;
		list[tot]=b;
		return;
	}
	
	void dfs(int p,int fa){
		dp[p]=0;
		int num=0;
		for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa){
			dfs(list[i],p);
			++num;
		}
		if (num==0){
			dp[p]=1;
			check[p]=true;
			dep[p]=1;
		}
		else if (num==1){
			for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa){
				if (check[list[i]]&&dep[list[i]]==1){
					check[p]=false;
					dep[p]=dep[list[i]]+1;
					dp[p]=dp[list[i]];
				}
				else{
					dp[p]=0;
					dep[p]=-1;
					check[p]=false;
				}
			}
		}
		else if (num==2){
			int a=0,b=0;
			for (int i=head[p];i;i=nxt[i]) if (list[i]!=fa){
				if (a==0) a=list[i];
				else b=list[i];
			}
			if (abs(dep[a]-dep[b])>1){
				dp[p]=0;
				dep[p]=-1;
				check[p]=false;
			}
			if (check[a]&&check[b]){
				if (dep[a]==dep[b]){
					dp[p]=2ll*dp[a]*dp[b];
					check[p]=true;
					dep[p]=dep[a]+1;
				}
				else if (abs(dep[a]-dep[b])==1){
					dp[p]=dp[a]*dp[b];
					dep[p]=max(dep[a],dep[b])+1;
					check[p]=false;
				}
				return;
			}
			
			if (check[a]){
				if (dep[a]==dep[b]) dp[p]+=dp[a]*dp[b];
				if (dep[a]==dep[b]-1) dp[p]+=dp[a]*dp[b];
			}
			else if (check[b]){
				if (dep[a]==dep[b]) dp[p]+=dp[a]*dp[b];
				if (dep[b]==dep[a]-1) dp[p]+=dp[a]*dp[b];
			}
			else dp[p]=0;
			check[p]=false;
			dep[p]=max(dep[a],dep[b])+1;
		}
		else{
			dp[p]=0;
			dep[p]=-1;
		}
		return;
	}
	
	public:
		long long countWays(vector<int> knob1, vector<int> knob2){
			long long ans=0;
			int n=knob1.size();
			for (int i=0;i<n;++i){
				add(knob1[i],knob2[i]);
				add(knob2[i],knob1[i]);
			}
			++n;
			for (int i=1;i<=n;++i){
				dfs(i,0);
				ans+=dp[i];
			}
			return ans;
		}
};
