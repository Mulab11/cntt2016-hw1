#line 2 "ColorfulChocolates.cpp"  
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

const int SIGMA = 26;

std::vector<int> p[SIGMA];
// p[i] means posotions of letter i + 'A'

class ColorfulChocolates {  
public:
	bool check(const std::vector<int> &p, int l, int r, int lim) {
		// enumerate the ans interval and check
		for(int i = p[l]; i <= p[r]; ++i) {
			int cur = 0;
			for(int k = l; k <= r; ++k)
				cur += abs(p[k] - (k - l + i));
			if(cur <= lim) return true;
		}
		return false;
	}
	int maximumSpread(string ch, int maxSwaps) {
		// init p[]
		for(int i = 0; i < SIGMA; ++i) p[i].clear();
		for(int i = 0; i < SZ(ch); ++i) p[ch[i] - 'A'].pb(i);
		int ans = 1;
		// enumerate the ans letter
		for(int i = 0; i < SIGMA; ++i)
			for(int j = 0; j < SZ(p[i]); ++j)
				for(int k = j + ans; k < SZ(p[i]); ++k)
					// enumerate the interval of certain letter and update
					if(!check(p[i], j, k, maxSwaps)) break;
					else ans = k - j + 1;
		return ans;
	}  
};  
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                