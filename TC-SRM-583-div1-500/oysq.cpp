#line 2 "TurnOnLamps.cpp"  
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

const int N = 50, INF = 1e9;

int n;
bool s[N + 9];
bool im[N + 9];
std::vector<int> adj[N + 9];
int f[N + 9][2];// f[x][p] 表示以x为根的子树中，点到x的路径数奇偶性为p的最小答案。

void dp(int x) {
	f[x][0] = 0, f[x][1] = INF;
	int g[2];
	for(auto y : adj[x]) {
		dp(y);
		g[0] = f[x][0], g[1] = f[x][1];
		if(im[y]) {
			if(s[y]) {// 不能选x->y
				f[x][0] = g[0] + std::min(f[y][0], f[y][1]);
				f[x][1] = g[1] + std::min(f[y][0], f[y][1]);
			}
			else {// 一定要选x->y
				f[x][0] = g[1] + std::min(f[y][0], f[y][1] - 1);
				f[x][1] = g[0] + std::min(f[y][0] + 1, f[y][1]);
			}
		}
		else {// x->y选不选都可以
			f[x][0] = std::min(g[0] + std::min(f[y][0], f[y][1]), g[1] + std::min(f[y][0], f[y][1] - 1));
			f[x][1] = std::min(g[1] + std::min(f[y][0], f[y][1]), g[0] + std::min(f[y][0] + 1, f[y][1]));
		}
	}
}

class TurnOnLamps {  
public:  
	int minimize(vector <int> r, string initState, string isImportant) {  
		n = SZ(r) + 1;
		for(int i = 0; i < n; ++i) adj[i].clear();
		for(int i = 0; i < n - 1; ++i) adj[r[i]].pb(i + 1);
		for(int i = 0; i < n - 1; ++i) s[i + 1] = initState[i] - '0';
		for(int i = 0; i < n - 1; ++i) im[i + 1] = isImportant[i] - '0';
		dp(0);
		return std::min(f[0][0], f[0][1]);
	}    
};  
