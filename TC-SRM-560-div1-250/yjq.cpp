#include <bits/stdc++.h>
using namespace std;

int n ;

const int MAXN = 60 ;

int cnt[MAXN] ;

class TomekPhone {
		public:
				int minKeystrokes(vector<int> w, vector<int> a) {
						n = w.size();
						sort(w.begin(), w.end());
						for(int i = 0; i < a.size(); i ++) for(int j = 0; j < a[i]; j ++) cnt[j] ++ ;  
						int ans = 0;
						for(int i = 0; i < 50 && n; i ++) for(int j = 0; j < cnt[i] && n; j ++) ans += w[--n] * (i + 1);
						return n ? -1 : ans;
				}
};
