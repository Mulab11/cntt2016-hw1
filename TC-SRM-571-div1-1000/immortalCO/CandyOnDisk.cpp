#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#define diff(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
const ld eps = 1e-8;

struct Circle
{
	ld x, y, r, d;
	ld min, max;
	bool operator < (const Circle& C) const {return r > C.r;}
	// 打表发现：每个圆的范围是一个区间
	// 保存这个区间，进行迭代
} cir[60];

ld f[60][60], g[60][60];

bool cmax(ld &a, const ld& b) {return a < b ? a = b, 1 : 0;}
bool cmin(ld &a, const ld& b) {return a > b ? a = b, 1 : 0;}

class CandyOnDisk
{
public:
	string ableToAchieve(vector<int> px, vector<int> py, vector<int> pr, int sx, int sy, int tx, int ty)
	{
		int N = px.size() + 2;
		for(int i = 2; i != N; ++i)
		{
			ld x = cir[i].x = px[i - 2];
			ld y = cir[i].y = py[i - 2];
			ld r = cir[i].r = pr[i - 2];
			cir[i].d = max(ld(0), sqrtl((x - sx) * (x - sx) + (y - sy) * (y - sy)) - r);
		}
		sort(cir + 2, cir + N);
		int M = N; N = 2;
		for(int i = 2; i != M; ++i)
		{
			for(int j = 2; j != i; ++j)
				if(diff(cir[i].x, cir[j].x) < eps && diff(cir[i].y, cir[j].y) < eps)
					goto removed;
			cir[N++] = cir[i];
		removed: ;
		}
		cir[1].x = sx;
		cir[1].y = sy;
		cir[1].r = cir[N].r = powl(10.0, -10.0);
		cir[N].x = tx;
		cir[N].y = ty;
		// 为了方便，按照到 1 的距离排序
		const ld inf = 1e100;
		cir[1].min = 0;
		cir[1].max = cir[1].r;
		cir[N].min = inf;
		cir[N].max = -inf;
		// 初始化区间
		for(int i = 2; i != N; ++i)
		{
			cir[i].min = inf,
			cir[i].max = -inf;
		}
		// 两个圆相交部分的最远部分和最近部分
		for(int i = 1; i <= N; ++i)
			for(int j = 1; j <= N; ++j) if(i != j)
			{
				ld dist = sqrtl((cir[i].x - cir[j].x) * (cir[i].x - cir[j].x) + (cir[i].y - cir[j].y) * (cir[i].y - cir[j].y));
				ld l = max(ld(0), dist - cir[j].r);
				ld r = min(cir[i].r, dist + cir[j].r);
				if(l < r + eps)
				{
					f[i][j] = l, g[i][j] = r;
				}
				else f[i][j] = inf, g[i][j] = -inf;
			}
		bool mod = 0;
		do
		{
			mod = 0;
			// 如果暴力迭代会超时
			// 考虑两个圆如果不断迭代会变成什么
			// 只要有相交，那么一定会慢慢填满整个相交的部分
			for(int i = 1; i <= N; ++i)
				if(cir[i].min <= cir[i].max)
					for(int j = 1; j <= N; ++j) if(i != j)
					{
						// 暴力迭代可能要很久
						// 我们先判断两个圆当前的环的范围是否有相交
						// 如果有，则必然能扩展为最大势力范围
						if(f[i][j] > g[i][j]) continue;
						if(max(cir[i].min, f[i][j]) > min(cir[i].max, g[i][j])) continue;
						mod |= cmin(cir[i].min, f[i][j]);
						mod |= cmin(cir[j].min, f[j][i]);
						mod |= cmax(cir[i].max, g[i][j]);
						mod |= cmax(cir[j].max, g[j][i]);
					}
			if(cir[N].min < cir[N].max + eps) return "YES";
		}
		while(mod);
		return "NO";
	}
}	user;
