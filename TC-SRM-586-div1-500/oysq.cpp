#line 2 "History.cpp"  
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

const int N = 26;
const int INF = 0x3f3f3f3f;

int n;
std::vector<int> T[N + 9];

std::vector<pii> adj[N + 9];

std::vector<int> get(std::string s) {
	std::vector<int> ret;
	s += ' ';
	for(int i = 0; i < SZ(s); ++i) {
		int j = i, num = 0;
		while(s[j] != ' ') num = num * 10 + s[j++] - '0';
		ret.pb(num), i = j;
	}
	return ret;
}

bool check() {
	// 如果有负环则无解
	static int dis[N + 9], in[N + 9], cnt[N + 9];
	static std::queue<int> q;
	for(int i = 0; i < n; ++i) dis[i] = 0, in[i] = 1, q.push(i), cnt[i] = 0;
	while(!q.empty()) {
		int x = q.front();
		in[x] = 0, q.pop();
		for(auto e : adj[x])
			if(dis[e.fi] > dis[x] + e.se) {
				dis[e.fi] = dis[x] + e.se;
				if(!in[e.fi]) {
					in[e.fi] = 1, q.push(e.fi);
					if((++cnt[e.fi]) > n) return false;
				}
			}
	}
	return true;
}

class History {  
public:  
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries) {  
		n = SZ(dynasties);
		for(int i = 0; i < n; ++i)
			T[i] = get(dynasties[i]);
		for(int i = 0; i < n; ++i)
			adj[i].clear();
		std::string b;
		for(auto s : battles) b += s;
		for(int i = 0; i < SZ(b); i += 6) {// 将题目中的限制化成形如x + c >= y的不等式，然后就是查分约束了
			std::string s = b.substr(i, 5);
			int u = s[0] - 'A', v = s[3] - 'A', x = s[1] - '0', y = s[4] - '0';
			// T[u] + tm[u][x] in [T[v] + tm[v][y] - (tm[u][x + 1] - tm[u][x] - 1), T[v] + tm[v][y + 1] - 1]
			adj[v].pb(mp(u, -T[v][y] + T[u][x + 1] - 1)), adj[u].pb(mp(v, T[v][y + 1] - 1 - T[u][x]));
		}
		std::string ret;
		for(auto s : queries) {
			// 对于每个询问将限制加进去判断有没有解
			int u = s[0] - 'A', v = s[3] - 'A', x = s[1] - '0', y = s[4] - '0';
			adj[v].pb(mp(u, -T[v][y] + T[u][x + 1] - 1)), adj[u].pb(mp(v, T[v][y + 1] - 1 - T[u][x]));
			if(check()) ret += 'Y';
			else ret += 'N';
			adj[u].pop_back(), adj[v].pop_back();
		}
		return ret;
	}  
};  
