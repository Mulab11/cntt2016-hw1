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
const	int P=1e9+9;
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

int n, ans;
struct UnknownTree{
	
	int work(VI A){
		int res = 1;
		for(auto u : A){
			assert(u > 0);
			int ans = 1;
			for(auto v : A) if(v < u) ans ++;
			res = 1LL * res * ans % P;
		}
		return res;
	}
	
	int work2(VPI A){
		int m = A.size();
		sort(A.begin(), A.end());
		if(m > 1 && A[0].fi == A[1].fi) return 0;
		int x = 0;
		while(A[x].se != 0) ++x;
		if(x == 0){
			VI Ans;
			FOR(i, 1, m){
				if(A[i].fi - A[0].fi != A[i].se) return 0;
				Ans.pb(A[i].fi);
			}
			return work(Ans);
		}
		
		VPI Ax;
		VI B;
		
		FOR(i, 1, m){
			int x = A[i].se - A[0].se;
			int y = A[i].fi - A[0].fi;
			if(x == y){
				B.pb(A[i].fi);
			}else{
				if(x + y < 0) return 0;
				Ax.pb(A[i]);
			}
		}
		
		return 1LL * work(B) * work2(Ax) % P;
	}
	
	void work(VI A, VI B, VI C){
		set<PII> st;
		FOR(i, 0, n){
			int u = 0, v = 0;
			u = B[i] - A[i];
			v = C[i] - B[i];
			if(u > 0 && v > 0) st.insert(mk(u, v));
			u = A[i] + B[i];
			v = C[i] - B[i];
			if(u > 0 && v > 0) st.insert(mk(u, v));
			u = A[i] - B[i];
			v = C[i] - B[i];
			if(u > 0 && v > 0) st.insert(mk(u, v));
			u = A[i] - B[i];
			v = B[i] + C[i];
			if(u > 0 && v > 0) st.insert(mk(u, v));
			u = A[i] - B[i];
			v = B[i] - C[i];
			if(u > 0 && v > 0) st.insert(mk(u, v));
		}
		
		for(auto ele : st){
			int ab = ele.fi;
			int bc = ele.se;
			VPI AB, BC;
			VI Bx;
			AB.pb(mk(0, ab));
			AB.pb(mk(ab, 0));
			BC.pb(mk(0, bc));
			BC.pb(mk(bc, 0));
			int ok = 1;
			FOR(i, 0, n){
				int u = C[i] - bc;
				int v = A[i] - ab;
				int w = B[i];
				if(u == w && v == w){
					Bx.pb(w);
				}else
				if(v == w){
					BC.pb(mk(B[i], C[i]));
				}else
				if(u == w){
					AB.pb(mk(B[i], A[i]));
				}else{
					ok = 0;
					break;
				}
			}
			if(ok){
				int res = 1;
				res = 1LL * res * work2(AB) % P;
				res = 1LL * res * work2(BC) % P;
				res = 1LL * res * work(Bx) % P;
				renew(ans, res);
			}
		}
	}
	
	void workY(VI A, VI B, VI C){
		FOR(i, 0, n){
			VPI AO, BO, CO;
			VI O;
			AO.pb(mk(0, A[i]));
			AO.pb(mk(A[i], 0));
			BO.pb(mk(0, B[i]));
			BO.pb(mk(B[i], 0));
			CO.pb(mk(C[i], 0));
			CO.pb(mk(0, C[i]));
			int ok = 1;
			FOR(j, 0, n) if(i != j){
				int u = A[j] - A[i];
				int v = B[j] - B[i];
				int w = C[j] - C[i];
				if(u > 0 && u == v && u == w){
					O.pb(u);
				}else
				if(u > 0 && u == w){
					BO.pb(mk(u, B[j]));
				}else
				if(v > 0 && v == w){
					AO.pb(mk(v, A[j]));
				}else
				if(v > 0 && u == v){
					CO.pb(mk(v, C[j]));
				}else{
					ok = 0;
					break;
				}
			}
			if(ok){
				int res = 1;
				res = 1LL * res * work2(AO) % P;
				res = 1LL * res * work2(BO) % P;
				res = 1LL * res * work2(CO) % P;
				res = 1LL * res * work(O) % P;
				renew(ans, res);
			}
		}
	}
	
	int getCount(VI A, VI B, VI C){
		n = A.size();
		work(A, B, C);
		work(A, C, B);
		work(C, A, B);
		workY(A, B, C);
		return ans;
	}
}stu;