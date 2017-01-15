#line 2 "UnknownTree.cpp"  
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
const int MOD = 1000000009;

int n;

int calc(std::vector<int> p) {// 对于一颗子树，到根距离集合为p的情况下有多少种不同的方案
	int ret = 1;
	p.pb(0), std::sort(p.begin(), p.end());
	for(int i = 1, j = -1; i < SZ(p); ++i) {
		while(p[j + 1] < p[i]) ++j;
		ret = (ll)ret * (j + 1) % MOD;// 对于距离p[i]，它能连向所有距离 < p[i]的点作为父亲
	}
	return ret;
}

int center(std::vector<int> dA, std::vector<int> dB, std::vector<int> dC, int ctr) {// ctr为中心点
	bool vis[N + 9] = {false};
	std::vector<int> on, ch[N + 9], chA, chB, chC;// on表示链上的点，ch[i]表示子树i的距离集合，chA,chB,chC同理
	on.pb(ctr), vis[ctr] = true;// 中心点一定在链上
	for(int i = 0; i < n; ++i)
		if(!vis[i]) {
			int f1 = dA[i] + dB[i] == dA[ctr] + dB[ctr] && dC[i] > dC[ctr];
			int f2 = dB[i] + dC[i] == dB[ctr] + dC[ctr] && dA[i] > dA[ctr];
			int f3 = dC[i] + dA[i] == dC[ctr] + dA[ctr] && dB[i] > dB[ctr];
			if(f1 + f2 + f3 == 2) on.pb(i), vis[i] = true;// 满足任意两个条件等价于在链A-ctr或B-ctr或C-ctr上
		}
	// 两点不能在链上的同一个地方
	for(int i = 0; i < SZ(on); ++i)
		for(int j = i + 1; j < SZ(on); ++j)
			if(dA[on[i]] == dA[on[j]] && dB[on[i]] == dB[on[j]] && dC[on[i]] == dC[on[j]])
				return 0;
	for(int i = 0; i < n; ++i)
		if(!vis[i]) {
			if(dA[i] + dA[ctr] + dB[ctr] == dB[i] && dA[i] + dA[ctr] + dC[ctr] == dC[i]) chA.pb(dA[i]), vis[i] = true;// 点在A的子树内，以下同理
			else if(dB[i] + dB[ctr] + dC[ctr] == dC[i] && dB[i] + dB[ctr] + dA[ctr] == dA[i]) chB.pb(dB[i]), vis[i] = true;// B
			else if(dC[i] + dC[ctr] + dA[ctr] == dA[i] && dC[i] + dC[ctr] + dB[ctr] == dB[i]) chC.pb(dC[i]), vis[i] = true;// C
			else {
				for(int j = 0; j < SZ(on); ++j)
					if(dA[i] > dA[on[j]] && dA[i] - dA[on[j]] == dB[i] - dB[on[j]] && dA[i] - dA[on[j]] == dC[i] - dC[on[j]]) {// on[j]
						ch[j].pb(dA[i] - dA[on[j]]);
						vis[i] = true;
						break;
					}
			}
			if(!vis[i]) return 0;// 如果一个点不能挂在任何一点链上的点下，显然无解
		}
	// 每颗子树都是独立的，累乘所有方案
	int ret = (ll)calc(chA) * calc(chB) % MOD * calc(chC) % MOD;
	for(int i = 0; i < SZ(on); ++i)
		ret = (ll)ret * calc(ch[i]) % MOD;
	return ret;
}

int chain(std::vector<int> dA, int dAB, std::vector<int> dB, int dBC, std::vector<int> dC) {
	bool vis[N + 9] = {false};
	std::vector<int> on, ch[N + 9], chA, chB, chC;
	for(int i = 0; i < n; ++i) {
		bool f1 = dA[i] + dB[i] == dAB;
		bool f2 = dB[i] + dC[i] == dBC;
		bool f3 = dA[i] + dC[i] == dAB + dBC;
		if(f3 && (f1 || f2)) on.pb(i), vis[i] = true;// 判断是否在链上
	}
	// 两点不能在链上的同一个地方
	for(int i = 0; i < SZ(on); ++i)
		for(int j = i + 1; j < SZ(on); ++j)
			if(dA[on[i]] == dA[on[j]] && dB[on[i]] == dB[on[j]] && dC[on[i]] == dC[on[j]])
				return 0;
	for(int i = 0; i < n; ++i)
		if(!vis[i]) {
			if(dA[i] + dAB == dB[i] && dA[i] + dAB + dBC == dC[i]) chA.pb(dA[i]), vis[i] = true;// 点在A的子树内，以下同理
			else if(dB[i] + dAB == dA[i] && dB[i] + dBC == dC[i]) chB.pb(dB[i]), vis[i] = true;// B
			else if(dC[i] + dBC == dB[i] && dC[i] + dBC + dAB == dA[i]) chC.pb(dC[i]), vis[i] = true;// C
			else {
				for(int j = 0; j < SZ(on); ++j)
					if(dA[i] > dA[on[j]] && dA[i] - dA[on[j]] == dB[i] - dB[on[j]] && dA[i] - dA[on[j]] == dC[i] - dC[on[j]]) {// on[j]
						ch[j].pb(dA[i] - dA[on[j]]);
						vis[i] = true;
						break;
					}
			}
			if(!vis[i]) return 0;
		}
	// 每颗子树都是独立的，累乘所有方案
	int ret = (ll)calc(chA) * calc(chB) % MOD * calc(chC) % MOD;
	for(int i = 0; i < SZ(on); ++i)
		ret = (ll)ret * calc(ch[i]) % MOD;
	return ret;
}

int chain(std::vector<int> dA, std::vector<int> dB, std::vector<int> dC) {
	// AB之间的距离只可能是dA[i] +/- dB[i]，BC同理
	std::vector<int> dAB, dBC;
	for(int i = 0; i < n; ++i) {
		dAB.pb(dA[i] + dB[i]);
		if(dA[i] != dB[i]) dAB.pb(abs(dA[i] - dB[i]));
	}
	for(int i = 0; i < n; ++i) {
		dBC.pb(dB[i] + dC[i]);
		if(dB[i] != dC[i]) dBC.pb(abs(dB[i] - dC[i]));
	}
	std::sort(dAB.begin(), dAB.end()), dAB.resize(std::unique(dAB.begin(), dAB.end()) - dAB.begin());
	std::sort(dBC.begin(), dBC.end()), dBC.resize(std::unique(dBC.begin(), dBC.end()) - dBC.begin());
	int ret = 0;
	// 枚举dAB,dBC
	for(int i = 0; i < SZ(dAB); ++i)
		for(int j = 0; j < SZ(dBC); ++j)
			(ret += chain(dA, dAB[i], dB, dBC[j], dC)) %= MOD;
	return ret;
}

class UnknownTree {  
public:  
	int getCount(vector <int> dA, vector <int> dB, vector <int> dC) {  
		n = SZ(dA);
		int ans = 0;
		// 枚举中心点，形如 A-center-B
		//                     |
		//                     C
		for(int i = 0; i < n; ++i)
			(ans += center(dA, dB, dC, i)) %= MOD;
		(ans += chain(dA, dB, dC)) %= MOD;// 链状 A-B-C
		printf("%d\n", ans);
		(ans += chain(dB, dA, dC)) %= MOD;// 链状 B-A-C
		printf("%d\n", ans);
		(ans += chain(dA, dC, dB)) %= MOD;// 链状 A-C-B
		return ans;
	}  
}; 
