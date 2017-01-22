
#include<bits/stdc++.h>
#define FT first
#define SC second
#define PB push_back
#define MP make_pair
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define PER(i, r, l) for(int i = (r); i >= (l); i--)
#define FOR(i, n) for(int i = 0; i < (n); i++)
#define ROF(i, n) for(int i = (n) - 1; i >= 0; i--)
#define VEP(i, x) for(int i = 0; i < x.size(); i++)
#define RUN(i, x) for(__typeof((x).begin()) i = (x).begin(); i != (x).end(); ++i)
#define DFOR(i, x, y) for(int i = hd[x], y = e[i].to; i; i = e[i].nxt, y = e[i].to)
#define MEM(a, b) memset(a, b, sizeof(a))
#define rint read<int>()
#define rll read<LL>()

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PI;
const int inf = 0x7ffffff;
const int MOD = 1000000007;

template <typename tn>
inline tn read(){
	char ch; tn f = 1;
	while (!isdigit(ch = getchar())) if (ch == '-') f = -1;
	tn x = ch - '0';
	while (isdigit(ch = getchar())) x = x * 10 + ch - '0';
	return x * f;
}
template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  

int dis(int x, int y){
	int z = int(sqrt(x * x + y * y) + 0.5);
	if (x * x + y * y == z * z) return z;
	else return inf;
}
class FindPolygons 
{  
        public:  
        double minimumPolygon(int L)  
        {  
        	//每条边必然是整数
			//然后奇数答案不存在
			//偶数的话必然存在矩形的答案
			//那么只要看是否存在三角形即可 
        	//枚举可能的两个点 
        	vector<PI> A;
        	if (L & 1 || L == 2) return -1;
        	int ans = inf;
			REP(i, 1, L) REP(j, 1, L) if (dis(i, j) <= L){
				A.PB(MP(i, j));
				if (i + j + dis(i, j) == L) cmin(ans, dis(i, j) - min(i, j));
				if (dis(i, j) * 2 + j * 2 == L) cmin(ans, abs(dis(i, j) - j * 2));
			}
			REP(i, 1, (int)A.size() - 1) REP(j, i + 1, (int)A.size() - 1){
				int d1 = dis(A[i].FT, A[i].SC), d2 = dis(A[j].FT, A[j].SC), d3 = dis(A[i].FT - A[j].FT, A[i].SC - A[j].SC);
				if (d1 + d2 + d3 == L && d1 + d2 > d3 && d2 + d3 > d1 && d3 + d1 > d2) cmin(ans, max(d1, max(d2, d3)) - min(d1, min(d2, d3)));
				
				if (A[j].FT == A[i].FT){
					d3 = A[j].SC + A[i].SC;
					if (d1 + d2 + d3 == L) cmin(ans, max(d1, max(d2, d3)) - min(d1, min(d2, d3)));
				}
			}
			return ans == inf ? (L % 4 ? 1 : 0) : ans;
        }  

};  

