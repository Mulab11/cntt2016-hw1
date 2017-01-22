
#line 7 "FoxAndChess.cpp"  

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
  
  
class FoxAndChess  
{  
        public:  
        string ableToMove(string A, string B)  
        {  
        	//将所有对应位置取出，然后必然是一一匹配，然后看位置关系即可。 
        	vector<PI> a, b;
        	VEP(i, A){
				if (A[i] == 'L') a.PB(MP(0, i));
				if (A[i] == 'R') a.PB(MP(1, i));
			}
			VEP(i, B){
				if (B[i] == 'L') b.PB(MP(0, i));
				if (B[i] == 'R') b.PB(MP(1, i));
			}
			if (a.size() != b.size()) return "Impossible";
			VEP(i, a){
				if (a[i].FT != b[i].FT) return "Impossible";
				if (a[i].FT == 1  && a[i].SC > b[i].SC) return "Impossible";
				if (a[i].FT == 0  && a[i].SC < b[i].SC) return "Impossible";
			}
			return "Possible";
        }  
 
};  

