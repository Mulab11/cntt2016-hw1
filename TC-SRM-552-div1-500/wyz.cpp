// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndFlowerShopDivOne.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;

void Max(int &x,int y){if (y>x)x=y;}

const int maxn=33;
const int maxk=1805;

class FoxAndFlowerShopDivOne {
	int s[maxn][maxn];
	int a[maxn][maxn];
	int utmp[maxn][maxk],u[maxn][maxk],dtmp[maxn][maxk],d[maxn][maxk];
	int ltmp[maxn][maxk],l[maxn][maxk],rtmp[maxn][maxk],r[maxn][maxk];
	int n,m;
	public:
	int theMaxFlowers(vector <string> flowers, int maxDiff){
		memset(s,0,sizeof(s));
		memset(a,0,sizeof(a));
		memset(ltmp,192,sizeof(l)*2);
		memset(rtmp,192,sizeof(r)*2);
		memset(utmp,192,sizeof(u)*2);
		memset(dtmp,192,sizeof(d)*2);
		n=flowers.size();
		m=flowers[0].size();
		for (int i=1;i<=n;++i)for (int j=1;j<=m;++j){
			s[i][j]=(flowers[i-1][j-1]!='L'?flowers[i-1][j-1]=='P':-1)+s[i-1][j]+s[i][j-1]-s[i-1][j-1];
			a[i][j]=(flowers[i-1][j-1]!='.')+a[i-1][j]+a[i][j-1]-a[i-1][j-1];
			for (int x=0;x<i;++x)for (int y=0;y<j;++y){
				int dlt=s[i][j]-s[x][j]-s[i][y]+s[x][y];
				int cnt=a[i][j]-a[x][j]-a[i][y]+a[x][y];
				Max(u[i][dlt],cnt);
				Max(d[x][dlt],cnt);
				Max(l[j][dlt],cnt);
				Max(r[y][dlt],cnt);
			}
		}
		for (int k=-n*m;k<=n*m;++k){
			for (int i=1;i<=n;++i) Max(u[i][k],u[i-1][k]);
			for (int i=n-1;i>=0;--i) Max(d[i][k],d[i+1][k]);
			for (int i=1;i<=m;++i) Max(l[i][k],l[i-1][k]);
			for (int i=m-1;i>=0;--i) Max(r[i][k],r[i+1][k]);
		}
		int ret=-1;
		for (int i=0;i<=n;++i)
			for (int k=-n*m;k<=n*m;++k)
				for (int j=max(-n*m,-maxDiff-k);j<=maxDiff-k&&j<=n*m;++j)
					Max(ret,u[i][k]+d[i][j]);
		for (int i=0;i<=m;++i)
			for (int k=-n*m;k<=n*m;++k)
				for (int j=max(-n*m,-maxDiff-k);j<=maxDiff-k&&j<=n*m;++j)
					Max(ret,l[i][k]+r[i][j]);
		return ret;
	}
};
