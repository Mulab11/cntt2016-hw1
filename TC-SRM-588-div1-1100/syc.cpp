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
const	int N=2555;

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

int W, H, cnt;
int ID[N][N];
VI adj[N];
int Ace, Bob, dA, dB, flag;
vector<string> field;
struct GameInDarknessDiv1{
	int getid(int x, int y){
		if(x < 0 || x >= W || y < 0 || y >= H || field[x][y] == '#') return 0;
		return ID[x][y];
	}
	void add(int x, int y){
		if(!x || !y) return;
		adj[x].pb(y);
	}
	void dfs(int x, int pre, int dis){
		if(x == Ace) dA = dis;
		if(x == Bob) dB = dis;
		if(dis >= 3) flag = 1;
		for(auto v : adj[x]) if(v != pre) dfs(v, x, dis + 1);
	}
	string Main(){
		REP(i, 1, cnt){
			dA = dB = 0;
			int cnt = 0;
			for(auto v : adj[i]){
				flag = 0;
				dfs(v, i, 1);
				cnt += flag;
			}
			if(dA - dB >= 2 && cnt >= 3) return "Bob wins";
		}
		return "Alice wins";
	}
	string check(vector<string> field){
		W = field.size();
		H = field[0].size();
		::field = field;
		FOR(i, 0, W) FOR(j, 0, H) if(field[i][j] != '#') ID[i][j] = ++cnt;
		FOR(i, 0, W) FOR(j, 0, H){
			int u = getid(i, j);
			add(u, getid(i - 1, j));
			add(u, getid(i + 1, j));
			add(u, getid(i, j - 1));
			add(u, getid(i, j + 1));
		}
		
		FOR(i, 0, W) FOR(j, 0, H){
			if(field[i][j] == 'A') Ace = getid(i, j);
			if(field[i][j] == 'B') Bob = getid(i, j);
		}
		
		return Main();
	}
}s;