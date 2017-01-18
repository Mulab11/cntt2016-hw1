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

stringstream iss;
string insource;
int tmp;
void init(vector<string> X){
	iss.clear();
	insource = "";
	for(auto v : X) insource += v;
	iss << insource;
}

int nx, ny;
struct po{
	LL x, y;
	po operator -(const po &a)const{
		return (po){x - a.x, y - a.y};
	}
	LL operator *(const po &a)const{
		return x * a.y - y * a.x;
	}
}A[N], B[N];

struct CheckerFreeness{
	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY){
		init(whiteX);
		while(iss >> tmp) A[++nx].x = tmp;
		init(whiteY); nx = 0;
		while(iss >> tmp) A[++nx].y = tmp;
		init(blackX);
		while(iss >> tmp) B[++ny].x = tmp;
		init(blackY); ny = 0;
		while(iss >> tmp) B[++ny].y = tmp;
		
		REP(i, 1, nx)
		REP(j, i + 1, nx){
			REP(k, 1, ny) if((B[k] - A[i]) * (A[j] - A[i]) < 0)
			REP(l, 1, ny) if((B[l] - A[i]) * (A[j] - A[i]) > 0){
				if((B[l] - A[i]) * (B[k] - A[i]) > 0 && (B[k] - A[j]) * (B[l] - A[j]) > 0){
					return "NO";
				}
			}
		}
		
		return "YES";
	}
}stu;