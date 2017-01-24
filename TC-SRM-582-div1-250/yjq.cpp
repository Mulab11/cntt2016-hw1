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
} sol ;

vector<int> g[2] ; 

vector<LL> gc ; 

int a[3][3] = {
		{2, 3, 5} ,
		{1, 3, 4} ,
		{2, 9, 4} } ;

int main() { 
		for (int i = 0; i < 2; i ++) for (int j = 0; j < 3; j ++) g[i].push_back(a[i][j]) ; 
		for (int i = 0; i < 3; i ++) gc.push_back(a[2][i]) ; 
		cout <<sol. minimalFatigue(g[0], g[1], gc) << endl ; 
}


