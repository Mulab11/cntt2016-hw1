// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicMolecule.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class MagicMolecule{
	pair<int,int> p[maxn*maxn];
	int m;
	int n,w[maxn];
	int res;
	bool flag[maxn];
	void dfs(int u,int now,int left){
		if (u==m){
			res=min(res,now);
			return;
		}
		int x=p[u].first,y=p[u].second;
		if (left==0&&!flag[x]&&!flag[y]) return;
		if (flag[x]||flag[y]) dfs(u+1,now,left);
		else for (int kk=0;kk<2;++kk,swap(x,y)){
			flag[x]=1;
			dfs(u+1,now+w[x],left-1);
			flag[x]=0;
		}
	}
	public:
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond){
		n=magicPower.size();
		int sum=0;
		for (int i=0;i<n;++i)
			sum+=(w[i]=magicPower[i]);
		m=0;
		for (int i=0;i<n;++i)
			for (int j=i+1;j<n;++j)if (magicBond[i][j]=='N')
				p[m++]=make_pair(i,j);
		res=sum+1;
		memset(flag,0,sizeof(flag));
		dfs(0,0,n/3);
		return sum-res;
	}
};
