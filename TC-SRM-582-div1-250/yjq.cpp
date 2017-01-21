#include <bits/stdc++.h>

using namespace std;

int n, m ; 

const int MAXN  = 110 ; 

typedef long long LL ; 


pair<int, LL> tmp[MAXN] ; 


bool cmp(int x, int y) {return x > y; } 
bool cmpP(pair<int, LL> a, pair<int, LL> b) {return a > b; } 

class SpaceWarDiv1 {
		public:
				LL minimalFatigue(vector<int> Gay, vector<int> Sth, vector<LL> Cnt) {
						n = Gay.size(), m = Sth.size();
						for(int i = 0; i < m; i++)
								tmp[i] = make_pair(Sth[i], Cnt[i]);
						sort(tmp , tmp + m, cmpP) ; 
						sort(Gay.begin(), Gay.end(), cmp) ; 
						LL ans = 0, sum = 0;
						for(int i = 0, j = 0; i < m; i ++) {
								sum += tmp[i].second;
								while(j < n && Gay[j] >= tmp[i].first) j++;
								if (!j) return -1;
								if ((sum + j - 1) / j > ans) ans = (sum + j - 1) / j ; 
						}
						return ans;
				}
};
