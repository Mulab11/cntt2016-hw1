#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int MaxN = 60;
void clear(int n, bool f[MaxN][MaxN])
{
    for(int i = 0; i != n; ++i)
        memset(f[i], 0, n);
}
bool piggy(string val, string ret)
{
    static int lim[MaxN];
    static bool f[MaxN][MaxN];
    // 先考虑能不能是所有的 push_front 操作构成的
    int n = val.size(), m = ret.size();
    int k = n;
    for(int i = 0; i != m; ++i)
    {
        do --k; while(k >= 0 && val[k] != ret[i]);
        if(k == -1) goto failed;
    }
    return 1;
failed:
    // 枚举到哪一个点是第一个 push_front
    for(k = 0; k != m; ++k) if(ret[k] == val[0])
    {
        // 那么现在就是最初的几个 push_back 是影响后半段前缀的
        string a = ret.substr(0, k + 1);
        string b = ret.substr(k + 1, ret.size() - k - 1);
        reverse(a.begin(), a.end());
        int p = n, A, B;
        lim[k] = n;
        for(int i = a.size(); i--; )
        {
            do p--; while(p >= 0 && val[p] != a[i]);
            if(p == -1) goto skipped;
            lim[i] = p;
        }
        clear(m, f);
        // 把反 a 和 b 一起匹配
        f[0][0] = 1;
        A = a.size(), B = b.size();
        for(int i = 0; i != n; ++i)
        {
            char w = val[i];
            for(int x = 0; x <= i && x <= A; ++x)
                if(f[x][i - x])
                {
                    int y = i - x;
                    if(y == B) // b 匹配完毕
                    {
                        if(i <= lim[x]) return 1;
                        continue;
                    }
                    if(x != A && a[x] == w) f[x + 1][y] = 1;
                    if(y != B && b[y] == w) f[x][y + 1] = 1;
                }
        }
        if(f[A][B]) return 1;
    skipped: continue;
    }
    return 0;
}
bool pig(string val, string ret, string lim, bool Free)
{
    int cnt[10] = {};
    for(int i = val.size(); i--; ) ++cnt[val[i] - '0'];
    for(int i = ret.size(); i--; ) --cnt[ret[i] - '0'];
    for(int i = 0; i != 10; ++i) if(cnt[i] < 0) return 0;
    if(!Free)
    {
        for(int i = ret.size(); i != (int) lim.size(); ++i)
        {
            int d = 9;
            while(d >= lim[i] - '0' && !cnt[d]) --d;
            if(d < lim[i] - '0') return 0;
            if(d > lim[i] - '0') break;
            --cnt[d];
        }
    }
    return piggy(val, ret);
}
string lim;
string dfs(string val, string ret, bool Free)
{
    if(ret.size() == val.size())
        return ret;
    int i = ret.size();
    for(char w = (Free ? '0' : lim[i]); w <= '9'; ++w)
        if(pig(val, ret + w, lim, Free || w > lim[i]))
        {
            string ans = dfs(val, ret + w, Free || w > lim[i]);
            if(ans.size()) return ans;
        }
    return "";
}

class LeftRightDigitsGame2
{
public:
    string minNumber(string val, string lim)
    {
        // 考虑按位确定
        ::lim = lim;
        return dfs(val, "", 0);
    }
}	user;
