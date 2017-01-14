#include <bits/stdc++.h>

using namespace std;

const int maxn = 300005;
const int xy[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

typedef long long ll;

struct node
{
	 ll x,y;

	 node(void){}
	 node(ll a,ll b) : x(a),y(b){}
};

node operator -(const node &a,const node &b) {return node(a.x - b.x,a.y - b.y);}
ll operator ^(const node &a,const node &b) {return a.x * b.y - a.y * b.x;}

vector<node> a,b;

bool ok(node x,node y)
{
	for(auto p : b)
		if (((y - x) ^ (p - x)) < 0) return 0;
	return 1;
}

class EnclosingTriangle
{
public:
	long long getNumber(int m, vector <int> x, vector <int> y)
	{
		for(int i = 0;i < x.size();i ++) b.push_back(node(x[i],y[i]));
		node cur = node(0,0);
		for(int i = 0;i < 4;i ++) //push the node counterclockwisely
		{
			for(int j = 0;j < m;j ++)
				a.push_back(cur),cur.x += xy[i][0],cur.y += xy[i][1];
		}
		static ll sum[maxn];
		static int f[maxn],g[maxn]; //f[i] : max{b},every point is on (i->b)'s left,g[i]: min(b),every point is on (b->i)'s left
		for(int i = 0,f_i = 0,g_i = 0;i < a.size();i ++)
		{
			for(f_i = max(f_i,i + 1);f_i < a.size() && ok(a[i],a[f_i]);f_i ++);
			for(g_i = max(g_i,i + 1);g_i < a.size() && !ok(a[g_i],a[i]);g_i ++);
			f[i] = f_i - 1,g[i] = g_i;
			sum[i] = f[i];
			if (i) sum[i] += sum[i - 1];
		}
		ll ans = 0;
		for(int i = 0,j = 0;i < a.size();i ++)
		{
			ans = (ans + max(f[f[i]] - max(g[i],f[i] + 1) + 1,0)); //b = f[i]
			for(;j < a.size() && f[j] < g[i];j ++);//min{j}:f[j]>=g[i]
			int lp = max(j,i + 1); //b in [lp,f[i])
			if (lp < f[i]) ans += sum[f[i] - 1] - (lp ? sum[lp - 1] : 0) - (g[i] - 1) * 1ll * (f[i] - lp); //sum{f[b]-g[a]+1}
		}
		return ans;
	}
};
