#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <set>
#include <iostream>
#include <sstream>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <iterator>
#include <numeric>
#include <list>
#include <complex>
#include <queue>
#include <climits>
 
using namespace std;
 
typedef vector<int> vi;
typedef vector<string> vs;
typedef long long ll;
typedef complex<double> pnt;
typedef pair<int, int> pii;
 
#define RA(x) (x).begin(), (x).end()
#define FE(i, x) for (typeof((x).begin()) i = (x).begin(); i != (x).end(); i++)
#define SZ(x) ((int) (x).size())
 
 
class RockPaperScissors
{
public:
    double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb);
};
 
static double dp[51][51][51], dp2[51][51][51], ex[51][51][51];
 
double RockPaperScissors::bestScore(vector <int> P1, vector <int> P2, vector <int> P3)
{
    int N = P1.size();
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1.0;
    for (int i = 1; i <= N; i++)
    {
        memset(dp2, 0, sizeof(dp2));
        dp2[0][0][0] = 1.0;
        for (int a = 0; a <= i; a++)
            for (int b = 0; a + b <= i; b++)
                for (int c = 0; a + b + c <= i; c++)
                {
                    int r = a + b + c;
                    if (r == 0)
                        continue;
                    dp2[a][b][c] = dp[a][b][c] * (i - r) / i;
                    double scl = r / (i * 300.0);
                    if (a > 0)
                        dp2[a][b][c] += dp[a - 1][b][c] * P1[i - 1] * scl;
                    if (b > 0)
                        dp2[a][b][c] += dp[a][b - 1][c] * P2[i - 1] * scl;
                    if (c > 0)
                        dp2[a][b][c] += dp[a][b][c - 1] * P3[i - 1] * scl;
                }
        memcpy(dp, dp2, sizeof(dp));
    }
 
    memset(ex, 0, sizeof(ex));
    for (int a = N; a >= 0; a--)
        for (int b = N - a; b >= 0; b--)
            for (int c = N - a - b; c >= 0; c--)
            {
                int r = a + b + c;
                if (r == N)
                    ex[a][b][c] = 0.0;
                else
                {
                    double v[3];
                    double f[3];
                    v[0] = dp[a + 1][b][c] * (a + 1) / (r + 1); f[0] = ex[a + 1][b][c];
                    v[1] = dp[a][b + 1][c] * (b + 1) / (r + 1); f[1] = ex[a][b + 1][c];
                    v[2] = dp[a][b][c + 1] * (c + 1) / (r + 1); f[2] = ex[a][b][c + 1];
                    double best = 0.0;
                    for (int s = 0; s < 3; s++) if (v[s] == 0) f[s] = 0.0;
                    for (int s = 0; s < 3; s++) {
                        double e = v[0] * (f[0] + 1.0) + v[1] * f[1] + v[2] * (f[2] + 3.0);
                        best = max(best, e);
                        rotate(v, v + 1, v + 3);
                        rotate(f, f + 1, f + 3);
                    }
                    best /= (v[0] + v[1] + v[2]);
                    ex[a][b][c] = best;
                }
            }
    return ex[0][0][0];
}
 
