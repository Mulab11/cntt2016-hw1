#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

struct Range{int l, r;} ran[60];
int val[110];

class EelAndRabbit
{
public:
	int getmax(vector<int> len, vector<int> beg)
	{
		const int N = len.size();
		// 找两个点，使得其和区间相交的个数最短
		// 离散化端点之后暴力
		int V = 0;
		for(int i = 0; i != N; ++i)
		{
			val[V++] = ran[i].l = beg[i];
			val[V++] = ran[i].r = beg[i] + len[i];
		}
		sort(val, val + V);
		V = unique(val, val + V) - val;
		int ans = 0;
		for(int a = 0; a != V; ++a)
			for(int b = a + 1; b != V; ++b)
			{
				int cur = 0;
				for(int i = 0; i != N; ++i)
					if((ran[i].l <= val[a] && val[a] <= ran[i].r)
					   || (ran[i].l <= val[b] && val[b] <= ran[i].r))
						++cur;
				ans = max(ans, cur);
			}
		return ans;
	}
}	user;
