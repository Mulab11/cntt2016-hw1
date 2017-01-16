#line 2 "TreeUnion.cpp"  
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

const int N = 300;

int n;
std::vector<int> fa1, fa2, e1[N + 9], e2[N + 9];
int c1[N + 9], c2[N + 9];// c1[i], c2[i]分别表示两棵树中长度为i的路径条数

std::vector<int> get(std::vector<std::string> g) {
	std::string s;
	for(auto t : g) s += t;
	s += ' ';
	std::vector<int> ret;
	for(int i = 0; i < SZ(s); ++i) {
		int j = i, num = 0;
		while(s[j] != ' ') num = num * 10 + s[j] - '0', j++;
		ret.pb(num);
		i = j;
	}
	return ret;
}

void dfs(int x, int fa, std::vector<int> e[], int d, int *c) {
	for(auto y : e[x])
		if(y != fa) {
			c[d + 1]++;
			dfs(y, x, e, d + 1, c);
		}
}

class TreeUnion {  
public:  
	double expectedCycles(vector <string> _fa1, vector <string> _fa2, int K) {
		// K <= 7的话，只能过去一次回来一次，所以就是两条路径拼起来即可
		fa1 = get(_fa1), fa2 = get(_fa2);
		n = SZ(fa1) + 1;
		for(int i = 0; i < n; ++i) e1[i].clear(), e2[i].clear();
		for(int i = 1; i < n; ++i) e1[fa1[i - 1]].pb(i), e1[i].pb(fa1[i - 1]), e2[fa2[i - 1]].pb(i), e2[i].pb(fa2[i - 1]);
		memset(c1, 0, sizeof c1), memset(c2, 0, sizeof c2);
		for(int i = 0; i < n; ++i) dfs(i, -1, e1, 0, c1), dfs(i, -1, e2, 0, c2);// 求出c1, c2
		for(int i = 0; i < n; ++i) c1[i] >>= 1, c2[i] >>= 1;// 每条路径被算了2次
		double p = 0;
		// tree1长度为i，tree2长度为K - 2 - i的概率为c1[i] * c2[K - 2 - i] * 2 * (n - 2)! / n!
		for(int i = 1; K - 2 - i >= 1; ++i)
			p += (double)c1[i] * c2[K - 2 - i] * 2;
		p /= n * (n - 1);
		return p;
	}    
};  
