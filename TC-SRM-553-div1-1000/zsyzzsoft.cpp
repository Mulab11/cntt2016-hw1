#include <algorithm>
using namespace std;
const long long inf = 1000000000000000LL;
struct Pair
{
	long long a;
	int b;
	Pair() {a = b = 0; }
	Pair(long long _a) {a = _a, b = 0; }
	Pair(long long _a, int _b) {a = _a, b = _b; }
	Pair operator - (const Pair &_p) const
	{
		return Pair(a - _p.a, b - _p.b);
	}
	Pair operator + (const Pair &_p) const
	{
		return Pair(a + _p.a, b + _p.b);
	}
	bool operator < (const Pair &_p) const
	{
		return a < _p.a;
	}
};
struct Edge
{
	int u, v;
	Pair w;
	Edge() {u = v = 0; }
	Edge(int _u, int _v, long long _w, int _t = 0) {u = _u, v = _v, w = Pair(_w, _t); }
};
class YamanoteLine
{
public:
	int n;
	Pair d[51];
	bool positive, negative;
	vector<Edge> edge;
	void Work(long long x)
	{
		positive = negative = false;
		d[0] = Pair(0);
		for(int i = 1; i < n; i++)
			d[i] = Pair(inf);
		for(int i = n - 1; i >= 0; i--) //求负环 
		{
			for(int j = 0; j < edge.size(); j++)
			{
				int u = edge[j].u, v = edge[j].v;
				Pair w(edge[j].w.a + x * edge[j].w.b, edge[j].w.b);
				if(d[u] + w < d[v])
				{
					if(!i)
					{
						Pair cycle = d[u] + w - d[v];
						if(cycle.b > 0)
							positive = true;
						if(cycle.b < 0)
							negative = true;
					}
					d[v] = d[u] + w;
				}
			}
		}
	}
	long long Upper() //上边界 
	{
		long long l = 0, r = inf * 2;
		while(l < r)
		{
			long long mid = (l + r + 1) / 2;
			Work(mid);
			if(negative)
				r = mid - 1;
			else
				l = mid;
		}
		return l;
	}
	long long Lower() //下边界 
	{
		long long l = 0, r = inf * 2;
		while(l < r)
		{
			long long mid = (l + r) / 2;
			Work(mid);
			if(positive)
				l = mid + 1;
			else
				r = mid;
		}
		return l;
	}
	long long howMany(int _n, vector<int> s1, vector<int> t1, vector<int> l1, vector<int> s2, vector<int> t2, vector<int> l2)
	{
		n = _n;
		for(int i = 0; i < n; i++) //建图 
			s1.push_back(i), t1.push_back((i + 1) % n), l1.push_back(1);
		for(int i = 0; i < s1.size(); i++)
		{
			int s = s1[i], t = t1[i], l = l1[i];
			if(s < t)
				edge.push_back(Edge(t, s, -l));
			else
				edge.push_back(Edge(t, s, -l, 1));
		}
		for(int i = 0; i < s2.size(); i++)
		{
			int s = s2[i], t = t2[i], l = l2[i];
			if(s < t)
				edge.push_back(Edge(s, t, l));
			else
				edge.push_back(Edge(s, t, l, -1));
		}
		long long ans = max(Upper() - Lower() + 1, 0LL);
		return ans >= inf ? -1 : ans;
	}
};
