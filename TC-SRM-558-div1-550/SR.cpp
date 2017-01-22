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

template <typename tn> inline void cmax(tn &a, tn b){ if (a < b) a = b; }
template <typename tn> inline void cmin(tn &a, tn b){ if (a > b) a = b; }
  
const int N = 300 + 5;  
struct Pt{ int x, y; }A[N], B[N];
int tmp[N], tmp1[N], tmp2[N], D[10000 + 5];

inline Pt operator - (const Pt &a, const Pt &b){ return (Pt){a.x - b.x, a.y - b.y};}
inline int operator * (const Pt &a, const Pt &b){ return a.x * b.y - a.y * b.x; }
void get(vector<string> a, int b[], int &n){
	b[n = 1] = 0;
	VEP(i, a) VEP(j, a[i])
		if (a[i][j] == ' ') { b[++n] = 0; }
		else b[n] = b[n] * 10 + a[i][j] - '0';
}
class Ear  
{  
        public:  
        long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY)  
        {  
        	int n, m;
        	get(redX, tmp, n), get(blueX, tmp1, m), get(blueY, tmp2, m);
        	REP(i, 1, n) A[i].x = tmp[i], A[i].y = 0;
        	REP(i, 1, m) B[i].x = tmp1[i], B[i].y = tmp2[i];
        	LL ans = 0;
        	MEM(D, 0);
        	REP(i, 1, n) D[A[i].x]++;
			REP(i, 1, 10000) D[i] += D[i - 1];
			//Ã¶¾Ù P Q 
        	REP(i, 1, m) REP(j, 1, m) if (B[j].y < B[i].y){ 
        		int L = 0, R = 0;
        		//¼ÆËã A B 
        		REP(k, 1, n) if ((B[j] - B[i]) * (A[k] - B[i]) < 0 && A[k].x < B[i].x && A[k].x < B[j].x)
        			L += D[B[j].x - 1] - D[A[k].x];
        		//¼ÆËã C D	
        		REP(k, 1, n) if ((B[j] - B[i]) * (A[k] - B[i]) > 0 && A[k].x > B[i].x && A[k].x > B[j].x)	
        			R += D[A[k].x - 1] - D[B[j].x];
        		ans += (LL)L * R;	
			}
			return ans;
        }  
};  
