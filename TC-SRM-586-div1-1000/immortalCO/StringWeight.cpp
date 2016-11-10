#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define dmax(a, b) ((a) > (b) ? (a) : (b))
#define dmin(a, b) ((a) < (b) ? (a) : (b))

const int inf = 1e9;
int f[2][27][27];
void clear(bool d) {memset(f[d], 63, sizeof f[d]);}
inline void contribute(int f[27][27], int a, int b, int v)
{
    if(f[a][b] > v) f[a][b] = v;
}
void extend(const int v, const int a, const int b, const int n, int f[27][27])
{
    if(v >= inf || 26 - b < dmin(26, n)) return;
    
    // 我们从左到右构造字符串
    // 那么状态只和两个有关：a. 未停止的字母个数; b. 已停止的字母个数
#define Count(n) (((n) * ((n) + 1)) >> 1)
    // 先计算被迫开始的字母，这样的字母有 c = 26 - a - b 个
    // 我们把它们排在序列的末尾，这样增加的量是最多的。
    const int c = dmax(0, dmin(26, n) - a);
    for(int a_stop = 0; a_stop <= a; ++a_stop)
        for(int c_stop = 0; c_stop <= c; ++c_stop)
        {
            const int a_stay = a - a_stop;
            const int c_stay = c - c_stop;
            // 如果不是所有字母都停止，我们可以把 a_stop 放在开头，c_stop 放在中间，c_stay 放在结尾，如果超了的话就把中间的 (n - 25) 个字母放在 a_stay，这样就只需要各出现一次
            if(n <= 26 || a_stay)
                contribute(f, a_stay + c_stay, b + a_stop + c_stop, v + Count(a_stop) + Count(c_stay - 1) + (a_stay * n));
            // 否则，有一个字母出现了 n - 26 次，增加了 n - 26 的贡献
            else
                contribute(f, a_stay + c_stay, b + a_stop + c_stop, v + Count(a_stop) + Count(c_stay - 1) + (a_stay * n) + (n - 26));
        }
}

class StringWeight
{
public:
    int getMinimum(vector<int> len)
    {
        // 轻字符串：
        // 存在 k = min(26, n) 个字符
        // 其他字符都只出现一次，只有一个字符出现了 n - k 次
        // 多次出现的那个字符出现在一个区间中
        bool d = 0;
        clear(d);
        f[d][0][0] = 0;
        for(int i = 0; i != len.size(); ++i)
        {
            clear(d = !d);
            for(int a = 0; a <= 26; ++a) for(int b = 0; b <= 26; ++b)
                extend(f[!d][a][b], a, b, len[i], f[d]);
        }
        int ans = inf;
        for(int b = 0; b <= 26; ++b)
            if(f[d][0][b] < ans) ans = f[d][0][b];
        return ans;
    }
}	user;
