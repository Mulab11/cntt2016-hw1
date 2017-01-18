#include <set>
#include <map>
#include <cmath>
#include <ctime>
#include <vector>
#include <bitset>
#include <cstdio>
#include <string>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>
#define REP(i,x,y)  for(int i=(int)x;i<=(int)y;i++)
#define FOR(i,x,y)  for(int i=(int)x;i< (int)y;i++)
#define PER(i,x,y)  for(int i=(int)x;i>=(int)y;i--)
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define md ((L+R)/2)
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int,int> PII;
const	int P=1e9+7;
const	int inf=1e9;
const	ll Inf=1e16;
const	int N=500005;
const	int M=1<<16;

inline int IN(){
	char ch=getchar();int x=0,f=0;
	for(;ch<48||ch>57;ch=getchar()) f=ch=='-';
	for(;ch>=48&&ch<=57;ch=getchar()) x=(x<<1)+(x<<3)+ch-48;
	return f?(-x):x;
}

int Pow(int x,int y,int p){
	int a=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) a=(ll)a*x%p;
	return a;
}

int ans, w;

int onestp(int n, int x){
	if(x == 1){
		if(n <= w) return 1;
		if(w == 1) return 1;
	}
	if(x == n){
		if((n - 1) % w == 0) return 1;
		if(n <= w) return 1;	
	}
	if(x == w){
		if(n < 2 * w) return 1;
	}
	return 0;
}

void dfs(int stp, int n, int x){
	if(stp + 0 >= ans) return;
	if(n == 1){
		ans = stp;
		return;
	}
	if(stp + 1 >= ans) return;
	if(onestp(n, x)){
		ans = stp + 1;
		return;
	}
	if(stp + 2 >= ans) return;
	
	int ux = (x - 1) / w + 1, vx = (x - 1) % w + 1, un = (n - 1) / w + 1, vn = (n - 1) % w + 1;
	FOR(i, 1, ux) REP(j, 1, w) dfs(stp + 1, n - i * j, x - i * j);
	dfs(stp + 1, ux * w, x);
	REP(i, un - ux + 1, un) FOR(j, 1, vx)
		dfs(stp + 1, n - ((i - 1) * j + min(vn, j)), x - (i - (un - ux)) * j);
	
	REP(i, un - ux + 1, un) REP(j, 1, w - vx){
		dfs(stp + 1, n - ((i - 1) * j + min(j, max(0, vn - vx))), x - (i - (un - ux + 1)) * j);
	}
}

struct FoxAndAvatar{
	int minimalSteps(int nn, int width, int rest){
		int n, x;
		n = nn;
		x = rest;
		w = width;
		ans = 4;
		dfs(0, n, x);
		return ans;
	}
}stu;