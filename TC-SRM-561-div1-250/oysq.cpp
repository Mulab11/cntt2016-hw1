#line 2 "ICPCBalloons.cpp"  
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

vector<int> large, medium;// 两种大小的气球集合
vector<int> plarge, pmedium;// 被分配给两种气球的题目

int solve(vector<int> p, vector<int> q) {// 气球集合为p, 题目集合为q, 最少移动次数
	sort(p.rbegin(), p.rend()), sort(q.rbegin(), q.rend());// 降序排序
	int sump = accumulate(p.begin(), p.end(), 0), sumq = accumulate(q.begin(), q.end(), 0);
	if(sump < sumq) return INF;// 如果气球的和 < 题目的和，显然无解
	int ret = 0;
	for(int i = 0; i < SZ(q); ++i) {
		int vp = i < SZ(p) ? p[i] : 0, vq = i < SZ(q) ? q[i] : 0;
		ret += max(0, vq - vp);// 如果p[i] < q[i], 那么代价为q[i] - p[i], 否则为0
	}
	return ret;
}

class ICPCBalloons {  
public:  
	int minRepaintings(vector <int> bc, string bs, vector <int> ma) {  
		large.clear(), medium.clear();
		// 将气球分成两类
		for(int i = 0; i < SZ(bc); ++i)
			if(bs[i] == 'M') medium.pb(bc[i]);
			else large.pb(bc[i]);
		int ans = INF;
		for(int i = 0; i < (1 << SZ(ma)); ++i) {// 2 ^ SZ(ma) 枚举每道题被分到了大气球还是中气球
			plarge.clear(), pmedium.clear();
			// 将题目分成两类
			for(int j = 0; j < SZ(ma); ++j)
				if(i >> j & 1) plarge.pb(ma[j]);
				else pmedium.pb(ma[j]);
			chkmin(ans, solve(medium, pmedium) + solve(large, plarge));// 更新答案
		}
		if(ans == INF) return -1;// 无解判断
		else return ans;
	}    
};  
