
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
int ans[N], cnt[N];
class SurveillanceSystem  
{  
        public:  
        string getContainerInfo(string A, vector <int> B, int L)  
        {  
        	sort(B.begin(), B.end());
        	MEM(ans, 0);
        	VEP(i, B){
        		int j = i, num = 0;
        		while (j < B.size() - 1 && B[j + 1] == B[i]) ++j;//对于相同数量的摄像头放一起考虑 
        		MEM(cnt, 0);
        		FOR(x, A.size() - L + 1){
        			int tmp = 0;
        			FOR(y, L) tmp += A[x + y] == 'X';
        			if (tmp == B[i]) ++cnt[x], --cnt[x + L], ++num;//找出所有合法区间 
				}
				REP(x, 1, A.size()) cnt[x] += cnt[x - 1];//统计每个点包含在几个合法区间内 
				FOR(x, A.size()){
					if (cnt[x] + j - i + 1 > num) cmax(ans[x], 2);
					if (cnt[x]) cmax(ans[x], 1);
				}
        		i = j;
			}
			string fans;
			VEP(i, A) fans.PB(ans[i] == 2 ? '+' : (ans[i] == 1 ? '?' : '-' ));
			return fans;
        }  
        

};  

