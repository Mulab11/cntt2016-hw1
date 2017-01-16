#line 2 "Egalitarianism.cpp"  
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
const int INF = 0x3f3f3f3f;

int g[N + 9][N + 9];

class Egalitarianism {  
public:  
	int maxDifference(vector <string> s, int d) {  
		int n = SZ(s);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(s[i][j] == 'Y') g[i][j] = 1;
				else {
					if(i == j) g[i][j] = 0;
					else g[i][j] = INF;
				}
		// 最短路
		for(int k = 0; k < n; ++k)
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < n; ++j)
					chkmin(g[i][j], g[i][k] + g[k][j]);
		int ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				chkmax(ans, g[i][j]);
		// 答案 = max{mindist(i, j)} * d
		return ans == INF ? -1 : ans * d;
	}    
};  
