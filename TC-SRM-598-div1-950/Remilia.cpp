// by ξ
// program sky  :)

#include <bits/stdc++.h>

#define pb push_back
#define SZ(V) (int(V.size()))
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)

using namespace std;

typedef vector<int> VI;

int n,d[55];
VI li[55];

int dfs(int u,int ff=0){
	// 贪心
	int ans=0;bool flag=0;
	for(int v:li[u])if(v^ff){
		int tmp=dfs(v,u);
		// 非单链必满足
		if(tmp)ans+=tmp;
		else{
			// 单链不满足一条
			if(flag)++ans;
			else flag=1;
		}
	}
	return ans;
}

struct TPS{
	int minimalBeacons(vector<string> linked){
		n=SZ(linked);
		if(n==1)return 0;
		For(i,1,n)For(j,1,n)if(linked[i-1][j-1]=='Y')
			li[i].pb(j),++d[i];
		// 保证单链的转移
		For(i,1,n)if(d[i]>2){
			return dfs(i);
		}
		return 1;
	}
};