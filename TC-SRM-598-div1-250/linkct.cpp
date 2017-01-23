#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;

class BinPacking{
public:
	int n; set <pii> item;
	int minBins(vector <int> item_){
		int i, ans = 0, now;
		set <pii> :: iterator it;
		n = item_.size();
		for(i = 0; i < n; ++ i)
			item.insert(pii(item_[i], i));
		while(item.size() >= 2){
			-- (it = item.end());
			if(it -> fi == 100) break;
			now = it -> fi; item.erase(it);
			it = item.upper_bound(pii(300 - now, n));
			if(it != item.begin())
				item.erase(-- it);
			++ ans;
		} if(item.size() <= 1) return ans + item.size();
		return ans + (int(item.size()) - 1) / 3 + 1;
	}
};
