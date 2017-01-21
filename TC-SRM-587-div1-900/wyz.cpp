// BEGIN CUT HERE

// END CUT HERE
#line 5 "ThreeColorability.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=105;


class ThreeColorability {
	int a[maxn][maxn],n,m;
	int r[maxn][maxn],c[maxn][maxn];
	bool build(int x,int y){
		if (a[x][y]<0) return 0;
		for (int i=0;i<n;++i)if (a[i][y]>=0){
			if (r[i][x]<0) r[x][i]=r[i][x]=a[i][y]^a[x][y];
			else if (r[i][x]!=(a[i][y]^a[x][y])) return 1;
		}
		for (int k=0;k<n;++k)for (int i=0;i<n;++i){
			if (r[i][k]<0||r[x][k]<0) continue;
			if (r[x][i]<0) r[i][x]=r[x][i]=r[i][k]^r[x][k];
			else if (r[x][i]!=(r[i][k]^r[x][k])) return 1;
		}
		for (int i=0;i<n;++i)for (int j=0;j<n;++j){
			if (r[i][x]<0||r[x][j]<0) continue;
			if (r[i][j]<0) r[i][j]=r[i][x]^r[x][j];
			else if (r[i][j]!=(r[i][x]^r[x][j])) return 1;
		}
		for (int j=0;j<m;++j)if (a[x][j]>=0){
			if (c[j][y]<0) c[y][j]=c[j][y]=a[x][j]^a[x][y];
			else if (c[j][y]!=(a[x][j]^a[x][y])) return 1;
		}
		for (int k=0;k<m;++k)for (int j=0;j<m;++j){
			if (c[j][k]<0||c[y][k]<0) continue;
			if (c[y][j]<0) c[j][y]=c[y][j]=c[j][k]^c[y][k];
			else if (c[y][j]!=(c[j][k]^c[y][k])) return 1;
		}
		for (int i=0;i<m;++i)for (int j=0;j<m;++j){
			if (c[i][y]<0||c[y][j]<0) continue;
			if (c[i][j]<0) c[i][j]=c[i][y]^c[y][j];
			else if (c[i][j]!=(c[i][y]^c[y][j])) return 1;
		}
		return 0;
	}
	void calc(int x,int y){
		if (a[x][y]>=0) return;
		for (int i=0;i<n;++i)if (a[i][y]>=0&&r[i][x]>=0){
			a[x][y]=a[i][y]^r[i][x];
			return;
		}
		for (int j=0;j<m;++j)if (a[x][j]>=0&&c[j][y]>=0){
			a[x][y]=a[x][j]^c[j][y];
			return;
		}
	}
	public:
	vector <string> lexSmallest(vector <string> cells){
		vector<string> ret;
		n=cells.size();
		m=cells[0].size();
		memset(r,-1,sizeof(r));
		memset(c,-1,sizeof(c));
		memset(a,-1,sizeof(a));
		for (int i=0;i<n;++i)for (int j=0;j<m;++j){
			a[i][j]=cells[i][j]!='?'?cells[i][j]=='Z':-1;
//			printf("%d %d\n",i,j);
			if (build(i,j)) return ret;
		}
//		for (int i=0;i<n;++i,puts(""))for (int j=0;j<n;++j)printf("%d ",r[i][j]);
//		for (int i=0;i<m;++i,puts(""))for (int j=0;j<m;++j)printf("%d ",c[i][j]);
		for (int i=0;i<n;++i)for (int j=0;j<m;++j)if (a[i][j]<0){
			calc(i,j);
			a[i][j]=max(a[i][j],0);
			if (build(i,j)) return ret;
		}
		for (int i=0;i<n;++i){
			string st;
			for (int j=0;j<m;++j) st.push_back(a[i][j]?'Z':'N');
			ret.push_back(st);
		}
		return ret;
	}
};
