
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

const int N = 50 + 5, M = 550000 + 5;
int n, m, l, b[N], total, cnt[M], nxt[M][10], tot;
string ans, a[N], data[M];


//使用meet in the middle算法，分别对前一半后一半的状态进行搜索。然后计算答案 
int calc(string a, string b){
	int ans = 0;
	VEP(i, a) if (a[i] == b[i]) ++ans;
	return ans;
}
void insert(string num){
	int p = 1;
	FOR(i, n){
		int c = calc(num, a[i].substr(0, l));
		if (!nxt[p][c]) nxt[p][c] = ++tot;
		p = nxt[p][c];
	}
	data[p] = num, cnt[p]++;
}
void query(string num){
	int p = 1;
	FOR(i, n){
		int c = b[i] - calc(num, a[i].substr(l, m - l));
		if (c < 0){ p = 0; break; } else p = nxt[p][c];
	}
	if (p){
		if (!total) ans = data[p] + num;
		total += cnt[p];
	}
}
void dfs1(int x, string num){
	if (x == l) insert(num);
	else REP(i, '0', '9') dfs1(x + 1, num + char(i));
}
void dfs2(int x, string num){
	if (x == m) query(num);
	else REP(i, '0', '9') dfs2(x + 1, num + char(i));
}
class EllysBulls  
{  
        public:  
        string getNumber(vector <string> ga, vector <int> gb)  
        {  
        	MEM(nxt, 0), MEM(cnt, 0), tot = 0;
        	n = ga.size(), m = ga[0].size(), l = m / 2;
        	FOR(i, n) a[i] = ga[i];
        	FOR(i, n) b[i] = gb[i];
			total = 0;
        	dfs1(0, ""), dfs2(l, "");
			if (total >= 2) return "Ambiguity";
			else if (total == 0) return "Liar";
		 	  	 else return ans;
        }  
        
};  

