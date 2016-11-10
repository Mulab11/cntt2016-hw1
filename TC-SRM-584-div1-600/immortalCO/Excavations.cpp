#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

#include <set>
pair<int, int> arr[55];
int cnt[55], cnt2[55], M;
ll f[2][2][55], comb[55][55];

void add_item(ll *f, const ll *g, int c)
{
	if(!c) return;
	static ll h[55];
	memcpy(h, g, (M + 1) << 3);
	while(c--) for(int i = M; i; --i) h[i] += h[i - 1];
	for(int i = 0; i <= M; ++i) f[i] += h[i] - g[i];
}
void add_free(ll *f, int c)
{
	if(!c) return;
	while(c--) for(int i = M; i; --i) f[i] += f[i - 1];
}

class Excavations
{
public:
	ll count(vector<int> k1, vector<int> k2, vector<int> k3, int M)
	{
		const int N = k1.size();
		const int K = k3.size();
		::M = M;
		for(int i = 0; i != N; ++i) arr[i] = make_pair(k2[i], k1[i]);
		sort(arr, arr + N);
		comb[0][0] = 1;
		for(int i = 1; i <= N; ++i)
		{
			comb[i][0] = comb[i][i] = 1;
			for(int j = 1; j != i; ++j)
				comb[i][j] = comb[i - 1][j] + comb[i - 1][j - 1];
		}
		ll ans = 0;
		for(int p = 0; p != N; ++p)
		{
			const int q = p;
			while(p + 1 != N && arr[p].first == arr[p + 1].first) ++p;
			for(int i = q; i <= p; ++i) ++cnt2[arr[i].second];
			// 统计答案，要求：至少有一个种类，出现在当前区间（cnt2）
			// f[i][2][j]：做到第 i 个，和为 j，并且是否已经出现种类为 k
			bool d = 0;
			memset(f[d], 0, sizeof f[d]);
			f[d][0][0] = 1;
			for(int i = 0; i != K; ++i)
			{
				d ^= 1;
				memset(f[d], 0, sizeof f[d]);
				const int c = k3[i];
				// 几种转移
				add_item(f[d][1], f[!d][0], cnt2[c]);
				add_item(f[d][1], f[!d][1], cnt[c] + cnt2[c]);
				add_item(f[d][0], f[!d][0], cnt[c]);
				add_free(f[d][0], cnt2[c]);
			}
			for(int i = 0; i <= M; ++i) ans += f[d][1][i] * comb[N - p - 1][M - i];
			for(int i = q; i <= p; ++i) ++cnt[arr[i].second], --cnt2[arr[i].second];
		}
		return ans;
	}
}	user;
