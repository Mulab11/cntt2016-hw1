#include <bits/stdc++.h>
using namespace std;

class TheSwapsDivOne{
public:
	double find(vector <string> seq, int k){
		int i, sum, n; double p, tot, ans = 0.0; string s;
		for(i = 0; i < int(seq.size()); ++ i)
			s += seq[i];
		n = s.length(), tot = 1.0 / (n * (n - 1) / 2);
		for(i = 1, p = 1.0; i <= k; ++ i)
			p = p * (1.0 - (n - 1) * tot) + (1.0 - p) * tot;
		for(i = sum = 0; i < n; ++ i)
			sum += (i + 1) * (n - i);
		tot = 1.0 / (n * (n + 1) / 2);
		for(i = 0; i < n; ++ i)
			ans += (s[i] - '0') * (p * (i + 1) * (n - i) + (1.0 - p) / (n - 1) * (sum - (i + 1) * (n - i))) * tot;
		return ans;
	}
};
