#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <bitset>
#include <vector>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> PII;
const	int N = 51;
const	int inf = 1e9;
const	ll Inf = 1e16;
const	int P = (int)1e9 + 7;

bool st;
int cost[N][N], sum[N][N], n, m;
char str[N];
int dp[2][N][N][N][N];
bool en;

int Work(int p, int x, int y, int yl, int yr){
	int &res = dp[p][x][y][yl][yr];
	if(res != -1) return res;
	if(p == 1){
		//defender
		if(x == n){
			res = 0;
		}else{
			res = Work(0, x, y, yl, yr);
			if((y < yl || y > yr) && (yr - yl + 2 < m)){
				res = max(res, Work(0, x, y, min(y, yl), max(y, yr)));
			}
		}
	}else{
		//attacker
		res=inf;
		if(!(yl <= y && y <= yr)){
			res = Work(1, x + 1, y, m + 1, 0) + cost[x + 1][y];
		}
		{		
			if(yr + 1 <= m)
				res = min(res, Work(1, x, yr + 1, yl, yr) + sum[x][yr + 1] - sum[x][y]);
			if(yl - 1 >= 1)
				res = min(res, Work(1, x, yl - 1, yl, yr) + sum[x][y - 1] - sum[x][yl - 2]);
			return res;
		}
	}
	return res;
}

struct WallGameDiv1{
	int play(vector<string> costs){
		n = costs.size();
		m = costs[0].size();
		REP(i, 1, n) REP(j, 1, m){
			cost[i][j] = costs[i - 1][j - 1] - 48;
			sum[i][j] = sum[i][j - 1] + cost[i][j];
		}
		if(m == 1){
			int ans = 0;
			REP(i, 1, n) ans += cost[i][1];
			return ans;
		}
		memset(dp, -1, sizeof dp);
		int ans = 1e8;
		REP(i, 1, m){
			ans = min(ans, cost[1][i] + Work(1, 1, i, m + 1, 0));
		}
		return ans;
	}
}s;