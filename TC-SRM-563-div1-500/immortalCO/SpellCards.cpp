#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 60;
int f[MaxN];

class SpellCards
{
public:
    int maxDamage(vector<int> _a, vector<int> _b)
    {
        int n = _a.size();
        for(int i = 0; i != n; ++i)
        {
            int A = _a[i], B = _b[i];
            for(int j = n; j >= A; --j)
                if(f[j] < f[j - A] + B)
                    f[j] = f[j - A] + B;
        }
        return f[n];
    }
}	user;
