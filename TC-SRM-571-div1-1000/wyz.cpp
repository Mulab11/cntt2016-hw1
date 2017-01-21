// BEGIN CUT HERE

// END CUT HERE
#line 5 "CandyOnDisk.cpp"
#include <bits/stdc++.h>
#define ll long long
#define eps (1e-8)

using namespace std;
inline double _dist(const double &x,const double &y){return sqrt(x*x+y*y);}
inline void Min(double &x,double y){if (y<x) x=y;}
inline void Max(double &x,double y){if (y>x) x=y;}


const int maxn=52;

class CandyOnDisk{
	int n;
	double dis[maxn][maxn];
	int q[maxn*maxn*maxn],qh,qt;
	double lb[maxn],rb[maxn];
	bool exist[maxn];
	bool flag[maxn][maxn];
	public:
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
		if (sx==tx&&sy==ty) return "YES";
		n=x.size();
		for (int i=0;i<n;++i)for (int j=i+1;j<n;++j)
			if (x[i]==x[j]&&y[i]==y[j]){
				int k=r[i]<r[j]?i:j;
				swap(x[k],x[n-1]);
				swap(y[k],y[n-1]);
				swap(r[k],r[n-1]);
				--n;
				--i;
				break;
			}
		for (int i=0;i<n;++i)for (int j=0;j<n;++j)
			dis[i][j]=_dist(x[i]-x[j],y[i]-y[j]);
		qh=qt=0;
		memset(exist,0,sizeof(exist));
		for (int i=0;i<n;++i){
			double tmp=_dist(x[i]-sx,y[i]-sy);
			if (tmp-eps<r[i]) lb[i]=rb[i]=tmp,q[++qt]=i,exist[i]=1;
			else lb[i]=r[i],rb[i]=0;
		}
		memset(flag,0,sizeof(flag));
		while (qh<qt){
			int u=q[++qh];
			exist[u]=0;
			for (int v=0;v<n;++v){
				if (u==v||flag[u][v]) continue;
//				[lb[u],rb[u]] [dis[u][v]-r[v],dis[u][v]+r[v]]
				if (rb[u]+eps<dis[u][v]-r[v]||dis[u][v]+r[v]+eps<lb[u]) continue;
				flag[u][v]=flag[v][u]=1;
				
				Min(lb[u],dis[u][v]-r[v]);
				Max(lb[u],0);
				Max(rb[u],dis[u][v]+r[v]);
				Min(rb[u],r[u]);
				exist[u]=1;
				q[++qt]=u;
				
				Min(lb[v],dis[u][v]-r[u]);
				Max(lb[v],0);
				Max(rb[v],dis[u][v]+r[u]);
				Min(rb[v],r[v]);
				if (!exist[v]) exist[q[++qt]=v]=1;
			}
		}
		for (int i=0;i<n;++i){
			double tmp=_dist(x[i]-tx,y[i]-ty);
			if (lb[i]-eps<tmp&&tmp<rb[i]+eps) return "YES";
		}
		return "NO";
	}
};
