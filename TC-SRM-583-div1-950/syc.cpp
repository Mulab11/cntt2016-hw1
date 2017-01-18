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
const	int N = 155;
const	int inf = 1e9;
const	LL Inf = 1e15;
const	int P = 1e9 + 7;

int n, m, pr[N][N], npr[N][N], sm;
db f[25][1550][2];int sum[N];

#define Contain(S, x) (((S) >> (x)) & 1)
struct RandomPaintingOnABoard{
	int cnt(int x){
		return __builtin_popcount(x);
	}
	db work(){
		db ans = 0;
		FOR(bid, 0, 1 << m){
			memset(f, 0, sizeof f);
			f[0][0][cnt(bid)&1] = 1;
			REP(i, 1, n){
				sum[i] = 0;
				REP(j, 1, m) if(!Contain(bid, j - 1)) sum[i] += pr[i][j];
			}
			REP(i, 1, n){
				REP(j, 0, sm){
					REP(k, 0, 1){
						f[i][j][k ^ 1] += f[i - 1][j][k];
						if(j >= sum[i]){
							f[i][j][k] += f[i - 1][j - sum[i]][k];
						}
					}
				}
			}
			
			FOR(x, 0, sm) ans += (f[n][x][1] - f[n][x][0]) * sm / (sm - x);			
		}
		return ans;
	}
	db expectedSteps(vector<string> prob){
		n = prob.size();
		m = prob[0].size();
		REP(i, 1, n) REP(j, 1, m) npr[i][j] = prob[i - 1][j - 1] - 48;
		if(n > m){
			REP(i, 1, n) REP(j, 1, m){
				sm += (pr[i][j] = npr[i][j]);
			}
		}else{
			swap(n, m);
			REP(i, 1, n) REP(j, 1, m){
				sm += (pr[i][j] = npr[j][i]);
			}
		}
		
		return work();
	}
} stu;