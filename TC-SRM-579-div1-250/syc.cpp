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

int calc(string x, string y, int flag){
	//计算x->y的最小步数,flag=1表示强制x是y的前缀.
	if(x == "") return y.length();
	int lcp = 0;
	FOR(i, 0, 1000){
		if(i >= x.length()){
			lcp = x.length();
			break;
		}
		if(i >= y.length()){
			lcp = y.length();
			break;
		}
		if(x[i] != y[i]){
			lcp = i;
			break;
		}
	}
	if(lcp == x.length()) return y.length() - lcp;
	if(flag) return inf;
	return y.length() - lcp;
}

struct UndoHistory{
	int minPresses(vector<string> history){
		/*
		1.使用操作3。那么一定会撤销到先前出现过的最长前缀，然后一直使用操作1。
		2.不使用操作3。那么一定是从上一个字符串一直使用操作1。(此时要求上一个字符串是这个字符串的前缀)
		直接模拟即可.
		*/
		int ans = history.size() + history[0].length();
		FOR(i, 1, history.size()){
			//要么直接从当前串转移到这个串
			int now = calc(history[i - 1], history[i], 1);
			//要么将当前串变成某个历史版本,然后从这个历史版本转移.
			FOR(j, 0, i) now = min(now, 2 + calc(history[j], history[i], 0));
			ans += now;
		}
		return ans;
	}
}s;