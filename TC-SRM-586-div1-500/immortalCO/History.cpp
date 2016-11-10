#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

vector<string> split(string s)
{
    vector<string> ret;
    s.push_back(' ');
    string t;
    for(int i = 0; i != (int) s.length(); ++i)
        if(s[i] == ' ') ret.push_back(t), t.clear();
        else t.push_back(s[i]);
    return ret;
}
vector<int> convert(const vector<string>& vec)
{
    vector<int> ret;
    int tmp = -1;
    for(int i = 0; i != (int) vec.size(); ++i)
    {
        sscanf(vec[i].c_str(), "%d", &tmp);
        ret.push_back(tmp);
    }
    return ret;
}

const int MaxN = 300;
#define to first
#define len second
#define mkp make_pair
vector< pair<int, int> > e[MaxN];
int n, pos[26][11], d[MaxN];
bool v[MaxN];
bool dfs(int p)
{
    v[p] = 1;
    for(int k = e[p].size(); k--; )
    {
        int q = e[p][k].to, w = e[p][k].len;
        if(d[p] + w < d[q])
        {
            d[q] = d[p] + w;
            if(v[q] || dfs(q)) return 1;
        }
    }
    v[p] = 0;
    return 0;
}
bool pig()
{
    memset(v, 0, n);
    memset(d, 0, n << 2);
    for(int i = 0; i != n; ++i)
        if(dfs(i)) return 1;
    return 0;
}

void add(int x, int y, int v)
{
    e[x].push_back(mkp(y, v));
}

class History
{
public:
    // 差分约束
    string verifyClaims(vector<string> dyn, vector<string> bat, vector<string> que)
    {
        // 0 号点为正无穷年
        for(int i = 0; i != (int) dyn.size(); ++i)
        {
            vector<int> list = convert(split(dyn[i]));
            for(int k = 0; k != (int) list.size(); ++k)
                pos[i][k] = n++;
            for(int k = 1; k != (int) list.size(); ++k)
            {
                int x = pos[i][k - 1], y = pos[i][k], v = list[k] - list[k - 1];
                // x -> y, v : t[x] + v >= t[y]
                add(x, y, v);
                add(y, x, -v);
            }
        }
        string battle;
        for(int i = 0; i != (int) bat.size(); ++i) battle += bat[i];
        vector<string> list = split(battle);
        for(int i = 0; i != (int) list.size(); ++i)
        {
            int x0 = list[i][0] - 'A', y0 = list[i][1] - '0';
            int x1 = list[i][3] - 'A', y1 = list[i][4] - '0';
            // 要让区间有交
            // pos[x0][y0 + 1] > pos[x1][y1]
            // pos[x1][y1 + 1] > pos[x0][y0]
            // a > b  ->  a - 1 >= b
            add(pos[x0][y0 + 1], pos[x1][y1], -1);
            add(pos[x1][y1 + 1], pos[x0][y0], -1);
        }
        string ret;
        for(int i = 0; i != (int) que.size(); ++i)
        {
            int x0 = que[i][0] - 'A', y0 = que[i][1] - '0';
            int x1 = que[i][3] - 'A', y1 = que[i][4] - '0';
            add(pos[x0][y0 + 1], pos[x1][y1], -1);
            add(pos[x1][y1 + 1], pos[x0][y0], -1);
            ret.push_back("YN"[pig()]);
            e[pos[x0][y0 + 1]].pop_back();
            e[pos[x1][y1 + 1]].pop_back();
        }
        return ret;
    }
}	user;
