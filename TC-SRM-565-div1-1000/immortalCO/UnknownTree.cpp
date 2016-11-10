#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 9;
const int MaxN = 110;
#define ddel(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
int n;

struct Edge
{
	int x, y, v;
	bool operator < (const Edge& T) const
	{
		if(x != T.x) return x < T.x;
		if(y != T.y) return y < T.y;
		if(v != T.v) return v < T.v;
		return 0;
	}
	bool operator == (const Edge& e) const
	{
		return x == e.x && y == e.y && v == e.v;
	}
};


// 判断两个关键点是否直接相连
// 返回中间的边的长度
int pig_directly_linked(const vector<int> &A, const vector<int> &B)
{
	// 每条边要么在这条边的左边，要么在右边
	// 那么任意一个点到两个点的距离之差的绝对值
	const int ret = ddel(A[0], B[0]); if(!ret) return 0; // 边权为正
	for(int i = 0; i != n; ++i) if(ddel(A[i], B[i]) != ret) return 0;
	return ret;
}
struct Triple
{
	int a, b, c;
	bool operator < (const Triple& T) const
	{
		if(a != T.a) return a < T.a;
		if(b != T.b) return b < T.b;
		if(c != T.c) return c < T.c;
		return 0;
	}
	bool father(const Triple& T) const
	{
		// 你能做父亲，当且仅当：
		// 1. 三维坐标都小于自己
		// 2. 三维坐标差相等
		if(a <= T.a || b <= T.b || c <= T.c) return 0;
		return (a - T.a) == (b - T.b) && (b - T.b) == (c - T.c);
	}
};
// 初始化函数，比 vector.clear 快
template<class T>void reinit(T &t) {t.~T(); new (&t)T;}
// 求距离的 DFS
vector< pair<int, int> > e[MaxN];
bool vd[MaxN], fail;
void dfs(int i, int f, int *D)
{
	vd[i] = 1;
	for(int k = 0; k != (int) e[i].size(); ++k)
		if(e[i][k].first != f)
		{
			if(vd[e[i][k].first]) {fail = 1; return;}
			D[e[i][k].first] = D[i] + e[i][k].second;
			dfs(e[i][k].first, i, D);
		}
}
// 解函数，先给定一个边集合，然后数数
int solve(vector<int> A, vector<int> B, vector<int> C, vector<Edge> E)
{
	for(int i = 0; i != (int) E.size(); ++i) if(!E[i].v) return 0;
	for(int i = 0; i != (int) E.size(); ++i)
		if(E[i].x > E[i].y) swap(E[i].x, E[i].y);
	sort(&*E.begin(), &*E.end());
	E.erase(unique(E.begin(), E.end()), E.end());
	// 这个函数能正确工作当且仅当在边集 E 中 A、B、C 三个点连通
	static bool vis[MaxN];
	static int AA[MaxN], BB[MaxN], CC[MaxN];
	memset(vis, 0, n);
	for(int i = 0; i != n + 3; ++i) reinit(e[i]);
	for(int i = 0; i != (int) E.size(); ++i)
	{
		vis[E[i].x] = vis[E[i].y] = 1;
		e[E[i].x].push_back(make_pair(E[i].y, E[i].v));
		e[E[i].y].push_back(make_pair(E[i].x, E[i].v));
	}
	// 求出两两之间距离
	AA[n + 0] = AA[n + 1] = AA[n + 2] = 0;
	fail = 0;
	memset(vd, 0, n + 3); dfs(n + 0, -1, AA);
	memset(vd, 0, n + 3); dfs(n + 1, -1, BB);
	memset(vd, 0, n + 3); dfs(n + 2, -1, CC);
	if(fail) return 0;
	static Triple data[MaxN];
	int l = 0;
	for(int i = 0; i != n; ++i) if(vis[i])
	{
		if(A[i] != AA[i] || B[i] != BB[i] || C[i] != CC[i]) return 0;
		data[l++] = (Triple) {AA[i], BB[i], CC[i]};
	}
	data[l++] = (Triple) {AA[n + 0], BB[n + 0], CC[n + 0]};
	data[l++] = (Triple) {AA[n + 1], BB[n + 1], CC[n + 1]};
	data[l++] = (Triple) {AA[n + 2], BB[n + 2], CC[n + 2]};
	int r = l;
	for(int i = 0; i != n; ++i) if(!vis[i])
		data[r++] = (Triple) {A[i], B[i], C[i]};
	sort(data + l, data + r);
	int ans = 1;
	// 每个点选择父亲是独立且不成环的，所以利用乘法原理，把每个点的可行父亲乘起来
	for(int i = l; i != r && ans; ++i)
	{
		int choice = 0;
		for(int j = 0; j != i; ++j)
			if(data[i].father(data[j])) ++choice;
		ans = (ll) ans * choice % mod;
	}
	return ans;
}
// 找直接连接这两个点的链，不合法返回空 vector
vector< pair<int, int> > get_chain(vector<int> A, vector<int> C)
{
	int len = 1e9;
	for(int i = 0; i != n; ++i) len = min(len, A[i] + C[i]);
	if(len >= 1e9) return vector< pair<int, int> >();
	vector< pair<int, int> > ret;
	for(int i = 0; i != n; ++i) if(A[i] + C[i] == len)
		ret.push_back(make_pair(A[i], i));
	sort(&*ret.begin(), &*ret.end());
	// 链上不能有距离相等的点
	for(int i = 1; i != (int) ret.size(); ++i)
		if(ret[i].first == ret[i - 1].first)
			return vector< pair<int, int> >();
	return ret;
}
// 把 AC 的边插到 E 里面去
void link_chain(vector<Edge>& E, const vector<int>& A, const vector<int>& C, int pA, int pC, const vector< pair<int, int> >& AC)
{
	E.push_back((Edge) {pA, AC.front().second, A[AC.front().second]});
	for(int i = 1; i != (int) AC.size(); ++i)
		E.push_back((Edge) {AC[i - 1].second, AC[i].second, AC[i].first - AC[i - 1].first});
	E.push_back((Edge) {AC.back().second, pC, C[AC.back().second]});
}
// 处理两个连在一起的函数
int working2(vector<int> A, vector<int> B, vector<int> C)
{
	// A 和 B 连在一起，且 C 在 A 的子树里面
	// 枚举什么点在 AC 这条链上面
	vector< pair<int, int> > AC(get_chain(A, C));
	if(AC.empty()) return 0;
	// 解！
	vector<Edge> E;
	E.push_back((Edge) {n + 0, n + 1, pig_directly_linked(A, B)});
	link_chain(E, A, C, n + 0, n + 2, AC);
	return solve(A, B, C, E);
}
int work1(vector<int> A, vector<int> B, vector<int> C)
{
	// 是 A->C->B 这种情况
	vector< pair<int, int> > AC = get_chain(A, C);
	vector< pair<int, int> > CB = get_chain(C, B);
	vector<Edge> E;
#define pbe(a, b, c) push_back((Edge) {a, b, c})
	E.pbe(n + 0, AC.front().second, A[AC.front().second]);
	for(int i = 1; i != (int) AC.size(); ++i) E.pbe(AC[i - 1].second, AC[i].second, AC[i].first - AC[i - 1].first);
	E.pbe(AC.back().second, n + 2, C[AC.back().second]);
	E.pbe(n + 2, CB.front().second, C[CB.front().second]);
	for(int i = 1; i != (int) CB.size(); ++i) E.pbe(CB[i - 1].second, CB[i].second, CB[i].first - CB[i - 1].first);
	E.pbe(CB.back().second, n + 1, B[CB.back().second]);
	return solve(A, B, C, E);
}
int work2(vector<int> A, vector<int> B, vector<int> C)
{
	// A 和 B 连在一起了
	// 枚举 C 在谁的子树里面
	int ans = 0;
	ans += working2(A, B, C);
	ans += working2(B, A, C);
	return ans % mod;
}
int work3(vector<int> A, vector<int> B, vector<int> C)
{
	// 三个连在一起，顺序是 A->B->C
	vector<Edge> E;
	E.push_back((Edge) {n + 0, n + 1, pig_directly_linked(A, B)});
	E.push_back((Edge) {n + 1, n + 2, pig_directly_linked(B, C)});
	return solve(A, B, C, E);
}

