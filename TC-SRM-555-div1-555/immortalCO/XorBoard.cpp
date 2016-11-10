#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
const int mod = 555555555;
const int MaxN = 3200;
int comb[MaxN][MaxN];

class XorBoard
{
public:
    int count(int N, int M, int R, int C, int S)
    {
        int L = std::max(std::max(N, M), std::max(R, C)) * 2;
        comb[0][0] = 1;
        for(int i = 1; i <= L; ++i)
        {
            comb[i][0] = comb[i][i] = 1;
            for(int j = 1; j != i; ++j)
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }
        int ans = 0;
        // 枚举被选了奇数次的行数 A，把这些行先选出来
        // 考虑哪些被选了偶数次的行，将这些选择两两配对
        // 那么剩下的是一个大小为 (R - A) / 2，值域为 [1, N] 的可重集合
        // 可重集合可以对应成不降数列，用组合数计算即可
        for(int A = R % 2; A <= R; A += 2)
        {
            if(A * 2 == N)
            {
                if(A * M == S)
                {
                    int tmp = (ll) comb[N][A] * comb[(R - A) / 2 + N - 1][N - 1] % mod;
                    for(int B = C % 2; B <= C; B += 2)
                        ans = (ans + (ll) tmp * comb[M][B] % mod * comb[(C - B) / 2 + M - 1][M - 1]) % mod;
                }
                continue;
            }
            // 这里的面积是一个十字形
            // 可以弄出一个方程
            // 但要满足不能超过 C、得和 C 的奇偶性相同的约数
            int tmp = S - A * M;
            if(tmp % (N - A * 2)) continue;
            int B = tmp / (N - A * 2);
            if(B < 0 || B > C || (C - B) % 2) continue;
            ans = (ans + (ll) comb[N][A] % mod * comb[(R - A) / 2 + N - 1][N - 1] % mod
                   * comb[M][B] % mod * comb[(C - B) / 2 + M - 1][M - 1]) % mod;
        }
        return ans;
    }
}	user;
