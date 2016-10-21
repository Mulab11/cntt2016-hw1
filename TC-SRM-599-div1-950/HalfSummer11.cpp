#line 2 "SimilarNames.cpp"
#include<vector>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<iostream>
#include<sstream>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define maxm 6600
#define maxs 65540
#define mo 1000000007
#define hash hashh
typedef long long ll;
using namespace std;
int n, m, tot, hash[maxn]; // n为names的大小，m为info的大小，tot为info1与info2涉及到的字符串个数, hash[i]表示原编号为i的字符串对应的新编号
int a[maxn], b[maxn]; // 存放m对限制：字符串a[i]是字符串b[i]的前缀
bool isv[1 << 16]; // isv[sta]表示sta是否是合法的状态
int cnt, valid[maxm]; // cnt为合法的状态个数，valid存放所有合法的状态
vector<int> valids[maxm]; // valids[i]存第i个合法状态S的合法子集A，满足S,A,S - A均合法
int tcnt, ch[maxn * maxn][26], id[maxn * maxn]; // ch存Trie，id[i]表示Trie上第i个节点是第id[i]个字符串的结尾
int g[maxn], ei;
struct edge {
	int t, nxt;
}e[maxn * 2];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
} // 存前缀树
void dfs(int x, int pre) { // 遍历Trie，建前缀树
	if (id[x]) {
		if (pre) ae(pre, id[x]);
		pre = id[x];
	}
	for (int i = 0; i < 26; ++i)
		if (ch[x][i]) 
			dfs(ch[x][i], pre);
}
int f[maxn][maxs]; // f[i][sta] 表示在以i为根的子树中安排sta这些字符串的方案数
int F[2][maxs], O; // 临时数组，保存以x为根的子树中，考虑前若干个儿子，在它们中安排sta这些字符串的方案数
#define now F[O]
#define last F[O ^ 1]
void add(int &a, int b) {
	a += b; a %= mo;
}
void dp(int x)
{
	for (int i = g[x]; i; i = e[i].nxt) 
		dp(e[i].t);
	cl(F); O = 0;
	now[0] = 1;
	for (int i = g[x]; i; i = e[i].nxt) {
		O ^= 1; cl(now);
		for (int j = 1; j <= cnt; ++j) 
			for (int k = 0; k < valids[j].size(); ++k) 
				add(now[valid[j]], 1ll * last[valids[j][k]] * f[e[i].t][valid[j] - valids[j][k]] % mo);
	}
	for (int j = 1; j <= cnt; ++j) {
		int s = valid[j];
		add(f[x][s], now[s]); // x节点代表的字符串不放在sta中
		if (x == n + 1) continue;
		for (int u = s; u; u -= (u & (-u))) // x节点代表的字符串放在sta中
			add(f[x][s], now[s - (u & (-u))]);
	}
}
class SimilarNames
{
	public:
		int count(vector <string> names, vector <int> info1, vector <int> info2) {
			n = names.size(); 
			// 建Trie
			tcnt = 1; cl(ch); cl(id); id[1] = n + 1;
			for (int i = 0; i < n; ++i){
				int x = 1;
				for (int j = 0; j < names[i].length(); ++j) {
					int c = names[i][j] - 'a';
					if (! ch[x][c]) 
						ch[x][c] = ++tcnt;
					x = ch[x][c];
				}
				id[x] = i + 1;
			}
			cl(g); ei = 0;
			dfs(1, 0); // 建前缀树
			// 离散化info涉及到的字符串
			m = info1.size();
			int tmp[maxn]; tot = 0; // 用于离散化的临时数组
			for (int i = 0; i < m; ++i)
				tmp[++tot] = info1[i], tmp[++tot] = info2[i];
			sort(tmp + 1, tmp + tot + 1);
			tot = unique(tmp + 1, tmp + tot + 1) - tmp - 1;
			cl(hash); 
			for (int i = 1; i <= tot; ++i)
				hash[tmp[i]] = i - 1;
			for (int i = 0; i < m; ++i) 
				a[i] = hash[info1[i]], b[i] = hash[info2[i]]; 
			//预处理所有合法的sta : 对任意一对(a[i], b[i]),不能出现仅有a[i]在sta中的情况
			cl(isv); cnt = 0;
			for (int s = 0; s < (1 << tot); ++s) {
				bool flag = 1;
				for (int i = 0; i < m; ++i)
					if ((s & (1 << a[i])) && !(s & (1 << b[i]))) {
						flag = 0; break;
					}
				if (flag) 
					valid[++cnt] = s, isv[s] = 1;
			}
			//预处理所有合法的sta的合法子集A，满足sta - A同样为合法的状态
			for (int i = 1; i <= cnt; ++i) valids[i].clear();
			for (int i = 1; i <= cnt; ++i) {
				int S = valid[i];
				for (int A = S; ; A = (A - 1) & S) {
					if (isv[A] && isv[S - A]) valids[i].pb(A);
					if (! A) break;
				}
			}
			cl(f);
			dp(n + 1);
			int ans = f[n + 1][(1 << tot) - 1];
			for (int i = 1; i <= n - tot; ++i)
				ans = 1ll * ans * i % mo;
			return ans;
		}
};
