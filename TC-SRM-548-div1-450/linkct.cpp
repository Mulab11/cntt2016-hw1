#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
const int MAXN = 55;

class KingdomAndDice{
	public:
		vector <int> all; int cnt[MAXN], f[MAXN * MAXN], n;
		double newFairness(vector <int> fi, vector <int> se, int X){
			int i, j, k, m = 0, tot = 0;
			sort(se.begin(), se.end());
			n = fi.size();
			for(i = 0; i < n; ++ i){
				all.push_back(fi[i]);
				all.push_back(se[i]);
			} sort(all.begin(), all.end());
			for(i = j = 0; i < n * 2; ++ i){
				if(!all[i]) continue;
				while(j < n && all[i] > se[j]) ++ j;
				if(!j) continue;
				cnt[j] += all[i] - all[i - 1] - 1;
				//For each i, calc cnt[i] = all available number greater than exactly i numbers in the second array
			} cnt[n] += X - all[i - 1];
			memset(f, 0x3f, sizeof(f));
			for(i = 1, f[0] = 0; i <= n; ++ i) //f[i]: minimal numbers needed for making probability i/n^2
				for(j = n * n; j >= 0; -- j)
					for(k = 1; k <= cnt[i] && i * k <= j; ++ k)
						f[j] = min(f[j], f[j - i * k] + k);
			for(i = 0; i < n; ++ i)
				if(fi[i]){
					for(j = 0; j < n; ++ j)
						if(fi[i] > se[j]) ++ tot;
				}else ++ m;
			for(i = n & 1; i <= n * n; i += 2){
				if((n * n - i) / 2 >= tot && f[(n * n - i) / 2 - tot] <= m)
					return 1.0 * (n * n - i) / (2 * n * n);
				if((n * n + i) / 2 >= tot && f[(n * n + i) / 2 - tot] <= m)
					return 1.0 * (n * n + i) / (2 * n * n);
			}
		}
};
