#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <bitset>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define REP(i, x, y)   for(int i = (int)(x); i <= (int)(y); i++)
#define FOR(i, x, y)   for(int i = (int)(x); i <  (int)(y); i++)
#define PER(i ,x, y)  for(int i = (int)(x); i >= (int)(y); i--)
#define CH	         ch = getchar()
#define Exit(...)    printf(__VA_ARGS__), exit(0)
#define dln()        fprintf(stderr,"\n")
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
typedef double	  db;
typedef long long LL;
typedef vector<int> VI;
typedef vector<VI > VII;
typedef PR<int,int> PII;
typedef vector<PII> VPI;
const	int inf=2e9;
const	LL Inf=1e10;
const	int P=1e9+7;
const	int N=100005;

inline LL IN(){
	LL x = 0;
	int ch = 0, f = 0;
	for (CH; ch != -1 && (ch < 48 || ch > 57); CH) f = (ch == '-');
	for (; ch >= 48 && ch <= 57; CH) x = (x << 1) + (x << 3) + ch - '0';
	return f ? (-x) : x;
}
template<typename T> inline int chkmin(T &a, const T &b){if(b < a) return a = b, 1; return 0;}
template<typename T> inline int chkmax(T &a, const T &b){if(b > a) return a = b, 1; return 0;}

void renew(int &x, const int &y){
	x += y;
	if(x >= P) x -= P;
	if(x <  0) x += P;
}

int Pow(int x, int y, int p){
	int a = 1;
	for (; y; y >>= 1, x = (LL)x * x %p) if(y & 1) a=(LL)a * x%p;
	return a;
}

VI H;
int n, ID[N];

int cmp(const int &xa, const int &xb){
	if(H[xa] == H[xb]) return xa < xb;
	return H[xa] < H[xb];
}

class TheBrickTowerMediumDivOne{
	public:
		vector<int> find(vector<int> heights){
			H = heights;
			n = heights.size();
			FOR(i, 0, n) ID[i] = i;
			sort(ID, ID + n, cmp);
			VI ans;
			ans.pb(1e9);
			FOR(put, 0, n){
				int lef = put;
				int rig = n - 1 - put;
				VI now;
				now.clear();
				{
					static int use[55];
					memset(use, 0, sizeof use);
					use[ID[0]] = 1;
					PER(req, lef, 1){
						FOR(i, 0, n){
							if(use[i]) continue;
							int cnt = 0;
							FOR(j, 0, n) if(!use[j] && H[j] <= H[i]) ++ cnt;
							if(cnt >= req && (!now.size() || H[i] <= H[now.back()])){
								use[i] = 1;
								now.pb(i);
								break;
							}
						}
					}
					
					now.pb(ID[0]);
					
					PER(req, rig, 1){
						FOR(i, 0, n){
							if(use[i]) continue;
							int cnt = 0;
							FOR(j, 0, n) if(!use[j] && H[j] >= H[i]) ++ cnt;
							if(cnt >= req && H[i] >= H[now.back()]){
								use[i] = 1;
								now.pb(i);
								break;
							}
						}
					}
				}
				
				for(auto v : now) cout << v << " " ; cout << endl;
				ans = min(ans, now);
			}
			return ans;
		}
} cla;