#line 2 "CirclesGame.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define eps 1e-9
typedef long long ll;
using namespace std;
int rts[maxn], rcnt; // 存森林里每棵树的根
int n, pre[maxn], g[maxn], ei; // n是点(题中的圆)的个数，pre是树上的父亲，g,ei是边表部分
int f[maxn]; // f[i]是以i为根的子树的sg函数值
struct edge {
	int t, nxt;
}e[maxn];
void ae(int a, int b) {
	e[++ei].t = b; e[ei].nxt = g[a]; g[a] = ei;
}
int sta[maxn], top, tmp[maxn], tot; // sta,top是dfs栈，tmp,tot用于存放一个状态所有后继状态的sg值
void collect(int x) { // 于以rt为根的子树里，尝试删去点x，计算这种情况下的后继状态sg值
	sta[++top] = x; // 把x放入dfs栈中
	tmp[++tot] = 0; // 后继状态sg值 = 去掉x到rt上的点，剩下的子树的sg值的异或和，初始为0
	for (int i = 1; i <= top; ++i) {
		int y = sta[i]; // 枚举x到rt路径上的每个点
		for (int j = g[y]; j; j = e[j].nxt) // 枚举每个点的儿子
			if (i == top || e[j].t != sta[i + 1]) // 若这个儿子是去掉x-rt后，剩下的某棵树的根，将它的sg值异或进答案
				tmp[tot] ^= f[e[j].t];
	}
	for (int i = g[x]; i; i = e[i].nxt)
		collect(e[i].t); // 递归下去，枚举删掉其它点的情况
	--top; // 退栈
}
void dfs(int x) { // 计算以x为根的子树中所有点的sg值
	for (int i = g[x]; i; i = e[i].nxt) dfs(e[i].t); 
	top = tot = 0;
	collect(x); // 计算f[x],先枚举子树中删去的点，找出后继状态
	sort(tmp + 1, tmp + tot + 1); // 以下均为找mex的过程
	if (tmp[1] > 0) { 
		f[x] = 0; return;
	} else {
		for (int i = 1; i < tot; ++i)
			if (tmp[i + 1] > tmp[i] + 1) { //!!! >
				f[x] = tmp[i] + 1; return;
			}
		f[x] = tmp[tot] + 1; 
	}
}
class CirclesGame {
	public:
		string whoCanWin(vector <int> x, vector <int> y, vector <int> r) {
			n = x.size(); 
			for (int i = 0; i < n; ++i) {
				pre[i + 1] = -1;
				for (int j = 0; j < n; ++j) {
					if (i == j) continue;
					if (sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) + 1.0 * r[i] < 1.0 * r[j] + eps) {
						if (pre[i + 1] == -1 || r[pre[i + 1] - 1] > r[j]) // 找到包含第i个圆的最小的圆j，作为它在树上的父亲
							pre[i + 1] = j + 1;
					}
				}
			}
			rcnt = 0; cl(g); ei = 0;
			for (int i = 1; i <= n; ++i)
				if (pre[i] == -1) 
					rts[++rcnt] = i; // 是森林中的一个树根
				else
					ae(pre[i], i); // 连树边
			int ans = 0;
			for (int i = 1; i <= rcnt; ++i) {
				dfs(rts[i]);
				ans ^= f[rts[i]]; // 将每棵树的sg值异或起来，得到整个局面的sg函数
			}
			return ans ? "Alice" : "Bob";
		}
};
