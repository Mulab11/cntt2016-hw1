// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulWolves.cpp"
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn=55;

class ColorfulWolves{
	int n;
	int g[maxn][maxn];
	int mind[maxn];
	bool flag[maxn];
	public:
	int getmin(vector <string> colormap){
		memset(g,63,sizeof(g));
		n=colormap.size();
		for (int i=0;i<n;++i){
			int cost=0;
			for (int j=0;j<n;++j)if (colormap[i][j]=='Y')
				g[i][j]=cost++;
		}
		memset(mind,63,sizeof(mind));
		memset(flag,0,sizeof(flag));
		mind[0]=0;
		for (;!flag[n-1];){
			int k=n;
			for (int i=0;i<n;++i)
				if (!flag[i]&&mind[i]<mind[k])
					k=i;
			if (k==n) break;
			flag[k]=1;
			for (int i=0;i<n;++i)
				mind[i]=min(mind[i],mind[k]+g[k][i]);
		}
		return mind[n-1]>n*n?-1:mind[n-1];
	}
};
