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
const	int N=55;

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
int n;
VI D[N];
int f[N][N];
struct History{
	string verifyClaims(vector<string> dynasties, vector<string> battles, vector<string> queries){
		n = dynasties.size();
		FOR(i, 0, n){
			stringstream is(dynasties[i]);
			int x;
			while(is >> x) D[i].pb(x);
		}
		string bat = accumulate(battles.begin(), battles.end(), string("")), in;
		stringstream is(bat);
		memset(f, 0x3f, sizeof f);
		FOR(i, 0, n) f[i][i] = 0;
		while(is >> in){
			int a = in[0] - 'A';
			int b = in[3] - 'A';
			int u = in[1] - '0';
			int v = in[4] - '0';
			
			int l1 = D[a][u], r1 = D[a][u + 1] - 1;
			int l2 = D[b][v], r2 = D[b][v + 1] - 1;
			//A[a] + r1 >= A[b] + l2
			//A[b] - A[a] <= r1 - l2
			chkmin(f[b][a], r1 - l2);
			chkmin(f[a][b], r2 - l1);
		}
		FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n) chkmin(f[i][j], f[i][k] + f[k][j]);
		string res;
		for(auto in : queries){
			int a = in[0] - 'A';
			int b = in[3] - 'A';
			int u = in[1] - '0';
			int v = in[4] - '0';
			
			int l1 = D[a][u], r1 = D[a][u + 1] - 1;
			int l2 = D[b][v], r2 = D[b][v + 1] - 1;
			if(f[a][b] + r1 - l2 >= 0 && f[b][a] + r2 - l1 >= 0){
				res += "Y";
			}else{
				res += "N";
			}
		}
		return res;
	}
}s;