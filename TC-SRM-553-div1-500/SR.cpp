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

const int N = 50 + 5;
  
class TwoConvexShapes  
{  
        public:  
        int f[N][N], can[N][N], ans, n, m;
        char a[N][N];
        
        void Non_decreasing(){//由上至下单调不降的情况 
            REP(i, 0, m) f[0][i] = 1;
            REP(i, 1, n) REP(j, 0, m){
                f[i][j] = j ? f[i][j - 1] : 0;
                if (can[i][j]) f[i][j] = (f[i][j] + f[i - 1][j]) % MOD;
            }
            ans = (ans + f[n][m]) % MOD;
        }
        
        void Non_increasing(){//有上至下单调不增的情况
            REP(i, 1, n / 2) REP(j, 0, m) swap(can[i][j], can[n - i + 1][j]);
            Non_decreasing();
            REP(i, 1, n / 2) REP(j, 0, m) swap(can[i][j], can[n - i + 1][j]);
        }
        
        void Exclusion_row(){//考虑每列的数都一样的情况。 
            REP(j, 0, n){
                int flag = 1;
                REP(i, 1, j) if (!can[i][m]) { flag = 0; break; }
                REP(i, j + 1, n) if (!can[i][0]) { flag = 0; break; }
                ans -= flag;
            }
        }
        
        void Exclusion_column(){//考虑每行的数都一样的情况 
            REP(j, 0, m){
                int flag = 1;
                REP(i, 1, n) flag &= can[i][j];
                ans -= flag;
            }
        }
        
        void Exclusion_all(){//所有格子都相同的情况 
            REP(i, 1, n) REP(j, 1, m) if (a[i][j] == 'W') return;
            ++ans;
        }
        
        void UpdateAns(){
            REP(i, 1, n) REP(j, 0, m){
                can[i][j] = 1;
                REP(k, 1, j) if (a[i][k] == 'W') {can[i][j] = 0; break;}
                REP(k, j + 1, m) if (a[i][k] == 'B') {can[i][j] = 0; break;}
            }    
            Non_decreasing();
            Non_increasing();
            Exclusion_row();
            Exclusion_column();
            Exclusion_all();
        }
        
        int countWays(vector <string> grid)  
        {  
            n = grid.size(), m = grid[0].size(), ans = 0;
        
            REP(i, 1, n) REP(j, 1, m) a[i][j] = grid[i - 1][j - 1];
            UpdateAns();
            
            REP(i, 1, n) REP(j, 1, m)
                if (a[i][j] == 'B') a[i][j] = 'W'; else
                if (a[i][j] == 'W') a[i][j] = 'B';
            UpdateAns();
            
            return (ans + MOD) % MOD;
        }  
};  
