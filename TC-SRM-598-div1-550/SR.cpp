
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
  
  
class FoxAndFencing  
{  
        public:  
        string WhoCanWin(int mov1, int mov2, int rng1, int rng2, int d)  
        {  
        	if (mov1 + rng1 >= d) return "Ciel"; //ciel一步获胜。 
        	if (mov1 + rng1 > mov2 + rng2) 
        		if (mov1 > mov2 && rng2 + mov2 + 1 + mov2 <= rng1 + mov1) return "Ciel";// 可以追赶，而且追赶途中不会被反杀。
				else return "Draw";
			else 
			if (mov1 + rng1 < mov2 + rng2)
				if (mov1 + d <= mov2 + rng2) return "Liss";//Liss一步获胜。 	
				else if (mov2 > mov1 && rng1 + mov1 + 1 + mov1 <= rng2 + mov2) return "Liss";// 可以追赶，而且追赶途中不会被反杀。
				 	 else return "Draw"; 
			return "Draw";	 	 
        }

};  

