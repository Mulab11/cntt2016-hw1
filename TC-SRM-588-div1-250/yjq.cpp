#include <bits/stdc++.h>

using namespace std;

int n ; 

const int MAXN = 60 ; 
struct Opt {
		int d, x ; 
		bool operator < (const Opt ano) const {
				if (d ^ ano.d) return d < ano.d ; 
				return x < ano.x ; 
		}
} a[MAXN] ; 
class GUMIAndSongsDiv1 {
		public:
				int maxSongs(vector<int> d, vector<int> x, int t) {
						n = d.size();
						for(int i = 0; i < n; i++) a[i].d = d[i], a[i].x = x[i] ; 
						sort(a, a + n);
						int ans = 0;
						for(int i = 0; i < n; i++) {
								for(int j = 0; j < n; j++) {
										int l = a[i].x, r = a[j].x;
										int cnt = 0;
										for(int k = 0, ret = t - (r - l); k < n; k++) {
												if (l <= a[k].x && a[k].x <= r) { 
														if (ret >= a[k].d) ret -= a[k].d, cnt ++ ;
												}
										}
										ans = max(ans, cnt);
								}
						}
						return ans;
				}
};
