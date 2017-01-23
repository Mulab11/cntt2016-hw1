#include <bits/stdc++.h>
using namespace std;

class TheDevice{
public:
	int minimumAdditional(vector <string> plates){
		int i, j, ans = 0, c[2];
		int n = plates.size(), m = plates[0].length();
		for(i = 0; i < m; ++ i){
			for(j = c[0] = c[1] = 0; j < n; ++ j)
				++ c[plates[j][i] - '0'];
			ans = max(ans, max(0, 2 - c[1]) + max(0, 1 - c[0]));
			//Only 2x'1' and 1x'0' are needed
		} return ans;
	}
};
