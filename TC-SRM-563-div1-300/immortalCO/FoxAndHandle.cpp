#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int n, cnt[26];
string s;
bool pig(int i)
{
    static int cnt[26];
    memcpy(cnt, ::cnt, 26 << 2);
    for(; i != n; ++i) --cnt[s[i] - 'a'];
    for(i = 0; i != 26; ++i) if(cnt[i] > 0) return 0;
    return 1;
}

class FoxAndHandle
{
public:
    string lexSmallestName(string s)
    {
        // 在 s 中找一个字典序最小的子序列，满足其字母的可重集为给定
        ::s = s;
        n = s.size();
        for(int i = 0; i != n; ++i) ++cnt[s[i] - 'a'];
        for(int i = 0; i != 26; ++i) cnt[i] >>= 1;
        int last = -1;
        string ret;
        for(int i = 0; i != n / 2; ++i)
        {
            // 考虑答案第 i 位是啥
            int p = -1, v = 'z' + 1;
            for(int j = last + 1; j != n; ++j)
                if(s[j] < v && cnt[s[j] - 'a'] > 0)
                {
                    --cnt[s[j] - 'a'];
                    if(pig(j + 1)) v = s[p = j];
                    ++cnt[s[j] - 'a'];
                }
            ret.push_back(v);
            --cnt[v - 'a'];
            last = p;
        }
        return ret;
    }
}	user;
