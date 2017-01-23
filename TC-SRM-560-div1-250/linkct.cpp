#include <bits/stdc++.h>
using namespace std;

class TomekPhone{
public:
	int cnt[55];
	int minKeystrokes(vector <int> freq, vector <int> sz){
		int i, j, mn, mnp, ans = 0;
		sort(freq.begin(), freq.end());
		for(i = 0; i < int(sz.size()); ++ i)
			cnt[i] = 0;
		for(i = int(freq.size()) - 1; i >= 0; -- i){
			for(j = 0, mn = freq.size(), mnp = -1; j < int(sz.size()); ++ j) //Find minimal number of keystrokes for current maximal character
				if(cnt[j] < sz[j] && cnt[j] <= mn)
					mn = cnt[j], mnp = j;
			if(mnp == -1) return -1;
			ans += freq[i] * (mn + 1), ++ cnt[mnp];
		} return ans;
	}
};
