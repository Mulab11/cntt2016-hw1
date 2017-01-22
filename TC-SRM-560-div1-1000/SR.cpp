
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
  
const int N = 14 + 5;
int a[N][N], pw[N];
double b[N], x[N];

class BoundedOptimization  
{  
        public:  
        double maxValue(vector <string> expr, vector <int> lb, vector <int> ub, int S)  
        {  
        	MEM(a, 0);
        	int l = 0, r = 0;
        	VEP(i, expr) VEP(j, expr[i])
        		if (expr[i][j] == '+') a[l][r] = a[r][l] = 1;
        		else l = r, r = expr[i][j] - 'a';
        	a[l][r] = a[r][l] = 1;
        	
			int n = lb.size();
			pw[0] = 1;
			REP(i, 1, n) pw[i] = pw[i - 1] * 3;
			
			double ans = 0;
			//3^n次方枚举，0表示其他值，1表示取最小值，2表示取最大值 
        	FOR(now, pw[n]){
        		vector<int> cur;
        		MEM(b, 0), MEM(x, 0);
        		FOR(i, n)
					if (now / pw[i] % 3 == 0) cur.PB(i); 
					else{
						x[i] = (now / pw[i] % 3 == 1 ? lb[i] : ub[i]);
						FOR(j, n) if (a[i][j]) b[j] += x[i];
					}
					
				//由于如果存在两个其他值之间系数为0，那么不难发现其中一个的答案可以取到最值，所以这是我们不需要考虑的
				//于是判断之间有系数为0的则直接跳过不做。 
				int flag = 1;
				VEP(i, cur)	VEP(j, cur) if (i != j && a[cur[i]][cur[j]] == 0) flag = 0;
				
				if (flag){
					double s = S;
					FOR(i, n) s -= x[i];
					
					//在所有其他值之间，我们不难通过计算可以搞出所有对应取值。 
					if (cur.size()){
						VEP(i, cur) s -= b[cur[i]] - b[cur[0]];
						s /= cur.size();
						VEP(i, cur) x[cur[i]] = s + b[cur[i]] - b[cur[0]];
					}
					
					//判断取值是否合法，然后更新答案。 
					double tot = 0;
					int flag = 1;
					FOR(i, n) tot += x[i];
					FOR(i, n) if (x[i] + 1e-10 < lb[i] || x[i] > ub[i] + 1e-10) flag = 0;
					if (tot <= S + 1e-10 && flag){
						double tmpans = 0;
						FOR(i, n) FOR(j, n) if (i < j && a[i][j]) tmpans += x[i] * x[j];
						cmax(ans, tmpans);
					}	
				}
			}
			return ans;
        }  
   
};  

