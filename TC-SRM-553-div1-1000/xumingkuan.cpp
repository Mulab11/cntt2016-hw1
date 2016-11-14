#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
namespace Simplex
{
const int MAXN = 55, MAXM = 123;
const long double INF = 1e20, EPS = 1e-7;
int n, m = 0, xl[MAXM], xe[MAXN];
long double a[MAXM][MAXN], b[MAXM], c[MAXN], c2[MAXN], v = 0.0, v2 = 0.0;
int cmp(long double x)
{
	return x > EPS ? 1 : x < -EPS ? -1 : 0;
}
void pivot(int l, int e)
{
	swap(xl[l], xe[e]);
	b[l] /= a[l][e];
	for(int j = 1; j <= n; j++)
		if(j != e)
			a[l][j] /= a[l][e];
	a[l][e] = 1 / a[l][e];
	for(int i = 1; i <= m; i++)
		if(i != l && cmp(a[i][e]) != 0)
		{
			b[i] -= a[i][e] * b[l];
			for(int j = 1; j <= n; j++)
				if(j != e)
					a[i][j] -= a[i][e] * a[l][j];
			a[i][e] = -a[i][e] * a[l][e];
		}
	v += c[e] * b[l];
	for(int j = 1; j <= n; j++)
		if(j != e)
			c[j] -= a[l][j] * c[e];
	c[e] = -a[l][e] * c[e];
	v2 += c2[e] * b[l];
	for(int j = 1; j <= n; j++)
		if(j != e)
			c2[j] -= a[l][j] * c2[e];
	c2[e] = -a[l][e] * c2[e];
}
long double simplex()
{
	v = v2 = 0;
	int l, e;
	long double bmn = 1.0;
	for(int i = 1; i <= m; i++)
		if(b[i] < bmn)
			bmn = b[i], l = i;
	if(cmp(bmn) < 0)
	{
		n++;
		for(int i = 1; i <= m; i++)
			a[i][n] = -1;
		xe[n] = n;
		memcpy(c2, c, sizeof(c));
		for(int i = 1; i < n; i++)
			c[i] = 0;
		c[n] = -1;
		pivot(l, n);
		long double tmp = v, tmp2 = v2;
		tmp += simplex();
		//printf("%.20Lf\n", tmp);
		if(cmp(tmp) != 0)
			return -INF;
		for(int i = 1; i <= m; i++)
			if(xl[i] == n)
			{
				bool ok = false;
				for(int j = n; j >= 1; j--)
					if(cmp(a[i][j]) != 0)
					{
						pivot(i, j);
						ok = true;
						break;
					}
				if(!ok)
					return -INF;
				break;
			}
		for(int i = 1; i < n; i++)
			if(xe[i] == n)
			{
				for(int j = 1; j <= m; j++)
					swap(a[j][i], a[j][n]);
				swap(c[i], c[n]);
				swap(c2[i], c2[n]);
				break;
			}
		memcpy(c, c2, sizeof(c));
		v = v2 + tmp2;
		n--;
	}
	while(1)
	{
		for(e = 1; e <= n; e++)
			if(c[e] > EPS)
				break;
		if(e > n)
			return v;
		long double tmp = INF;
		for(int i = 1; i <= m; i++)
			if(a[i][e] > EPS && (b[i] / a[i][e] < tmp - EPS || (b[i] / a[i][e] < tmp + EPS && xl[i] < xl[l])))
				tmp = b[i] / a[l = i][e];
		if(tmp == INF)
			return INF;
		pivot(l, e);
	}
}
}
class YamanoteLine
{
	public:
	long long howMany(int n, vector<int> s1, vector<int> t1, vector<int> l1, vector<int> s2, vector<int> t2, vector<int> l2)
	{
		Simplex::n = n;
		Simplex::m = 0;
		memset(Simplex::a, 0, sizeof(Simplex::a));
		for(int i = 0; i < s1.size(); i++)
		{
			Simplex::m++;
			for(int j = s1[i]; j != t1[i]; j = (j + 1) % n)
				Simplex::a[Simplex::m][j + 1] = -1;
			Simplex::b[Simplex::m] = -(l1[i] - (t1[i] - s1[i] + n) % n);
		}
		for(int i = 0; i < s2.size(); i++)
		{
			Simplex::m++;
			for(int j = s2[i]; j != t2[i]; j = (j + 1) % n)
				Simplex::a[Simplex::m][j + 1] = 1;
			Simplex::b[Simplex::m] = l2[i] - (t2[i] - s2[i] + n) % n;
		}
		for(int i = 1; i <= n; i++)
			Simplex::xe[i] = i;
		for(int i = 1; i <= Simplex::m; i++)
			Simplex::xl[i] = -i;
		for(int i = 1; i <= n; i++)
			Simplex::c[i] = 1;
		const long double up = Simplex::simplex();
		if(up == Simplex::INF)//infinite
			return -1;
		if(up == -Simplex::INF)//impossible
			return 0;
		Simplex::n = n;
		Simplex::m = 0;
		memset(Simplex::a, 0, sizeof(Simplex::a));
		for(int i = 0; i < s1.size(); i++)
		{
			Simplex::m++;
			for(int j = s1[i]; j != t1[i]; j = (j + 1) % n)
				Simplex::a[Simplex::m][j + 1] = -1;
			Simplex::b[Simplex::m] = -(l1[i] - (t1[i] - s1[i] + n) % n);
		}
		for(int i = 0; i < s2.size(); i++)
		{
			Simplex::m++;
			for(int j = s2[i]; j != t2[i]; j = (j + 1) % n)
				Simplex::a[Simplex::m][j + 1] = 1;
			Simplex::b[Simplex::m] = l2[i] - (t2[i] - s2[i] + n) % n;
		}
		for(int i = 1; i <= n; i++)
			Simplex::xe[i] = i;
		for(int i = 1; i <= Simplex::m; i++)
			Simplex::xl[i] = -i;
		for(int i = 1; i <= n; i++)
			Simplex::c[i] = -1;
		const long double down = -Simplex::simplex();
		//printf("%Lf %Lf\n", up, down);
		return (long long)(up + Simplex::EPS) - (long long)(down + 1 - Simplex::EPS) + 1;
	}
};

