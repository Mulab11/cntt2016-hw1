#line 2 "PiecewiseLinearFunction.cpp"  
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


class PiecewiseLinearFunction {  
public:  
	int maximumSolutions(vector <int> y) {  
		int n = SZ(y);
		std::vector<double> v;
		for(int i = 1; i < n; ++i)
			if(y[i] == y[i - 1]) return -1;
		for(auto i : y) v.pb(i), v.pb(i + 0.5), v.pb(i - 0.5);// 答案肯定在所有的y，以及y附近的地方
		int ans = 0;
		for(auto i : v) {// 枚举答案对应的纵坐标
			int cur = 0;
			for(int j = 1; j < n; ++j)
				if(std::min(y[j - 1], y[j]) <= i && i <= std::max(y[j - 1], y[j]))
					cur++;
			for(int j = 1; j < n - 1; ++j)// 减去重复计算的个数
				if(i == y[j]) cur--;
			chkmax(ans, cur);
		}
		return ans;
	}    
};  
