
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
  
const int N = 50 + 5;
int cnt[N][26], suv[N], used[N];
class StringGame  
{  
        public:  
        vector <int> getWinningStrings(vector <string> S)  
        {  
        	MEM(cnt, 0);
        	int n = S.size();
        	//不在乎字母排列顺序，在乎各字母的个数 
        	FOR(i, n) VEP(j, S[i]) cnt[i][S[i][j] - 'a']++;
        	vector<int> ans;
        	FOR(i, n){
        		MEM(used, 0);
        		FOR(j, n) suv[j] = 1;
        		//采取贪心，如果当前该字母能取便取（如果同时存在多个字母能取的话不会影响答案） 
        		FOR(num, 26) 
        			FOR(ch, 26) if (!used[ch]){
        				bool flag = 1;
        				FOR(j, n) if (suv[j] && cnt[j][ch] > cnt[i][ch]) flag = 0;
        				if (flag){ FOR(j, n) if (cnt[j][ch] < cnt[i][ch]) suv[j] = 0; used[ch] = 1; break; }
        			}
        		int tmp = 0;	
        		FOR(j, n) tmp += suv[j];
        		if (tmp == 1) ans.PB(i);
			}
			return ans;
        }  

};  

