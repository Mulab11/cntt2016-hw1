#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3005, INF = 0x3f3f3f3f;

class FoxAndAvatar{
public:
	int dp[MAXN][MAXN];
	inline void update(int &a, int b){if(a > b) a = b;}
	int minimalSteps(int n, int w, int x){
		int i, j, k, l, cur, last, delta;
		memset(dp, 0x3f, sizeof(dp));
		dp[0][x - 1] = n - x;
		for(i = 0; i < 4; ++ i){
			for(j = 0; j < x; ++ j){
				if((cur = dp[i][j]) == INF) continue;
				last = (j % w) + 1;
				for(k = 1; k < last; ++ k){
					if(cur <= w - last) delta = 0;
					else delta = (cur - (w - last)) / w * k + min((cur - (w - last)) % w, k);
					for(l = 1; l <= j / w + 1; ++ l)
						update(dp[i + 1][j - l * k], cur - delta);
				}
				for(k = 1, last = w - last; k <= last; ++ k){
					if(cur <= last) delta = min(k, cur);
					else delta = k + (cur - last) / w * k + min(max(((cur - last) % w) - (w - last), 0), k);
					for(l = 1; l <= j / w; ++ l)
						update(dp[i + 1][j - l * k], cur - delta);
				}
				for(k = last + 1; k <= w; ++ k)
					for(l = 1; l <= j / w; ++ l)
						update(dp[i + 1][j - k * l], cur);
				if(cur <= last) update(dp[i + 1][j], 0);
				else update(dp[i + 1][j], last);
			}
		}
		for(i = 0; i <= 4; ++ i)
			if(dp[i][0] == 0)
				break;
		return i;
	}
};
