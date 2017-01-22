
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
const int inf = 0x3f3f3f3f;
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
  
const int N = 100 + 5;
int a[N], n, m;

class YetAnotherBoardGame  
{  
        public:  
        int work(int last){
        	int now = 0;
        	FOR(i, m) if (last >> i & 1){
        		if (i - 1 >= 0) now ^= 1 << (i - 1); 
        		if (i + 1 <  m) now ^= 1 << (i + 1);
			}
			return now;
		}
        int work(int dep, int last, int down, int A, int B){ 
			//dep表示当前层数，last表示上一层的颜色，down表示上一层对下一层的影响，A表示进行操作一的行，B表示进行操作二的行 
        	if (dep == n)
				if (!last) return 0;
				else return inf;
			int now = down ^ a[dep] ^ work(last), ans = inf, flag;
			flag = 1;
			FOR(i, m) if (last >> i & 1 && B >> i & 1) flag = 0;
			if (flag) cmin(ans, work(dep + 1, now, last, A | last, B));
			flag = 1;
			FOR(i, m) if (last >> i & 1 && A >> i & 1) flag = 0;
			if (flag) cmin(ans, work(dep + 1, now ^ last, last, A, B | last));
			return ans + __builtin_popcount(last);
		}
        int minimumMoves(vector <string> A)  
        {  
        	n = A.size(), m = A[0].size();
        	MEM(a, 0);
        	FOR(i, n) FOR(j, m) a[i] |= (A[i][j] == 'W') << j;
        	int ans = inf;
        	FOR(last, 1 << m){//枚举第一行做那些操作。 
        		int now = work(last) ^ a[0];
				cmin(ans, work(1, now, last, last, 0) + __builtin_popcount(last));
				cmin(ans, work(1, now ^ last, last, 0, last) + __builtin_popcount(last));
			}
			return ans == inf ? -1 : ans;
        }  

};  

