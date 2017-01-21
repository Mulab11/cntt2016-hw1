// BEGIN CUT HERE

// END CUT HERE
#line 5 "BallsSeparating.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=55;

class BallsSeparating {
	vector<int> a[3];
	bool used[maxn];
	int n,t;
	int b[3];
	int ans;
	void dfs(int u){
		if (u==t){
			int res=0;
			for (int i=0;i<n;++i){
				int mx=0;
				for (int j=0;j<t;mx=max(mx,a[j++][i]))
					if (b[j]!=i) res+=a[j][i];
				if (!used[i]) res-=mx;
			}
			ans=min(ans,res);
			return;
		}
		for (int i=0;i<n;++i)if (!used[i]){
			used[i]=1;
			b[u]=i;
			dfs(u+1);
			used[i]=0;
		}
	}
	public:
	int minOperations(vector <int> red, vector <int> green, vector <int> blue){
		n=red.size();t=0;
		bool found=0;
		for (int i=0;!found&&i<n;++i)if (red[i])found=1;
		if (found) a[t++]=red;
		found=0;
		for (int i=0;!found&&i<n;++i)if (green[i])found=1;
		if (found) a[t++]=green;
		found=0;
		for (int i=0;!found&&i<n;++i)if (blue[i])found=1;
		if (found) a[t++]=blue;
		if (t>n) return -1;
		memset(used,0,sizeof(used));
		ans=1e9;
		dfs(0);
		return ans;
	}
};
