#include <bits/stdc++.h>
using namespace std;

class TriangleXor{
public:
	double ht[100005];
	inline double calc(int i, int n){return i ? 1.0 / (1.0 / i + 1.0 / n) : 0.0;}
	int theArea(int n){
		int i; double ans = 0.0; ht[0] = 0.0;
		for(i = 1; i <= n; ++ i)
			ht[i] = 1.0 / (1.0 / i + 1.0 / n);
		for(i = 1; i <= n; i += 2)
			ans += ht[i] - ht[i - 1];
		if(n & 1){
			for(i = 2; i <= n; ++ i)
				ans += 0.5 * ht[n - i + 1] / n * (n - i + 1) * (2 * i - 2) * ((i & 1) ? -1 : 1);
		}else{
			ans += n * 0.5;
			for(i = 2; i <= n; ++ i)
				ans += 0.5 * ht[n - i + 1] / n * (n - i + 1) * (2 * i - 2) * ((i & 1) ? 1 : -1);
		} return ans;
	}
};
