#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair <int, int> pii;

class GUMIAndSongsDiv1{
public:
	int n, f[55]; pii song[55];
	int maxSongs(vector <int> dur, vector <int> tone, int t){
		int i, j, k, ans = 0;
		n = dur.size();
		for(i = 0; i < n; ++ i)
			song[i] = pii(tone[i], dur[i]);
		sort(song, song + n);
		for(i = 0; i < n; ++ i){
			if(t < song[i].se) continue;
			memset(f, 0x3f, sizeof(f));
			f[1] = song[i].se, ans = max(ans, 1);
			for(j = i + 1; j < n; ++ j)
				for(k = j - i + 1; k; -- k){
					f[k] = min(f[k], f[k - 1] + song[j].se);
					if(f[k] + song[j].fi - song[i].fi <= t)
						ans = max(ans, k);
				}
		} return ans;
	}
};
