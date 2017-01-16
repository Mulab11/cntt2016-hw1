#line 2 "MagicMolecule.cpp"  
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

int n;
std::vector<int> pw;
std::vector<string> g;
std::vector<pii> edge;
bool used[N];
int ans;

void dfs(int x, int res) {// 当前第x条边，还剩下res个点可以选做点覆盖
	if(res < 0) {// res < 0显然不合法
		return ;
	}
	if(x == SZ(edge)) {// 计算贡献，点覆盖和点独立集互补
		int sum = 0;
		for(int i = 0; i < n; ++i) {
			if(!used[i]) {
				sum += pw[i];
			}
		}
		chkmax(ans, sum);
	}
	else {
		if(used[edge[x].fi] || used[edge[x].se]) {// 已经覆盖
			dfs(x + 1, res);
		}
		else {// 选一个点覆盖，因为是要选最小点覆盖，因此不要考虑两个点都选的情况
			used[edge[x].fi] = true;
			dfs(x + 1, res - 1);
			used[edge[x].fi] = false;
			
			used[edge[x].se] = true;
			dfs(x + 1, res - 1);
			used[edge[x].se] = false;
		}
	}
}

class MagicMolecule {  
public:  
	int maxMagicPower(vector <int> magicPower, vector <string> magicBond) {  
		pw = magicPower;
		g = magicBond;
		edge.clear();
		n = SZ(pw);
		ans = -1;// 初始化，-1表示无解
		memset(used, 0, sizeof used);
		for(int i = 0; i < n; ++i) {
			for(int j = i + 1; j < n; ++j) {
				if(g[i][j] == 'N') {
					edge.pb(mp(i, j));// 构建补图
				}
			}
		}
		dfs(0, n - ceil(n * 2.0 / 3));
		return ans;
	}
};  
