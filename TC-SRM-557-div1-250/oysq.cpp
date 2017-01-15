#line 2 "FoxAndMountainEasy.cpp"  
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


class FoxAndMountainEasy {  
public:
	// check if x steps can make up sum of y
	bool ok(int x, int y) {
		return -x <= y && y <= x && !((x - y) & 1);
	}
	string possible(int n, int h0, int hn, string history) {
		// 'U' equals '+', 'D' equals '-'
		int min = 0, sum = 0;
		for(int i = 0; i < SZ(history); ++i) {
			if(history[i] == 'U') sum++;
			else sum--;
			chkmin(min, sum);
		}
		// enumerate the beginning of "history" in original "h"
		for(int i = 0; i + SZ(history) <= n; ++i) {
			int pre = i, suf = n - i - SZ(history);
			// h0 + presum >= -min -> presum >= -h0 - min
			// presum >= -pre
			// sufsum <= suf
			// sufsum + presum = hn - h0 - sum = tmp <= suf + presum
			int tmp = hn - h0 - sum, lb = std::max(tmp - suf, std::max(-pre, -h0 - min));
			for(int presum = lb; presum <= lb + 1; ++presum)
				if(ok(pre, presum) && ok(suf, tmp - presum))
					return "YES";
		}
		return "NO";
	}  	  
};  
