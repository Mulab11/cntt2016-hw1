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
const	int N=305;

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
struct io{
	stringstream iss;
	void init(string s){
		iss.clear();
		iss << s;
	}
	void init(vector<string> V){
		string t;
		for(auto v : V) t += v;
		init(t);
	}
	int read(){
		int x;
		if(!(iss >> x)) return -1;
		return x;
	}
}A;

int m;
int lef[N], rig[N], DP[N][N];
multiset<int> st;

struct WolfInZooDivOne{
	int count(int n, vector<string> L, vector<string> R){
		A.init(L);
		while(1){
			int x = A.read();
			if(x < 0) break;
			lef[++m] = x + 1;
		}
		A.init(R);
		m = 0;
		while(1){
			int x = A.read();
			if(x < 0) break;
			rig[++m] = x + 1;
		}
		
		
		st.insert(n);
		REP(i, 1, m) st.insert(lef[i]);
		int ans = 1;
		REP(i, 1, n){
			int v =  *st.begin();
			DP[i][0] = 1;
			REP(j, 1, v - 1) renew(DP[i][j], DP[j][j - 1]);
			REP(j, v, i - 1) renew(DP[i][j], DP[j][v - 1]);
			REP(j, 1, i - 1) renew(DP[i][j], DP[i][j - 1]);
			renew(ans, DP[i][i - 1]);
			REP(j, 1, m) if(rig[j] == i) st.erase(st.find(lef[j]));
		}
		return ans;
	}
}stu;