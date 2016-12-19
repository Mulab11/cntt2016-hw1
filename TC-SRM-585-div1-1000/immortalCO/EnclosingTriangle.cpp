#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Point
{
	int x, y;
	Point operator - (const Point& p) const
	{
		return (Point) {x - p.x, y - p.y};
	}
	ll operator * (const Point& p) const
	{
		return (ll) x * p.y - (ll) y * p.x;
	}
} p[250010], q[25];

int P, Q, pre[250010];

bool pig_r(Point p, Point q)
{
	Point v = q - p;
	for(int i = 0; i != Q; ++i)
		if(v * (::q[i] - p) < 0) return 0;
	return 1;
}
int solve_r(Point p, int l, int r)
{
	while(l != r)
	{
		int m = (l + r + 1) >> 1;
		pig_r(p, ::p[m]) ? l = m : r = m - 1;
	}
	return pig_r(p, ::p[l]) ? l : -1000000000;
}
bool pig_l(Point p, Point q)
{
	Point v = q - p;
	for(int i = 0; i != Q; ++i)
		if(v * (::q[i] - p) > 0) return 0;
	return 1;
}
int solve_l(Point p, int l, int r)
{
	while(l != r)
	{
		int m = (l + r + 0) >> 1;
		pig_l(p, ::p[m]) ? r = m : l = m + 1;
	}
	return pig_l(p, ::p[l]) ? l : 1000000000;
}

class EnclosingTriangle
{
public:
	ll getNumber(int M, vector<int> qx, vector<int> qy)
	{
		Q = qx.size();
		for(int i = 0; i != Q; ++i) q[i] = (Point) {qx[i], qy[i]};
		for(int i = 0; i != M; ++i) p[++P] = (Point) {i, 0};
		for(int i = 0; i != M; ++i) p[++P] = (Point) {M, i};
		for(int i = M; i != 0; --i) p[++P] = (Point) {i, M};
		for(int i = M; i != 0; --i) p[++P] = (Point) {0, i};
		ll ans = 0, cur = 0;
		// 枚举三角形按逆时针的第一个点
		for(int i = 2; i <= P; ++i) pre[i] = solve_l(p[i], 1, i - 1);
		for(int a = 1, l = 0, r = 0, lb = 1, lt = 1; a <= P; ++a)
		{
			// 找出三角形第二个点可行的范围
			const int b = solve_r(p[a], max(lb, a + 1), P); lb = b;
			const int t = solve_l(p[a], max(lt, a + 1), P); lt = t;
			if(t > P) break;
			if(!l) l = r = b;
			for(; r <= P && pre[r] <= b; ++r)
				cur += pre[r] - 1;
			for(; l < t && l < r; ++l)
				cur -= pre[l] - 1;
			ans += (ll) (r - l) * b - cur;
			// 扣除退化的两个三角形
			if(l == b) ans -= 2;
		}
		return ans;
	}
}	user;
