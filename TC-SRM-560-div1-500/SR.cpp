
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
const int inf = 0x7fffffff;
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
  
const int N = 300;
int A[N][N], B[N][N], n;
PI a[N];

int work(int x){
	//模拟倒过去的答案，判断结果是否正确。 
	MEM(A, 0);
	REP(i, 1, n) REP(j, 0, x) REP(k, 0, x) A[a[i].FT + j][a[i].SC + k] = 1;
	REP(i, 1, x){
		MEM(B, 0);
		FOR(i, N - 1) FOR(j, N - 1)
			B[i][j] = A[i][j] && A[i + 1][j] && A[i][j + 1] && A[i + 1][j + 1];
		swap(A, B);
	}
	int tot = 0;
	FOR(i, N) FOR(j, N) tot += A[i][j];
	return tot == n;
}
class DrawingPointsDivOne  
{  
        public:  
        int maxSteps(vector <int> x, vector <int> y)  
        {  
        	n = x.size(); 
        	FOR(i, n) a[i + 1] = MP(x[i] + 70, y[i] + 70);
        	int l = 0, r = 141;
        	//二分答案 
        	while (l < r){
        		int mid = (l + r) >> 1;
        		if (work(mid + 1)) l = mid + 1; else r = mid;
			}
			return (l == 141) ? -1 : l;
        }  
    
};  

