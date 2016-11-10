#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, -1, 0, 1};

typedef pair<LL, LL> point;

inline point operator + (const point & a, const point & b)		//位移向量相加
{
	return point(a.x + b.x, a.y + b.y);
}

inline point rotate(point x, int d)			//顺时针旋转移动向量 90*d 度
{
	if (!d)
		return x;
	return rotate(point(x.y, -x.x), d - 1);	
}

class RobotHerb
{
public:
	//模拟，找规律
	LL getdist(int T, vector<int> a)
	{
		point ans(0, 0);
		point p(0, 0), q(0, 0);
		int dir = 0;

		rep (i, 0, a.size() - 1)		//模拟一次命令序列的执行
		{
			q.x += a[i] * dx[dir];
			q.y += a[i] * dy[dir];
			dir = (dir + a[i]) % 4;
		}

		int cnt = T / 4;		//把 T 次命令分为 (T/4)*4 次和零散部分
		T %= 4;

		rep (i, 0, 3)		//算出每 4 次命令执行产生的位移
		{
			p = p + q;
			q = rotate(q, dir);
		}

		ans = point(p.x * cnt, p.y * cnt);		// 计算 (T/4)*4 次执行产生的位移

		rep (i, 1, T)			//计算零散部分  
		{
			ans = ans + q;
			q = rotate(q, dir);
		}

		return abs(ans.x) + abs(ans.y);
	}
};

