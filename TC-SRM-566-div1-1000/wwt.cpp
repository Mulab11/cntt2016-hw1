#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 505,mo = 100007;
const double pi = acos(-1);

struct node
{
	double x,y;

	node(void){}
	node(double a,double b) : x(a),y(b){}
};

node operator +(const node &a,const node &b) {return node(a.x + b.x,a.y + b.y);}
node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}
node operator *(const node &a,const double &b) {return node(a.x * b,a.y * b);}
node operator *(const double &a,const node &b) {return b * a;}
double operator *(const node &a,const node &b) {return a.x * b.x + a.y * b.y;}
double operator ^(const node &a,const node &b) {return a.x * b.y - a.y * b.x;}

node p[maxn];
bool ok[maxn][maxn];
int c[maxn],h[maxn][maxn][2],f[maxn][maxn],g[maxn][maxn];
ll ap[maxn][maxn],cap[maxn][maxn];

class FencingPenguins
{
public:

	int countWays(int n, int radius, vector <int> x, vector <int> y, string color)
	{
		int m = x.size();
		for(int i = 0;i < n;i ++)
			p[i] = radius * node(cos(i * 2 * pi / n),sin(i * 2 * pi / n));
		for(int i = 0;i < m;i ++)
		{
			if (color[i] >= 'a' && color[i] <= 'z')
				c[i] = color[i] - 'a'; else
					c[i] = color[i] - 'A' + 26;
		}
		//令ap[l][r]表示在l->r右侧的点集，cap[l][r]表示颜色集合
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < n;j ++)
				if (i != j)
					for(int k = 0;k < m;k ++)
						if (((node(x[k],y[k]) - p[i]) ^ (p[j] - p[i])) > 0)
						{
							ap[i][j] |= (1ll << k);
							cap[i][j] |= (1ll << c[k]);
						}
		if (ap[0][n - 1] != (1ll << m) - 1) return 0;
		for(int i = 0;i < n;i ++)
			for(int j = i + 1;j < n;j ++)
				if (cap[i][j] & cap[j][i]) ok[i][j] = 0; else ok[i][j] = 1;
		//h[l][r][0..1]表示考虑l->r右侧的点，l->r这条边固定存在凸包上，凸包之前是否有点的方案
		//g[l][r]表示考虑l->r右侧的点，并且l这个点必须在某个凸包内的方案
		//f[l][r]表示现在考虑l->r右侧的点的答案
		for(int i = 0;i < n;i ++) h[i][i][1] = 1;
		for(int l = n - 1;l >= 0;l --)
			for(int r = l + 1;r < n;r ++)
			{
				for(int get = 0;get < 2;get ++)
					for(int nl = l + 1;nl <= r;nl ++)
						if (ok[l][nl])
						{
							//l->r,r->nl,nl->l这个三角形假如有点，凸包内有点的性质就保证了
							int ng = get | bool(ap[l][r] & ap[r][nl] & ap[nl][l]);
							int cur = h[nl][r][ng];
							if (ap[l][nl])
							{
								//l->nl,nl+1->l-1这块区域内不能有点
								if (ap[l][nl] & ap[nl - 1][l + 1]) cur = 0; else
									cur = cur * 1ll * f[l + 1][nl - 1] % mo;
							}
							h[l][r][get] = (h[l][r][get] + cur) % mo;
						}
				for(int nr = l + 1;nr <= r;nr ++)
					if (ok[l][nr])
					{
						//l->r,r->nr+1,nr->l这三个向量夹着的区域内不能有点
						if (ap[l][r] & ap[r][nr + 1] & ap[nr][l]) continue;
						if (!(ap[l][r] & ap[nr][l])) 
							g[l][r] = (g[l][r] + h[l][nr][0]) % mo; else
								g[l][r] = (g[l][r] + h[l][nr][0] * 1ll * f[nr + 1][r]) % mo;
					}
				for(int nl = l;nl <= r;nl ++)
				{
					//举nl，表示标号最小的属于某个凸包的点，那么l->r->nl这个三角形内不能有点
					if (ap[l][r] & ap[r][nl]) continue;
					f[l][r] = (f[l][r] + g[nl][r]) % mo;
				}
			}
		return f[0][n - 1];
	}
};
