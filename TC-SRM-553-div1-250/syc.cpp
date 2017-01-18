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

struct node{
	LL x, y;
	node operator +(const node &a)const{
		return (node){x + a.x, y + a.y};
	}
}stk[N];
int top;
LL V[N], Top;

struct Suminator{	
	int findMissing(VI SS, int wanted){
		top = 0;
		for(auto v : SS){
			node now;
			if(v == -1){
				now.x = 1;
				now.y = 0;
				stk[++top] = now;
				
				LL x, y;
				if(!Top) x = 0; else{
					x = V[Top];
					Top--;
				}
				if(!Top) y = 0; else{
					y = V[Top];
					Top--;
				}
				V[++Top] = x + y;
			}else
			if(v != 0){
				now.x = 0;
				now.y = v;
				stk[++top] = now;
				
				V[++Top] = v;
			}else
			if(v == 0){
				node x, y;
				if(!top) x.x = x.y = 0; else{
					x = stk[top];
					top --;
				}
				if(!top) y.x = y.y = 0; else{
					y = stk[top];
					top --;
				}
				stk[++top] = x + y;
				
				
				LL X, Y;
				if(!Top) X = 0; else{
					X = V[Top];
					Top--;
				}
				if(!Top) Y = 0; else{
					Y = V[Top];
					Top--;
				}
				V[++Top] = X + Y;
			}
		}
		
		if(V[Top] == wanted) return 0;
		if(!stk[top].x){
			if(stk[top].y == wanted) return 1;
			return -1;
		}
		LL P = wanted - stk[top].y;
		if(P <= 0) return -1;
		if(P % stk[top].x) return -1;
		return P / stk[top].x;
	}
} stu;