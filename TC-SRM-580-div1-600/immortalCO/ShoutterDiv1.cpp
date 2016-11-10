#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Range
{
	int l, r;
	bool operator < (const Range& ran) const
	{
		return l < ran.l || (l == ran.l && r > ran.r);
	}
} ran[3000];

class ShoutterDiv1
{
	typedef vector<string> vs;
public:
	int count(vs a,vs b,vs c,vs d,vs e,vs f,vs g,vs h)
	{
		string A, B, C, D, E, F, G, H;
		for(int i = 0; i != (int) a.size(); ++i)
		{
			A += a[i], B += b[i], C += c[i], D += d[i];
			E += e[i], F += f[i], G += g[i], H += h[i];
		}
		const int N = A.size();
		int M = 10000;
		for(int i = 0; i != N; ++i)
		{
			ran[i].l = (A[i]-'0')*1000 + (B[i]-'0')*100 + (C[i]-'0')*10 + (D[i]-'0');
			ran[i].r = (E[i]-'0')*1000 + (F[i]-'0')*100 + (G[i]-'0')*10 + (H[i]-'0');
			if(M > ran[i].r) M = ran[i].r;
		}
		sort(ran, ran + N);
		int ans = 0;
		for(int i = 0; i != N; ++i)
		{
			// 每一个的影响是一个区间，一个转发可以把区间扩展出去
			// 以每个人为内容的转发是独立的，每一个跑贪心，答案分别相加
			int j = 0, k = M;
			for(; ;)
			{
				// 免费用自己
				// 前半段是别人给他的，后半段是他给别人的
				if(ran[i].l <= k) k = max(k, ran[i].r);
				int p = -1;
				for(; j != N && ran[j].l <= k; ++j)
					p = max(p, ran[j].r);
				if(j == N) break;
				if(p <= k) return -1;
				++ans;
				k = p;
			}
		}
		return ans;
	}
}	user;
