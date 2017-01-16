#line 2 "SkiResorts.cpp"  
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
const ll INF = 1e18;

std::queue<int> q;
bool inq[N + 9];// inq[i]表示i是否在队列内
std::vector<int> val;// 离散化后的权值
ll f[N + 9][N + 9];// f[i][j] 表示从0到i，且i点权值为val[j]的时候，最小的代价，用队列更新答案

ll abs(ll x) {
	return x < 0 ? -x : x;
}

void push(int x) {// 入队
	if(!inq[x]) inq[x] = true, q.push(x);
}

int pop() {// 出队
	int x = q.front();
	q.pop(), inq[x] = false;
	return x;
}

class SkiResorts {  
public:  
	long long minCost(vector <string> g, vector <int> a) {
		// 离散化
		val = a;
		std::sort(val.begin(), val.end());
		val.resize(std::unique(val.begin(), val.end()) - val.begin());

		int n = SZ(a);

		// 初始化
		memset(f, -1, sizeof f);
		for(int i = 0; i < SZ(val); ++i)
			f[0][i] = abs(val[i] - a[0]);

		// 队列维护dp值
		push(0);
		while(!q.empty()) {
			int x = pop();
			for(int y = 0; y < n; ++y)
				if(g[x][y] == 'Y')
					for(int u = 0; u < SZ(val); ++u)
						for(int v = 0; v <= u; ++v)
							if(f[y][v] == -1 || f[x][u] + abs(val[v] - a[y]) < f[y][v])
								f[y][v] = f[x][u] + abs(val[v] - a[y]), push(y);
		}

		ll ans = INF;
		for(int i = 0; i < SZ(val); ++i)
			chkmin(ans, f[n - 1][i]);
		return ans == INF ? -1 : ans;
	}  
};  
