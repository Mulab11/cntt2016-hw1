#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i, x, y)  for(int i = (int)x; i <= (int)y; i ++)
#define FOR(i, x, y)  for(int i = (int)x; i <  (int)y; i ++)
#define PER(i, x, y)  for(int i = (int)x; i >= (int)y; i --)
#define fi first
#define se second
#define mk make_pair
#define pb push_back
using namespace std;
typedef double db;
typedef long long LL;
typedef pair<int, int> PII;
const	int N = 66;
const	int inf = 1e9;
const	LL Inf = 1e15;
const	int P = 1e9 + 7;

int n, f[N][27][27];
struct StringWeight{
	void renew(int &x, int y){
		if(x > y) x = y;
	}
	int calc(int l, int r){
		return (l + r) * (r - l + 1) / 2;
	}
	int getMinimum(vector<int> L){
		n = L.size();
		memset(f, 0x3f, sizeof f);
		f[0][0][0] = 0;
		int sum = 0;
		REP(i, 1, n){
			int sz = L[i - 1];
			int kd = min(sz, 26);
			REP(j, 0, 26) REP(k, 0, j){
				for(int nw = 0; nw + j <= 26; nw ++)
				for(int ed = 0; ed + nw <= kd && ed + k <= j; ed ++)
				for(int al = 0; al + ed + nw <= kd && nw + j + al <= 26; al ++){
					int usekd = nw + al + j - k;
					if(usekd < kd) continue;
					int prev = f[i - 1][j][k];
					prev += calc(sum, sum + ed - 1) - calc(sum + sz - nw, sum + sz - 1);
					if(j == k || nw + ed + al == kd) prev += sz - nw - ed - al;
					renew(f[i][j + nw + al][k + ed + al], prev);
				}
			}
			sum += sz;
		}
		
		int ans = inf;
		REP(i, 0, 26) renew(ans, f[n][i][i]);
		return ans;
	}
} stu;