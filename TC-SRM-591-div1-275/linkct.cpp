#include <bits/stdc++.h>
using namespace std;

class TheTree{
public:
	int maximumDiameter(vector <int> cnt_){
		int ans = cnt_.size(), d = ans, i, j;
		vector <int> cnt; cnt.push_back(1);
		for(i = 0; i < d; ++ i) cnt.push_back(cnt_[i]);
		for(i = 0; i <= d; i = j){
			for(j = i + 1; j <= d && cnt[j] >= 2; ++ j) ;
			ans = max(ans, d - i + j - i - 1);
		} return ans;
	}
};
