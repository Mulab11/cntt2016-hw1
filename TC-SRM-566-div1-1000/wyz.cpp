// BEGIN CUT HERE

// END CUT HERE
#line 5 "FencingPenguins.cpp"
#include <bits/stdc++.h>
#define ll long long
#define pi acos(-1.0)
#define P 100007

using namespace std;

inline double cross(double x0,double y0,double x1,double y1,double x2,double y2){
	return (x1-x0)*(y2-y0)-(x2-x0)*(y1-y0);
}

const int maxn=233;
const int maxc=52;

class FencingPenguins{
	ll bin[maxn];
	int n,m,col[maxn];
	double ax[maxn],ay[maxn];
	ll s[maxn][maxn],cs[maxn][maxn];
	ll f[maxn][maxn],g[maxn][maxn],h[maxn][maxn][2];
	bool valid[maxn][maxn];
	public:
	int countWays(int numPosts, int radius, vector <int> x, vector <int> y, string color){
		n=numPosts;
		for (int i=0;i<n;++i)
			ax[i]=1.0*radius*cos(2.0*i*pi/n),
			ay[i]=1.0*radius*sin(2.0*i*pi/n);
		m=x.size();
		for (int i=0;i<=maxc;++i) bin[i]=1LL<<i;
		for (int i=0;i<m;++i) col[i]=color[i]<'a'?color[i]-'A':(color[i]-'a'+26);
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			for (int k=0;k<m;++k) if (cross(ax[i],ay[i],ax[j],ay[j],x[k],y[k])>0)
				s[i][j]|=bin[k],cs[i][j]|=bin[col[k]];
		if (s[0][n-1]) return 0;
		for (int i=0;i<n;++i)for (int j=0;j<n;++j) valid[i][j]=!(cs[i][j]&cs[j][i]);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		memset(h,0,sizeof(h));
		for (int i=0;i<n;++i) h[i][i][1]=1;
		for (int len=1;len<n;++len)for (int i=0,j;(j=i+len)<n;++i){
			for (int k=0;k<2;++k)for (int l=i+1;l<=j;++l)if (valid[i][l]){
				ll tmp=h[l][j][k||(s[i][l]&s[l][j]&s[j][i])];
				if (!s[l][i]) h[i][j][k]+=tmp;
				else if (l-i>3&&!(s[l][i]&s[i+1][l-1])) h[i][j][k]+=tmp*f[i+1][l-1];
			}
			h[i][j][0]%=P;h[i][j][1]%=P;
			for (int k=i+2;k<=j;++k)if (valid[i][k]){
				if (!(s[j][i]&s[i][k])) g[i][j]+=h[i][k][0];
				else if (k<j-2&&!(s[j][i]&s[i][k]&s[k+1][j])) g[i][j]+=f[k+1][j]*h[i][k][0];
			}
			g[i][j]%=P;
			for (int k=i;k<=j;++k)
				if (!(s[j][i]&s[k][j]))
					f[i][j]+=g[k][j];
			f[i][j]%=P;
		}
		return (int)f[0][n-1];
	}
};
