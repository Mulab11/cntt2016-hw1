#line 2 "CirclesGame.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;
const int INF = 1e9;

int n;
vector<int> ch[N + 9];// 树的孩子

#define sqr(x) ((x) * (x))

int sg[N + 9];// 每棵子树的sg值
int fa[N + 9];// 每个点的父亲

vector<int> sub;// 子树中的所有点
vector<int> mex;// 所有后继状态的sg值

void dfssub(int x) {// 搜出子树中的点
	sub.pb(x);
	for(int i = 0; i < SZ(ch[x]); ++i)
		dfssub(ch[x][i]);
}

int dfs(int x) {
	for(int i = 0; i < SZ(ch[x]); ++i)
		dfs(ch[x][i]);
	sub.clear(), dfssub(x), mex.clear();
	for(int i = 0; i < SZ(sub); ++i) {
		int cursg = 0;
		for(int last = -1, j = sub[i]; j != fa[x]; last = j, j = fa[j]) {
			for(int k = 0; k < SZ(ch[j]); ++k)
				if(ch[j][k] != last)
					cursg ^= sg[ch[j][k]];// 每次删除一条到子树根的链，剩下的子树的sg异或起来就是这种选择下的sg值
		}
		mex.pb(cursg);
	}
	sort(mex.begin(), mex.end());// 排序
	mex.resize(unique(mex.begin(), mex.end()) - mex.begin());// 去重
	// 求出mex
	for(int i = 0; i < SZ(mex); ++i)
		if(i != mex[i]) {
			sg[x] = i;
			break;
		}
	if(sg[x] == -1) sg[x] = SZ(mex);
	return sg[x];
}

class CirclesGame {  
public:  
	string whoCanWin(vector <int> x, vector <int> y, vector <int> r) {
		n = SZ(x);
		for(int i = 0; i < n; ++i) ch[i].clear();
		memset(fa, -1, sizeof fa), memset(sg, -1, sizeof sg);
		for(int i = 0; i < n; ++i) {
			int minr = INF;
			for(int j = 0; j < n; ++j)
				if(r[i] < r[j] && r[j] < minr && sqr(x[i] - x[j]) + sqr(y[i] - y[j]) <= sqr(r[i] - r[j]))
					minr = r[j], fa[i] = j;// 圆的包含关系可以构成一棵树，每个圆的父亲就是包含它的最小圆
			if(fa[i] != -1) ch[fa[i]].pb(i);
		}
		int ans = 0;
		for(int i = 0; i < n; ++i)
			if(fa[i] == -1) ans ^= dfs(i);// 每棵树异或起来
		return ans ? "Alice" : "Bob";
	}  
};  