class UnknownTree
{
public:
	int getCount(vector<int> A, vector<int> B, vector<int> C)
	{
		n = A.size();
		int AB = pig_directly_linked(A, B);
		int BC = pig_directly_linked(B, C);
		int AC = pig_directly_linked(A, C);
		int Total = bool(AB) + bool(BC) + bool(AC);
		int pA = n + 0, pB = n + 1, pC = n + 2;
		int ans = 0;
		// 首先处理有直接连边的
		switch(Total)
		{
			case 3:
			case 2:
				// 1. 三个连在一起的
				(ans += work3(A, B, C)) %= mod;
				(ans += work3(A, C, B)) %= mod;
				(ans += work3(B, A, C)) %= mod;
			case 1:
				// 2. 只有两个连在一起的
				// （似乎上面的特判就没用了？）
				if(AB) (ans += work2(A, B, C)) %= mod;
				if(BC) (ans += work2(B, C, A)) %= mod;
				if(AC) (ans += work2(A, C, B)) %= mod;
			case 0:
				// 3. 没有连在一起的
				// 我们找出这三条链，求一个交集
				vector<pair<int, int> > chainAB(get_chain(A, B)); if(chainAB.empty()) goto done;
				vector<pair<int, int> > chainBC(get_chain(B, C)); if(chainBC.empty()) goto done;
				vector<pair<int, int> > chainAC(get_chain(A, C)); if(chainAC.empty()) goto done;
				// 现在要求满足对称差，即 A ^ B ^ C = {}
				static bool vis[MaxN];
				static int len[MaxN][MaxN];
				int cnt = 0;
				for(int i = 0; i != (int) chainAB.size(); ++i) vis[chainAB[i].second] ^= 1;
				for(int i = 0; i != (int) chainBC.size(); ++i) vis[chainBC[i].second] ^= 1;
				for(int i = 0; i != (int) chainAC.size(); ++i) vis[chainAC[i].second] ^= 1;
				for(int i = 0; i != n; ++i) if(vis[i]) ++cnt;
				// 只有中心点被访问了 3 次（但有可能中心点是 ABC 中的一个）
				if(cnt > 1) goto done;
				if(!cnt) // 中心点是其中一个
				{
					if(chainAB.size() == chainAC.size() + chainBC.size()) (ans += work1(A, B, C)) %= mod;
					if(chainBC.size() == chainAB.size() + chainAC.size()) (ans += work1(B, C, A)) %= mod;
					if(chainAC.size() == chainBC.size() + chainAB.size()) (ans += work1(A, C, B)) %= mod;
				}
				else
				{
					vector<Edge> E;
					link_chain(E, A, B, pA, pB, chainAB);
					link_chain(E, A, C, pA, pC, chainAC);
					link_chain(E, B, C, pB, pC, chainBC);
					for(int i = 0; i != (int) E.size(); ++i)
					{
						if(!len[E[i].x][E[i].y]) len[E[i].x][E[i].y] = len[E[i].y][E[i].x] = E[i].v;
						else if(E[i].v != len[E[i].x][E[i].y]) goto done;
					}
					(ans += solve(A, B, C, E)) %= mod;
				}
				// 现在就可以做啦
		}
	done:
		return ans;
	}
}	user;
