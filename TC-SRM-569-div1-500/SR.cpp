
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
  
  
class TheJediTest  
{  
        public:  
        int minimumSupervisors(vector <int> s, int k)  
        {  
        	//贪心地前移使其凑满K的倍数即可
        	int ans = 0;
			VEP(i, s){
				ans += s[i] / k, s[i] %= k;
				int del = (k - s[i]) % k;
				if (del > 0){ // 如果当前还有剩余，则可以从i+1~i+2中取出来填满。 
					REP(j, i + 1, i + 2) 
						if (j < s.size())
							if (s[j] >= del) {s[j] -= del; break;}
							else del -= s[j], s[j] = 0;
						else break;	
					ans++;
				}
			}
			return ans;
        }  
 
};  

