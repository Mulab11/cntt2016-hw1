#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;
// 带通配符的匹配
bool match(string s, string t)
{
    for(int i = s.size(); i--; )
        if(t[i] != '*' && s[i] != t[i])
            return 0;
    return 1;
}
// 将带通配符的串转为约数
ll convert(string cur)
{
    ll ret = 0;
    for(int i = cur.size(); i--; )
        if(cur[i] == '*') ret |= 1ll << i;
    return ret;
}
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
int total;
ll patterns[20000];

ll solve(int len, vector<ll> vec)
{
    if(vec.empty()) return 0;
    static int vis[60], pid[60], timer;
    int n = vec.size();
    ll *a = vec.data();
    
    // 首先只提取出有 1 的二进制位
    int tot = 0; ++timer;
    vector<ll> v0, v1;
    for(int i = 0, k; i != n; ++i)
    {
        ll t = 0;
        for(ll s = a[i]; s; s -= 1ll << k)
        {
            k = __builtin_ctzll(s);
            if(vis[k] != timer) {vis[k] = timer; pid[k] = tot++;}
            t |= 1ll << pid[k];
        }
        a[i] = t;
    }
    
    if(!tot) return 1ll << len;
    
    // 然后把有子集包含的合并了
    sort(a, a + n);
    n = unique(a, a + n) - a;
    int m = 0;
    for(int i = 0; i != n; ++i)
    {
        ll t = a[i];
        for(int j = 0; j != m; ++j)
            if((t | a[j]) == t) goto failed;
        a[m++] = t;
        if(~t & 1) v0.push_back(t >> 1);
        v1.push_back(t >> 1);
    failed: continue;
    }
    // 这是去掉了全 0 位置之后的系数 2^(len-tot)
    return (solve(tot - 1, v0) + solve(tot - 1, v1)) << (len - tot);
}

class MapGuessing
{
public:
    ll countPatterns(string goal, vector<string> input_code)
    {
        const int n = goal.size();
        string code;
        for(int i = 0; i != (int) input_code.size(); ++i)
            code += input_code[i];
        int l = 0, r = 0, p = 0;
        for(int i = 0; i != (int) code.size(); ++i)
        {
            if(code[i] == '<') --p;
            if(code[i] == '>') ++p;
            if(p < l) l = p;
            if(p > r) r = p;
        }
        if(r - l >= n) return 0;
        
        string empty;
        for(int i = 0; i != n; ++i) empty.push_back('*');
        patterns[total++] = (1ll << n) - 1;
        for(int start = 0; start != n; ++start)
            if(start + l >= 0 && start + r < n)
            {
                int p = start;
                string cur = empty;
                for(int i = 0; i != (int) code.size(); ++i)
                    switch(code[i])
                {
                    case '<': --p; break;
                    case '>': ++p; break;
                    default:
                        cur[p] = code[i];
                        if(match(goal, cur))
                            patterns[total++] = convert(cur);
                }
            }
        // 暴力统计方案数
        return solve(n, vector<ll>(patterns, patterns + total));
    }
}	user;
