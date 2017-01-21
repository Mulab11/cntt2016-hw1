// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinSledding.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class PenguinSledding{
	ll bin[maxn];
	int n;
	bool g[maxn][maxn];
	int dgr[maxn];
	public:
	long long countDesigns(int numCheckpoints, vector <int> checkpoint1, vector <int> checkpoint2){
		n=numCheckpoints;
		for (int i=0;i<=n;++i) bin[i]=1LL<<i;
		memset(g,0,sizeof(g));
		memset(dgr,0,sizeof(dgr));
		for (int i=0;i<checkpoint1.size();++i){
			g[checkpoint1[i]-1][checkpoint2[i]-1]=g[checkpoint2[i]-1][checkpoint1[i]-1]=1;
			++dgr[checkpoint1[i]-1];
			++dgr[checkpoint2[i]-1];
		}
		ll ret=0;
		for (int i=0;i<n;ret+=bin[dgr[i++]]-1)for (int j=i+1;j<n;++j)for (int k=j+1;k<n;++k)
			if (g[i][j]&&g[j][k]&&g[k][i]) ++ret;
		
		return ret-checkpoint1.size()+1;
	}
};
