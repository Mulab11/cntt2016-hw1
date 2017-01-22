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
  
const int N = 50 + 5;
string f[N][N][3][3];
char A[N], B[N];

class LeftRightDigitsGame2  
{  
        public:  
        
        void cmin(string &a, string b){ 
			if (a == "") a = b;
			if (b != "") a = min(a, b);
		}
        //状态中 0表示小于 1表示相等 2表示大于 
        int cop(int x, int y){ if (x < y) return 0; if (x == y) return 1; return 2; }//比较函数 
        string plus(string a, string b){ if (a == "" || b == "") return ""; return a + b; }
        string calc(int l, int r, int p, int q){
        	int i = r - l + 1;
        	if (l == r) return (p == 2 || p == 1 && (A[i] > B[l] || A[i] == B[l] && q >= 1)) ? string(1, A[i]) : "";
        	if (f[l][r][p][q] != "NEW") return f[l][r][p][q];
        	f[l][r][p][q] = "";
        	//两种转移方式 
        	cmin(f[l][r][p][q], plus(string(1, A[i]), calc(l + 1, r, p == 1 ? cop(A[i], B[l]) : p, q)));
        	cmin(f[l][r][p][q], plus(calc(l, r - 1, p, cop(A[i], B[r]) == 1 ? q : cop(A[i], B[r])), string(1, A[i])));
        	return f[l][r][p][q];
		}
        string minNumber(string digits, string lowerBound)  
        {  
        	int n = digits.size();
        	REP(i, 1, n) A[i] = digits[i - 1];
        	REP(i, 1, n) B[i] = lowerBound[i - 1];
        	REP(i, 1, n) REP(j, 1, n) FOR(k, 3) FOR(l, 3) f[i][j][k][l] = "NEW";//初值 
        	return calc(1, n, 1, 1);
        }  
};  

