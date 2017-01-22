
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
  
  
class EllysRoomAssignmentsDiv1  
{  
        public:  
        double getAverage(vector <string> R)  
        {  
        	int num = 0;
        	vector<int> a;
        	VEP(i, R) VEP(j, R[i])
        		if (R[i][j] == ' ') a.PB(num), num = 0;
        		else num = num * 10 + R[i][j] - '0';
        	a.PB(num);
        	int t = a[0];
        	
        	sort(a.begin(), a.end()), reverse(a.begin(), a.end());
        	int n = a.size(), m = (n - 1) / 20 + 1;
        	num = n / m;
        	int sum = 0;
        	FOR(i, num) if (t > a[i * m] || t < a[i * m + m - 1]) FOR(j, m) sum += a[i * m + j];
       		//判断当前一层是否是Elly所在的一层，分情况讨论。 
			
			int sum2 = 0;
			//elly在最后一层而且不满的情况 
			if (n % m && t <= a[num * m]) return ((double)sum / m + t) / (num + 1);
			REP(i, n / m * m, n - 1) sum2 += a[i];
			
			double ans1 = ((double)sum / m + t) / num;//elly所在房间人数有num个 
			double ans2 = (n % m ? ((double)sum / m + (double)sum2 / (n % m) + t) / (num + 1) : 0);//elly房间人数有(num+1)个 
        	return (ans1 * (m - n % m) + ans2 * (n % m)) / m;	
        }  
        

};  

