// BEGIN CUT HERE

// END CUT HERE
#line 5 "MapGuessing.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int maxn=36;

class MapGuessing {
	ll ans;
	int n;
	bitset<maxn> b[maxn],now;
	void dfs(int u,int v,bitset<maxn> mask,int k){
		if (u==v){
			int cnt=0;
			for (int i=0;i<n;++i) cnt+=mask[i];
			ans+=((1LL<<cnt)-1)*k;
			return;
		}
		dfs(u+1,v,mask&b[u],-k);
		dfs(u+1,v,mask,k);
	}
	int _l,_r;
	pair<int,int> op[666];int m;
	bool _conflict[maxn];
	public:
	long long countPatterns(string goal, vector <string> code){
		_l=_r=0;
		int p=0;
		m=0;
		for (string i:code) for (char j:i)
			if (j=='<') _l=min(_l,--p);
			else if (j=='>') _r=max(_r,++p);
			else op[m++]=make_pair(p,j);
//		for (int j=0;j<m;++j) printf("%d %d\n",op[j].first,op[j].second);
		n=goal.size();
		ans=0;
		bool flag=0;
		for (int i=0;i<n;++i)if (i+_l>=0&&i+_r<n){
			flag=1;
			int cnt=0;
			now=b[i]=0;
			memset(_conflict,0,sizeof(_conflict));
			for (int j=0;j<m;++j){
				if (_conflict[i+op[j].first]) --cnt;
				_conflict[i+op[j].first]=goal[i+op[j].first]!=op[j].second;
				if (_conflict[i+op[j].first]) ++cnt;
//				printf("%d %d %d\n",i+op[j].first,(int)_conflict[i+op[j].first],cnt);
				now[i+op[j].first]=1;
				if (!cnt) b[i]=now;
			}
//			for (int j=0;j<n;++j) printf("%d",(int)b[i][j]);
//			puts("");
			dfs(max(-_l,i+_l-_r),i,b[i],1);
		}
		return ans+flag;
	}
};
