#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class SpellCards{
	static const int maxn=55;
	typedef vector<int> vi;
	int f[maxn][maxn],cost[maxn],val[maxn],n;
	int id[maxn];
	
	int solve(){
//		for (int i=0;i<n;++i) printf("%d ",id[i]);
//		puts("");
		for (int i=0;i<=n;++i)
		for (int j=0;j<=n;++j) f[i][j]=-1000000000;
		f[n][0]=0;
		int ret=0;
		for (int i=n-1;i>=0;--i){
			int c=cost[id[i]],w=val[id[i]];
			for (int j=0;j<=n-i;++j){
				f[i][j]=0;
				if (j>0) f[i][j]=max(f[i][j],f[i+1][j-1]);
				if (j+c<=n) f[i][j]=max(f[i][j],f[i+1][j+c-1]+w);
				ret=max(ret,f[i][j]);
			}
//			printf("%d:%d\n",i,f[i][0]);
		}
		return ret;
	}
	
	public:
	int maxDamage(vector<int> level, vector<int> damage){
		n=level.size();
		for (int i=0;i<n;++i) cost[i]=level[i],val[i]=damage[i];
		int ans=0;
		for (int i=0;i<n;++i){
			for (int j=0;j<n;++j) id[j]=(i+j)%n;
			ans=max(ans,solve());
//			break;
		}
		return ans;
	}
};
