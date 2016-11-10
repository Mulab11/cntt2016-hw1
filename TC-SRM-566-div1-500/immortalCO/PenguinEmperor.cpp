#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MaxN = 350;
const int mod = 1e9 + 7;

int n;
typedef int Perm[MaxN];
Perm cur, bak, tmp;
void mul(Perm a, Perm b)
{
    memset(tmp, 0, n << 2);
    int k;
    for(int i = 0; i != n; ++i)
        for(int j = 0; j != n; ++j)
        {
            k = (ll) a[i] * b[j] % mod;
            (tmp[(i + j) % n] += k) %= mod;
        }
    memcpy(a, tmp, n << 2);
}

class PenguinEmperor
{
public:
    int countJourneys(int n, ll m)
    {
        ::n = n;
        int rem = m % n;
        cur[0] = bak[0] = 1;
        for(int d = 1; d != n; ++d)
        {
            memset(tmp, 0, n << 2);
            for(int i = 0; i != n; ++i)
            {
                (tmp[(i + 0 + d) % n] += cur[i]) %= mod;
                if(d * 2 == n) continue;
                (tmp[(i + n - d) % n] += cur[i]) %= mod;
            }
            memcpy(cur, tmp, n << 2);
            if(d == rem) memcpy(bak, tmp, n << 2);
        }
        m /= n;
        for(; m; m >>= 1)
        {
            if(m & 1) mul(bak, cur);
            if(m > 1) mul(cur, cur);
        }
        return bak[0];
    }
}	user;
