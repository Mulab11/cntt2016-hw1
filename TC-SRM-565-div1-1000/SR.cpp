
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
const int MOD = 1000000009;

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
int n, a[N], b[N], c[N];
class UnknownTree  
{  
        public:  
        //问题转化为得到中间点到三个关键点的距离，然后球方案。 
        int work(int a[], int b[], int c[], int da, int db, int dc){ 
        	if (da <= 0 || db <= 0 || dc < 0) return 0;
        	map<PI, vector<int> > pos;
        	FOR(i, n){
        		LL x = 0;
        		int y = 0, d = 0, flag = 0;
        		//看是否在三个臂上, 在中心点的下方的话，可以算在合法的两个臂上的任意一个。 
        		if (a[i] - b[i] == da - db) x = (LL)dc + da + c[i] - a[i], y = c[i], d = dc, flag = -1; else
        		if (b[i] - c[i] == db - dc) x = (LL)da + db + a[i] - b[i], y = a[i], d = da, flag = 0; else
				if (c[i] - a[i] == dc - da) x = (LL)db + dc + b[i] - c[i], y = b[i], d = db, flag = 1; else
				return 0;
				if (x < 0 || x > d * 2 || x & 1) return 0;
				x /= 2, y -= x;
				pos[MP(x, flag)].PB(y);
			}
			int ans = 1;
			for (map<PI, vector<int> > :: iterator it = pos.begin(); it != pos.end(); ++it){
				vector<int> &tmp = it -> SC;
				sort(tmp.begin(), tmp.end());
				if (it -> FT.FT && (tmp[0] || (tmp.size() > 1 && tmp[1] == 0))) return 0;
				int j = 0;
				REP(i, 1, tmp.size() - 1){
					if (tmp[i - 1] < tmp[i]) j = i - (tmp[0] == 0);
					ans = (LL)ans * (j + 1) % MOD;//不同分叉的情况相乘。 
				}
			}
			return ans;
		}
        int Tree(int a[], int b[], int c[]){ // 三叉情况 
        	pair<LL, int> ctr((LL)inf * inf, inf);
    		FOR(i, n) cmin(ctr, MP((LL)a[i] + b[i] + c[i], i));
    		swap(a[0], a[ctr.SC]), swap(b[0], b[ctr.SC]), swap(c[0], c[ctr.SC]);
    		return work(a, b, c, a[0], b[0], c[0]);
		}
    	int Line(int a[], int b[], int c[]){ // 一条链情况 
    		PI ctr(inf, inf);
    		FOR(i, n) cmin(ctr, MP(c[i], i));
    		swap(a[0], a[ctr.SC]), swap(b[0], b[ctr.SC]), swap(c[0], c[ctr.SC]);
    		return ((LL)work(a, b, c, a[0] - c[0], b[0] - c[0], 0) + 
						work(a, b, c, a[0] + c[0], b[0] - c[0], 0) +
						work(a, b, c, a[0] - c[0], b[0] + c[0], 0) +
						work(a, b, c, c[0] - a[0], b[0] - c[0], 0) + 
						work(a, b, c, a[0] - c[0], c[0] - b[0], 0)) % MOD;
		}
        int getCount(vector <int> A, vector <int> B, vector <int> C)  
        {  
        	n = A.size();
        	FOR(i, n) a[i] = A[i], b[i] = B[i], c[i] = C[i];
        	return ((LL)Line(a, b, c) + Line(b, c, a) + Line(c, a, b) + Tree(a, b, c)) % MOD;
        }  
   
};  

