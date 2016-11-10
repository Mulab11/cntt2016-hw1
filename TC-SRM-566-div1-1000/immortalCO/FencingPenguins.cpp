#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 100007;
const int MaxN = 300;
const int MaxM = 60;

struct Point
{
    double x, y;
    Point operator - (const Point& P) const {return (Point) {x - P.x, y - P.y};}
    double operator * (const Point& P) const {return x * P.y - y * P.x;}
    double length() {return sqrt(x * x + y * y);}
} c[MaxN], p[MaxM];

#define Bit(i) (1ll << (i))
int decode(char w) {return w <= 'Z' ? w - 'A' : w - 'a' + 26;}

bool good[MaxN][MaxN];          // 每条边是否合法（没有跨越点集）
ll points_set[MaxN][MaxN];      // 每条边右边的点
ll color_points[MaxM];          // 每种颜色的点集

// 这是一个调试用的函数，能把状态压缩输出为 {a, b, c} 这样的集合
string format(ll set)
{
    string ans = "{";
    for(int i = 0; set; set >>= 1, ++i)
        if(set & 1)
        {
            static char tmp[100];
            sprintf(tmp, "%d,", i);
            ans += tmp;
        }
    if(ans.size() > 1u) ans.back() = '}'; else ans.push_back('}');
    return ans;
}
#define Format(s) format(s).c_str()

int f[MaxN][MaxN];  // 最外面那条边是 (l, r) 的方案数
int s[MaxN][MaxN];  // 子区间 (l, r) 内全部合法的方案数
int g[MaxN][MaxN];  // 最外面那条边是 (l, r)，之前构成的图形里面至少有一个点
int h[MaxN][MaxN];  // 最外面那条边是 (l, r)，之前构成的图形里面没有点或至少有一个点

class FencingPenguins
{
public:
    // 神坑的题！！！！！！
    int countWays(const int n, const int R, vector<int> px, vector<int> py, string col)
    {
        const double pi = acos(-1);
        const double eps = 1e-7;
        const int m = px.size();
        for(int i = 0; i != n; ++i)
            c[i] = (Point) {R * cos(2 * i * pi / n), R * sin(2 * i * pi / n)};
        for(int i = 0; i != m; ++i)
        {
            p[i] = (Point) {(double) px[i], (double) py[i]};
            color_points[decode(col[i])] |= Bit(i);
            if(p[i].length() > R) return 0; // 有在圆外的不合法
        }
        
        // 预处理每条边{是否合法、右边哪几个点}
        for(int i = 0; i != n; ++i)
            for(int j = i + 1; j != n; ++j)
            {
                Point a = c[i], ab = c[j] - a;
                ll &set = points_set[i][j];
                good[i][j] = 1;
                for(int k = 0; k != m; ++k)
                    if((p[k] - a) * ab >= -eps)
                        set |= Bit(k);
                for(int k = 0; k != 52; ++k)
                    if((set & color_points[k]) && (set & color_points[k]) != color_points[k])
                        good[i][j] = 0;
            }
        if(points_set[0][n - 1] != ((1ll << m) - 1)) return 0;
        for(int i = 0; i != n; ++i)
            if(points_set[i][i + 1]) return 0;
        for(int i = n; i--; )
        {
            h[i][i] = 1;
            for(int j = i + 1; j != n; ++j)
            {
                const ll Ps = points_set[i][j];
                int &F = f[i][j], &S = s[i][j], &G = g[i][j], &H = h[i][j];
                
                // 考虑 G 和 H 的转移
                for(int k = i + 1; k <= j; ++k)
                {
                    // 考虑我们在这个新的多边形上放置了边 (i, k)
                    if(!good[i][k]) continue;
                    // 对于 g，如果三角形 (i, k, j) 不是空的，那么我们可以从 h 转移，否则就只能从 g 转移
                    const int mov_g = ((Ps != points_set[i][k] + points_set[k][j]) ? h : g)[k][j];
                    const int mov_h = h[k][j];
                    // 如果 (i, k) 是空的，就可以直接转移了
                    if(!points_set[i][k])
                    {
                        (G += mov_g) %= mod;
                        (H += mov_h) %= mod;
                    }
                    // 否则，我们要考虑 (i+1, k-1) 这一块区域，是否应该从 s 转移过来
                    else if(k - i >= 4 && points_set[i][k] == points_set[i + 1][k - 1])
                    {
                        int tmp = s[i + 1][k - 1];
                        G = (G + (ll) tmp * mov_g) % mod;
                        H = (H + (ll) tmp * mov_h) % mod;
                    }
                }
                
                // 考虑 F 的转移
                for(int k = i + 2; k <= j; ++k)
                {
                    // 考虑 (i, k) 恰好是一个 g
                    if(!good[i][k]) continue;
                    int mov = g[i][k];
                    // 如果剩下的是空，则可以直接转移 F
                    if(Ps == points_set[i][k])
                        (F += mov) %= mod;
                    // 否则就必须考虑那个梯形是否非空，然后从 s 转移过来
                    else if(k + 3 <= j && (Ps == points_set[i][k] + points_set[k + 1][j]))
                        F = (F + (ll) mov * s[k + 1][j]) % mod;
                }
                
                // 考虑 S 的转移
                for(int k = i; k != j; ++k)
                    // 如果剩下一块区域不包含，就可以从 F 转移来
                    if(Ps == points_set[k][j])
                        (S += f[k][j]) %= mod;
            }
        }
        return s[0][n - 1];
    }
}	user;
