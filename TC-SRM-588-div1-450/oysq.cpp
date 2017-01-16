#line 2 "KeyDungeonDiv1.cpp"  
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

const int INF = 1e9;
const int N = 12;

int n;
std::unordered_set<int> f[1 << N];
int sr[1 << N], sg[1 << N], sw[1 << N];

class KeyDungeonDiv1 {  
public:  
	int maxKeys(vector <int> dr, vector <int> dg, vector <int> rr, vector <int> rg, vector <int> rw, vector <int> key) {
		n = SZ(dr);
		for(int i = 0; i < (1 << n); ++i) f[i].clear();
		// f[i][s]表示集合i，有s个w变成了r，剩下的变成g的情况是否存在
		for(int i = 0; i <= key[2]; ++i) f[0].insert(i);
		// sr[i], sg[i], sw[i]分别表示开门的集合为i的时候，剩下的r, g, w的个数
		sr[0] = key[0], sg[0] = key[1], sw[0] = key[2];
		int ans = 0;
		for(int i = 0; i < (1 << n); ++i) {
			for(int j = 0; j < n; ++j)// 枚举最后开的门
				if(i >> j & 1) {
					int t = i ^ (1 << j);
					sr[i] = sr[t] + rr[j] - dr[j], sg[i] = sg[t] + rg[j] - dg[j], sw[i] = sw[t] + rw[j];// 更新sr, sg, sw
					for(auto x : f[i ^ (1 << j)]) {
						int r = sr[t] + x, g = sg[t] + sw[t] - x;// 之前的r, g
						if(r >= dr[j] && g >= dg[j])// 判断是否能开当前的门
							for(int k = 0; k <= rw[j]; ++k)
								f[i].insert(x + k);// 枚举当前门的w分配给r, g的方案
					}
				}
			if(SZ(f[i])) chkmax(ans, sr[i] + sg[i] + sw[i]);// 更新答案
		}
		return ans;
	}    
};  
