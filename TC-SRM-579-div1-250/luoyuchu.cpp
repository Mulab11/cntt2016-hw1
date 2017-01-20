#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

template <class TAT>
void Ckmax(TAT &a, const TAT &b)
{
    if (a < b) a = b;
}
template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
    if (a > b) a = b;
}

typedef long long LL;

class UndoHistory {
    public:
    int minPresses(vector<string> lines) {
        int Ans = 0;
        Ans += lines[0].length() + 1;
        for (int i = 1; i < lines.size(); ++i) {
            int nowlen = lines[i].length();
            int lastlen, com, Max, last;
            Max = 0;
            for (int j = 0; j < i; ++j) {//检查当前要达到的状态与所有历史状态的最大公共前缀
                lastlen = lines[j].length();
                com = -1;
                for (int k = 0; k < min(lastlen, nowlen); ++k) {
                    if (lines[j][k] == lines[i][k]) {
                        Ckmax(com, k);
                    }
                    else {
                        break;
                    }
                }
                Ckmax(Max, com + 1);
                if (j == i - 1) {//记录当前状态是否是要达到的状态的前缀
                    last = com + 1;
                }
            }
            if (last == lines[i - 1].length()) {//在撤回最大历史和不撤回之间选择最小值
                Ans += min(2 + nowlen - Max + 1, nowlen - last + 1);
            }
            else {
                Ans += 2 + nowlen - Max + 1;//直接撤回最大历史
            }
        }
        return Ans;
    }
};
