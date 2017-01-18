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

#include <sstream>
db sum;
int s[N], R, X, tot, x, SS = 20;
struct EllysRoomAssignmentsDiv1{
	db getAverage(vector<string> ratings){
		string tt;
		for(auto v : ratings) tt += v;
		stringstream iss(tt);
		while(iss >> x) s[++tot] = x;
		X = s[1];
		sort(s + 1, s + tot + 1);
		reverse(s + 1, s + tot + 1);
		R = (tot + SS - 1) / SS;
		int rst = tot % R;
		if(!rst){
			for(int i = 1; i <= tot; i += R){
				int flag = 0;
				REP(j, i, i + R - 1) if(s[j] == X) flag = 1;
				if(!flag){
					REP(j, i, i + R - 1) sum += s[j];
				}
			}
			int k = tot / R;
			return (X + sum / R) / k;
		}else{
			for(int i = 1; i <= tot; i += R){
				if(i + R - 1 >= tot){
					int flag = 0;
					REP(j, i, tot)if(s[j] == X) flag = 1;
					if(flag){
						int k = tot / R;
						return (1.0 * X + sum / R) / (k + 1);
					}else{
						int k = tot / R;
						db ans = 0;
						REP(j, i, tot){
							ans += (1.0 * X / R + 1.0 * s[j] / R + sum / R / R) / (k + 1);
						}
						ans += (1.0 * X / R + sum / R / R) / k * (R - rst);
						return ans;
					}
				}
				int flag = 0;
				REP(j, i, i + R - 1) if(s[j] == X) flag = 1;
				if(!flag){
					REP(j, i, i + R - 1) sum += s[j];
				}
			}
		}
		return -1;
	}
}s2;