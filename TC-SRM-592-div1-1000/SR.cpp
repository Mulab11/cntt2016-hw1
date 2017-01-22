
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
typedef complex<double> cp;
const int inf = 0x7fffffff;
const int MOD = 1000000007;
const double pi = acos(-1);

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
int n, a[N], b[N];
cp A[N], B[N], tmp[N], w[N];
inline bool compare(vector<int> A, vector<int> B){
	VEP(i, A){
		if (A[i] < B[i]) return 1;
		if (A[i] > B[i]) return 0;
	}
	return 0;	
}
void DFT(cp A[], int f){
	FOR(i, n){
		cp x = 1; tmp[i] = 0;
		REP(j, 0, n) tmp[i] += x * A[j], x *= w[f == 1 ? i : n - i]; 
	}
	FOR(i, n) A[i] = f == 1 ? tmp[i] : tmp[i] / (double)n;
}
inline vector<int> work(){
	vector<int> bad;
	bad.PB(-1);
	FOR(i, n) if (a[i] != a[(n - i) % n]) return bad;
	REP(i, 0, n) w[i] = cp(cos(2 * pi / n * i), sin(2 * pi / n * i));
	FOR(i, n) A[i] = a[i];
	DFT(A, 1);
	FOR(i, n) A[i] = sqrt(A[i]);
	
	vector<int> ans;
	int m = n / 2 + 1;
	FOR(now, 1 << m){
		int ok = 1;
		
		FOR(i, n) 
			if (i < m) B[i] = now >> i & 1 ? A[i] : -A[i];
			else B[i] = now >> (n - i) & 1 ? A[i] : -A[i];
		DFT(B, -1);
		FOR(i, n) b[i] = int(B[i].real() + 0.5);
		//由于原来的数组是整数，所以我们要倒过来验算一遍。 
		FOR(i, n) if (b[i] != b[(n - i) % n]) {ok = 0; break;}
		FOR(i, n){
			int sum = 0;
			FOR(j, n) sum = sum + b[j] * b[(i - j + n) % n];
			if (sum != a[i]) { ok = 0; break; }
		}
		
		if (ok && (!ans.size() || compare(vector<int>(b, b + n), ans))) ans = vector<int>(b, b + n);
	}
	return ans.size() ? ans : bad;
}
class SplittingFoxes2  
{  
        public:  
        vector <int> getPattern(vector <int> amount)  
        {  
        	//考虑dft，由于是循环的我们只要枚举一半就行了。 
        	n = amount.size();
			FOR(i, n) a[i] = amount[i];
			return work(); 
        }  
 
};  

