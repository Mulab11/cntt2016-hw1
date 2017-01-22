
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
  
  
class TheNumberGame  
{  
        public:  
        bool pack(int A, int B, int T){
        	if (A % T == B) return 1;
        	if (A < B) return 0;
        	return pack(A / 10, B, T);
		}
        string determineOutcome(int A, int B)  
        {  
        	//结论：只要B或者B的翻转（记为B'）A的一个子串，那么Manao赢，否则Manao输 
        	int C = 0, T = 1, tmp = B;
        	while (tmp) C = C * 10 + tmp % 10, tmp /= 10, T *= 10;
        	return pack(A, B, T) || pack(A, C, T) ? "Manao wins" : "Manao loses";
        }  

  
};  

