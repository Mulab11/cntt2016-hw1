// BEGIN CUT HERE

// END CUT HERE
#line 5 "NewArenaPassword.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=66;

class NewArenaPassword{
	string st;
	int n,k;
	bool vis[maxn];
	int cnt[233];
	void dfs(int u){
		if (vis[u]) return;
		vis[u]=1;
		++cnt[(int)st[u]];
		if (u<k) dfs(n-k+u);
		if (u>=n-k) dfs(u+k-n);
	}
	public:
	int minChange(string oldPassword, int K){
		st=oldPassword;
		k=K;
		n=st.size();
		int ret=min(n,K*2);
		memset(vis,0,sizeof(vis));
		for (int i=0;i<K;++i)if (!vis[i]){
			memset(cnt,0,sizeof(cnt));
			dfs(i);
			int mx=0;
			for (int i='a';i<='z';++i)mx=max(mx,cnt[i]);
			ret-=mx;
		}
		return ret;
	}
};
