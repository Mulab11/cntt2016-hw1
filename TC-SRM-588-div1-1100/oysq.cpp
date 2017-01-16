#line 2 "GameInDarknessDiv1.cpp"  
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
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int id[N + 9][N + 9], tot;
int A, B;
std::vector<int> adj[N * N + 9];
int dA[N * N + 9], dB[N * N + 9];

void getdis(int x, int fa, int d, int *dis) {// 求距离
	dis[x] = d;
	for(auto y : adj[x])
		if(y != fa)
			getdis(y, x, d + 1, dis);
}

bool chk(int x, int fa, int d) {// 判断是否深度 >= 3
	if(d == 3) return true;
	for(auto y : adj[x])
		if(y != fa)
			if(chk(y, x, d + 1))
				return true;
	return false;
}

class GameInDarknessDiv1 {  
public:  
	string check(vector <string> field) {  
		tot = 0, A = B = -1;
		int n = SZ(field), m = SZ(field[0]);
		// 将每个empty结点重标号存在id中
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(field[i][j] != '#') {
					id[i][j] = tot++;
					if(field[i][j] == 'A') A = id[i][j];
					if(field[i][j] == 'B') B = id[i][j];
				}
		for(int i = 0; i < tot; ++i) adj[i].clear();
		// 连边
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(field[i][j] != '#')
					for(int t = 0; t < 4; ++t) {
						int x = i + d[t][0], y = j + d[t][1];
						if(x >= 0 && x < n && y >= 0 && y < m && field[x][y] != '#')
							adj[id[i][j]].pb(id[x][y]);
					}
		// 分别求出每个点到A, B的距离
		getdis(A, -1, 0, dA), getdis(B, -1, 0, dB);
		// 检查是否存在一个点满足dA - dB >= 2 && 这个点有至少三棵子树深度 >= 3
		for(int i = 0; i < tot; ++i)
			if(dA[i] - dB[i] >= 2) {
				int cnt = 0;
				for(auto j : adj[i])
					if(chk(j, i, 1))
						cnt++;
				if(cnt >= 3) return "Bob wins";
			}
		return "Alice wins";
	}  
};  
