// BEGIN CUT HERE

// END CUT HERE
#line 5 "PastingPaintingDivOne.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class PastingPaintingDivOne{
	int a[maxn][maxn];
//	int l[maxn],r[maxn];
	int r,c;
	public:
	vector<long long> countColors(vector <string> clipboard, int T){
		vector<ll> ret;
		for (int i=0;i<3;++i) ret.push_back(0);
		r=clipboard.size();
		c=clipboard[0].size();
		for (int i=0;i<r;++i)for (int j=0;j<c;++j)
			if (clipboard[i][j]=='R') a[i][j]=0;
			else if (clipboard[i][j]=='G') a[i][j]=1;
			else if (clipboard[i][j]=='B') a[i][j]=2;
			else a[i][j]=-1;
		
		for (int i=r-1,j=0;i>=0;(j<c-1)?(++j):(--i)){
			int x=i,y=j,last=-1,x0=-1;
			for (;x>=0&&y>=0;--x,--y){
				if (a[x][y]>=0) last=a[x][y],x0=x;
				if (last>=0&&T-1+x>=x0) ++ret[last];
			}
			if (last>=0) ret[last]+=T+x-x0;
		}
		return ret;
	}
};
