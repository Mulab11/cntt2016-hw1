#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 2505;

class LittleElephantAndRGB{
public:
	int col[MAXN], cnt[MAXN][MAXN], n;
	LL getNumber(vector <string> input, int m){
		int i, j, cur, mx, sfm; LL ans = 0LL;
		for(i = n = 0; i < int(input.size()); ++ i)
			for(j = 0; j < int(input[i].length()); ++ j)
				col[++ n] = int(input[i][j] == 'G');
		memset(cnt, 0, sizeof(cnt));
		for(i = n; i; -- i){
			memcpy(cnt[i], cnt[i + 1], sizeof(cnt[i]));
			for(j = i, cur = mx = sfm = 0; j <= n; ++ j){
				if(col[j]){ if(mx < (++ cur)) ++ mx;}
				else cur = 0;
				if(cur == j - i + 1) sfm = cur;
				if(mx >= m) ++ cnt[i][m];
				else ++ cnt[i][sfm];
			}
		}
		for(i = 1; i < n; ++ i){
			for(j = m - 1; j >= 0; -- j) cnt[i + 1][j] += cnt[i + 1][j + 1];
			for(j = i, cur = mx = sfm = 0; j; -- j){
				if(col[j]){ if(mx < (++ cur)) ++ mx;}
				else cur = 0;
				if(cur == i - j + 1) sfm = cur;
				if(mx >= m) ans += (n - i) * (n - i + 1) / 2;
				else ans += cnt[i + 1][m - sfm];
			}
		} return ans;
	}
};
