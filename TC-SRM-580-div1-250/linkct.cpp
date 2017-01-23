#include <bits/stdc++.h>
using namespace std;

class EelAndRabbit{
public:
	int getmax(vector <int> l, vector <int> t){
		int i, j, k, c, ans = 0, n;
		n = l.size();
		for(i = 0; i < n; ++ i)
			for(j = i + 1; j < n; ++ j){
				for(k = c = 0; k < n; ++ k)
					if((t[i] - t[k] >= 0 && t[i] - t[k] - l[k] <= 0) || (t[j] - t[k] >= 0 && t[j] - t[k] - l[k] <= 0))
						++ c;
				if(c > ans) ans = c;
			}
		return ans;
	}
};
