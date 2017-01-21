// BEGIN CUT HERE

// END CUT HERE
#line 5 "TPS.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;
const int maxn=55;

class TPS{
	int n;
	vector<int> edg[maxn];
	bool vis[maxn];
	int dfs(int u){
		vis[u]=1;
		int ret=0,v,cnt=0,tmp;
		for (int j=0;j<edg[u].size();++j)if (!vis[v=edg[u][j]]){
			if (!(tmp=dfs(v))) ++cnt;
			ret+=tmp;
		}
		ret+=max(cnt-1,0);
		return ret;
	}

	
	public:
	int minimalBeacons(vector <string> linked){
		n=linked.size();
		for (int i=0;i<n;++i)
			for (int j=0;j<n;++j)
				if (linked[i][j]=='Y')
					edg[i].push_back(j);
		int ret=n;
		for (int i=0;i<n;++i)if (edg[i].size()!=2){
			memset(vis,0,sizeof(vis));
			ret=min(ret,dfs(i)+(edg[i].size()==1));
//			if (ret==2) printf("%d\n",i);
		}
		return ret;
	}
};

//this is for test
/*
int main(){
	TPS test;
	vector<string> a;
	
	a.push_back("NYYNNNNNNNNY");
	a.push_back("YNNYNNNNYYNN");
	a.push_back("YNNNNNNNNNNN");
	a.push_back("NYNNNNYNNNNN");
	a.push_back("NNNNNNNNYNNN");
	a.push_back("NNNNNNNNNNNY");
	a.push_back("NNNYNNNNNNNN");
	a.push_back("NNNNNNNNNNNY");
	a.push_back("NYNNYNNNNNNN");
	a.push_back("NYNNNNNNNNYN");
	a.push_back("NNNNNNNNNYNN");
	a.push_back("YNNNNYNYNNNN");
	printf("%d\n",test.minimalBeacons(a));
//	test.run_test(-1);
	return 0;
}
*/
//test end
