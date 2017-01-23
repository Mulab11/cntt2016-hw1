#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;

class PiecewiseLinearFunction{
public:
	vector <int> y; int n;
	inline int sgn(LL x){return x == 0LL ? 0 : (x > 0LL ? 1 : -1);}
	inline int check(int x){
		int i, ret = 0;
		for(i = 0; i < n; ++ i)
			if(y[i] == x) ++ ret;
		for(i = 1; i < n; ++ i)
			if(sgn(LL(y[i - 1]) - x) * sgn(LL(y[i]) - x) == -1)
				++ ret;
		return ret;
	}
	int maximumSolutions(vector <int> y_){
		int i, ans = 0;
		n = y_.size();
		for(i = 0; i < n; ++ i)
			y_[i] <<= 1;
		y = y_; sort(y_.begin(), y_.end());
		for(i = 0; i < n; ++ i){
			ans = max(ans, check(y_[i]));
			if(i + 1 < n){
				if(y[i] == y[i + 1]) return -1;
				ans = max(ans, check((LL(y_[i]) + y_[i + 1]) >> 1));
			}
		} return ans;
	}
};
