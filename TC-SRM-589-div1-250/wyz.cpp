// BEGIN CUT HERE

// END CUT HERE
#line 5 "GooseTattarrattatDiv1.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=233;


class GooseTattarrattatDiv1{
	vector<int> e[maxn];
	int cnt[maxn];
	int dfs(int u,int &mx){
		if (!cnt[u]) return 0;
		int ret=cnt[u];
		mx=max(mx,cnt[u]);
		cnt[u]=0;
		for (int i=0;i<e[u].size();++i)
			ret+=dfs(e[u][i],mx);
		return ret;
	}
	public:
	int getmin(string S){
		memset(cnt,0,sizeof(cnt));
		for (int i=0;i<S.size();++i){
			e[S[i]].push_back(S[S.size()-i-1]);
			++cnt[S[i]];
		}
		int ret=0,mx;
		for (int i='a';i<='z';++i)if (cnt[i]){
			ret+=dfs(i,mx=0);
			ret-=mx;
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	GooseTattarrattatDiv1 test;
//	test.run_test(-1);
	return 0;
}
*/
//test end
