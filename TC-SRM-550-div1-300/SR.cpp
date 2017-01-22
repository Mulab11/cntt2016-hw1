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
  
const int dx[4] = {0, -1, 0, 1};
const int dy[4] = {1, 0, -1, 0};
bool a[5000 + 5][5000 + 5];
class RotatingBot  
{  
        public:  
        int minArea(vector <int> moves)  
        {  
        	//假设不一定要碰到边界就可以转向，模拟整个机器人运动的路线，记录经过的点最上端，最左端，最右端，最下端的坐标，从而得到最小矩形的边界。 
        	int x = 2500, y = 2500, Xmx = 2500, Xmn = 2500, Ymx = 2500, Ymn = 2500, fx = 3;
        	MEM(a, 0), a[2500][2500] = 1;//初始点之后也无法经过。 
        	RUN(it, moves){
        		fx = (fx + 1) % 4;//变换方向 
        		REP(i, 1, *it){
        			x += dx[fx], y += dy[fx];
        			if (a[x][y]) return -1;//如果经过了之前经过的点，则返回-1。 
        			a[x][y] = 1, cmin(Xmn, x), cmax(Xmx, x), cmin(Ymn, y), cmax(Ymx, y);//更新极值。 
				}
			}
			//验证是否碰到边界以及之前经过的格子才进行转向。 
			x = 2500, y = 2500, MEM(a, 0), a[2500][2500] = 1, fx = 3;
			moves.pop_back();//最后一次行走可以任意停下，所以不需要判断，可以扔掉。 
			RUN(it, moves){
        		fx = (fx + 1) % 4;
        		REP(i, 1, *it) x += dx[fx], y += dy[fx], a[x][y] = 1;
        		int tx = x + dx[fx], ty = y + dy[fx]; 
        		if (!a[tx][ty] && tx >= Xmn && tx <= Xmx && ty >= Ymn && ty <= Ymx)
        			return -1;//判断是否碰到边界或以前经过的格子 
			}
			return (Xmx - Xmn + 1) * (Ymx - Ymn + 1);
        }  
  
};  
  
