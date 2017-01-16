#line 2 "SurveillanceSystem.cpp"  
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

class SurveillanceSystem {  
public:  
	string getContainerInfo(string s, vector <int> a, int L) {  
		int n = SZ(s), m = SZ(a);
		std::vector<int> pos[N + 9];
		int cnt[N + 9] = {0};
		for(int i = 0; i + L - 1 < n; ++i) {
			int c = 0;
			for(int j = 0; j < L; ++j)
				c += s[i + j] == 'X';
			pos[c].pb(i);// 把和可能为c的位置放在一起
		}
		for(int i = 0; i < m; ++i)
			cnt[a[i]]++;// camera中某个和的个数
		std::string ret;
		for(int i = 0; i < n; ++i) {
			bool f1 = true, f2 = false;
			// f1, f2 分别表示能否不被扫到，被扫到
			for(int j = 0; j <= L; ++j) {
				int c = 0;
				for(int k = 0; k < SZ(pos[j]); ++k)
					if(pos[j][k] + L - 1 < i || pos[j][k] > i)
						c++;
				if(c < cnt[j]) f1 = false;// 当前和的camera太多了，一定会扫到
				if(SZ(pos[j]) - c && cnt[j]) f2 = true;// 存在camera可以扫到
			}
			if(f1 && f2) ret += '?';
			else if(f1) ret += '-';
			else ret += '+';
		}
		return ret;
	}    
};  
