#include <vector>
using namespace std;

#define check(a) (tmp = (a)) > ans ? ans = tmp : 0
int n, v[60];
int count(int x)
{
    int ret = 0;
    for(int i = 1; i <= n - 1; ++i)
        if((v[i - 1] <= x && x <= v[i])
           || (v[i] <= x && x <= v[i - 1])) ++ret;
    for(int i = 1; i <= n - 2; ++i)
        if(v[i] == x) --ret;
    return ret;
}
class PiecewiseLinearFunction
{
public:
    int maximumSolutions(vector<int> _v)
    {
        n = _v.size();
        for(int i = 0; i != n; ++i) ::v[i] = _v[i] * 2;
        for(int i = 1; i != n; ++i) if(v[i - 1] == v[i]) return -1;
        int ans = 0, tmp;
        for(int i = 0; i != n; ++i)
        {
            check(count(v[i]));
            check(count(v[i] + 1));
            check(count(v[i] - 1));
        }
        return ans;
    }
}	user;
