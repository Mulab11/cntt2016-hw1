
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
  
  
class UndoHistory  
{  
        public:  
        int minPresses(vector <string> a)  
        {  
        	int ans = a[0].size() + a.size();
        	REP(i, 1, a.size() - 1){
        		//分别考虑是否使用第三种操作，然后分别计算一下代价即可。 
        		int tmp = inf;
        		if (a[i].size() >= a[i - 1].size() && a[i].substr(0, a[i - 1].size()) == a[i - 1]) cmin(tmp, (int)a[i].size() - (int)a[i - 1].size());
       			int mx = 0;
       			REP(j, 0, i - 1) REP(k, 0, min(a[i].size(), a[j].size()))
       				if (a[i].substr(0, k) == a[j].substr(0, k)) cmax(mx, k);
       			cmin(tmp, (int)a[i].size() - mx + 2);
				ans += tmp;
			}
			return ans;
        }  
        

};  

