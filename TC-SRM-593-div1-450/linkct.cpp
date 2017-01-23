#include <bits/stdc++.h>
using namespace std;

class MayTheBestPetWin{
public:
	bool f[1000005]; int n, ans;
	int calc(vector <int> a, vector <int> b){
		int i, j, sum = 0, sa = 0, sb = 0;
		n = a.size();
		memset(f, false, sizeof(f));
		f[0] = true;
		for(i = sum = 0; i < n; ++ i){
			sum += a[i] + b[i];
			sa += a[i], sb += b[i];
			for(j = sum; j >= a[i] + b[i]; -- j)
				if(f[j - a[i] - b[i]]) f[j] = true;
		}
		for(i = 0, ans = sum; i <= sum; ++ i)
			if(f[i]) ans = min(ans, max(i - sa, sb - i));
		return ans;
	}
};
