#include <bits/stdc++.h>

using namespace std;

int n = 0 ; 

const int MAXN = 60 ; 

vector<int> vis[MAXN];

int ans[MAXN] ;

int use[MAXN];

char get(int x) { 
		if (x == 1) return '?' ; 
		if (x == 2) return '+' ; 
		return '-' ; 
}

class SurveillanceSystem {
		public:
				string getContainerInfo(string s, vector<int> info, int l) {
						n = s.length();
						
						for(int i = 0; i < info.size(); i ++) info[i][use] ++ ; 

						for(int i = 0; i <= n - l ; i ++)  {
								int cnt = 0;
								for(int j = i; j < i + l; j ++) cnt += (s[j] == 'X');
								vis[cnt].push_back(i);
						}
						for(int i = 0; i <= MAXN - 10; i++) {
								if(use[i]) {
										for(int j = 0; j < n; j++) {
												int cnt = 0;
												for(int k = 0; k < vis[i].size(); k++) cnt += (j >= vis[i][k] && j < vis[i][k] + l);
												if(cnt) j[ans] = max(ans[j], 1);
												if(cnt + i[use] > vis[i].size()) j[ans] = max(ans[j], 2);
										}
								}
						}
						string res;
						for(int i = 0; i < n; i ++) res += get(ans[i]) ; 
						return res;
				}
};
