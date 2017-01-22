
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
vector <int> A, B;
vector<long long> C;
LL L[N], R[N];
class SpaceWarDiv1  
{  
        public:  
        bool judge(LL x){
        	int n = A.size(), m = B.size();
        	FOR(i, n) L[i] = x;
        	FOR(i, m) R[i] = C[i];
        	FOR(i, m) while (R[i]){
				int flag = 0; 
				FOR(j, n) if (A[j] >= B[i] && L[j]){//对于每个怪物我们找到目前能大于它战斗力的最小战斗力且有剩余疲劳值的战士与它战斗 
        			LL k = min(L[j], R[i]); L[j] -= k, R[i] -= k; flag = 1; break;
				}
				if (!flag) return 0;
			}
			return 1;
		} 
        long long minimalFatigue(vector <int> A, vector <int> B, vector<long long> C)  
        {  
        	sort(A.begin(), A.end());
        	::A = A, ::B = B, ::C = C;
			LL l = 0, r = 1ll << 60;
			while (l < r){//考虑二分答案 
				LL mid = l + r >> 1;
				if (judge(mid)) r = mid;
				else l = mid + 1;
			}
			return l == (1ll << 60) ? -1 : l;
        }  

};  
   
