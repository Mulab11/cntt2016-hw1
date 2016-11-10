#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;
vector<int> e[60];
bool comp(const string& a, const string& b) {return a.size() < b.size();}

struct Set
{
	int count;
	vector<int> another;
	vector<int> next;
} set[6561], *current;

int N, M, S, A[10], B[10], p3[10];
ll point_0, point_1;
void dfs_find(int i, int s)
{
	if(i == M)
	{
		if(set[s].count != -1)
		{
			current->another.push_back(s);
		}
		return;
	}
	dfs_find(i + 1, s);
	if(point_1 & 1ll << B[i]) return;
	dfs_find(i + 1, s += p3[i]);
	if(point_1 & 1ll << A[i]) return;
	dfs_find(i + 1, s += p3[i]);
}

int f[60][6561], h[6561];

void add(int &a, int b) {(a += b) >= mod ? a -= mod : 0;}
void merge(int *f, const int *g)
{
	memset(h, 0, S << 2);
	// 枚举补集
	for(int s = 0; s != S; ++s) if(f[s])
	{
		const int *another = set[s].another.data();
		const int Another = set[s].another.size();
		const int v = f[s];
		for(int t = 0; t != Another; ++t) if(g[another[t]])
		{
			add(h[s + another[t]], (ll) v * g[another[t]] % mod);
		}
	}
	memcpy(f, h, S << 2);
}

void dfs(const int i)
{
	f[i][0] = 1;
	for(int k = 0; k != (int) e[i].size(); ++k)
	{
		const int p = e[i][k];
		dfs(p);
		merge(f[i], f[p]);
	}
	if(i != N)
	{
		int *f = ::f[i];
		memset(h, 0, S << 2);
		for(int s = 0; s != S; ++s) if(f[s])
		{
			const int *next = set[s].next.data();
			const int Next = set[s].next.size();
			const int v = f[s];
			for(int t = 0; t != Next; ++t) add(h[next[t]], v);
		}
		for(int s = 0; s != S; ++s) add(f[s], h[s]);
	}
}

class SimilarNames
{
public:
	int count(vector<string> inp, vector<int> aa, vector<int> bb)
	{
		sort(inp.begin(), inp.end(), comp);
		N = inp.size();
		for(int i = 0; i != N; ++i)
		{
			for(int j = i; j--; )
				if(inp[j] == inp[i].substr(0, inp[j].size()))
				{
					e[j].push_back(i);
					goto found;
				}
			e[N].push_back(i);
		found: continue;
		}
		// 状压每一个 pair 的情况
		// 从下往上 DP，每一个 pair 只有 3 种情况：{}, {b}, {a,b}
		// 枚举子集进行转移，只有 5 种情况 {}{}, {b}{}, {}{b}, {a,b}{}, {}{a,b}
		M = aa.size();
		p3[0] = 1;
		for(int i = 0; i != M; ++i)
		{
			A[i] = aa[i], B[i] = bb[i];
			p3[i + 1] = p3[i] * 3;
		}
		S = p3[M];
		for(int s = 0; s != S; ++s)
		{
			// 集合要求：不能自相矛盾
			// 对于同一个点，如果 A 既出现又不出现，那就不行
			static int bit[8];
			current = set + s;
			point_0 = point_1 = 0;
			for(int t = s, i = 0; i != M; ++i, t /= 3)
			{
				bit[i] = t % 3;
				if(bit[i] < 1) 	{if(point_1 & 1ll << B[i]) goto failed; else point_0 |= 1ll << B[i];}
				else 			{if(point_0 & 1ll << B[i]) goto failed; else point_1 |= 1ll << B[i];}
				if(bit[i] < 2) 	{if(point_1 & 1ll << A[i]) goto failed; else point_0 |= 1ll << A[i];}
				else 			{if(point_0 & 1ll << A[i]) goto failed; else point_1 |= 1ll << A[i];}
			}
			current->count = __builtin_popcountll(point_1);
			continue;
		failed: current->count = -1;
		}
		if(set[S - 1].count == -1) return 0;
		// 此时 point_1 为所有关键点的集合
		const ll key_point = point_1;
		for(int s = 0; s != S; ++s) if(set[s].count != -1)
		{
			static int bit[8];
			current = set + s;
			point_1 = 0;
			for(int t = s, i = 0; i != M; ++i, t /= 3)
			{
				bit[i] = t % 3;
				if(bit[i] >= 1) point_1 |= 1ll << B[i];
				if(bit[i] >= 2) point_1 |= 1ll << A[i];
			}
			// 现在集合是合法的了！枚举补集！
			// 要求：补集里面一定不能有 point_1 里面的点
			dfs_find(0, 0);
			// 求下一个集合
			// 枚举新加入的关键点
			for(ll S = key_point - point_1; S; )
			{
				int k = __builtin_ctzll(S); S -= 1ll << k;
				int t = s;
				for(int i = 0; i != M; ++i)
					if((bit[i] == 0 && B[i] == k) || (bit[i] == 1 && A[i] == k))
						t += p3[i];
				if(s == t || set[t].count == -1) continue;
				set[s].next.push_back(t);
			}
		}
		dfs(N);
		int ret = f[N][S - 1];
		for(int i = 1; i <= N - __builtin_popcountll(key_point); ++i)
			ret = (ll) ret * i % mod;
		return ret;
	}
}	user;
