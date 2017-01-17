#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

#define pb push_back
#define mp make_pair
#define x first
#define y second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;

int c[55];

struct XorCards 
{
    long long numberOfWays(vector<long long> number, long long limit)
    {
        int n=number.size(),m=0;
        for (int i=50;i>=0;i--)
        {
            int k=-1;
            for (int j=m;j<n;j++) if (number[j]&(1ll<<i)) {k=j;break;}
            if (k!=-1)
            {
                swap(number[m],number[k]);
                for (int j=m+1;j<n;j++) if (number[j]&(1ll<<i)) number[j]^=number[m];
                c[i]=m++;
            }
            else
                c[i]=-1;
        }
        ll ans=0,t=0;bool ok=1;
        for (int i=50;i>=0;i--)
            if (c[i]>=0)
            {
                if (limit&(1ll<<i)||(!ok))
                {
                    ans+=1ll<<(m-c[i]-1);
                    if (!(t&(1ll<<i))) t^=number[c[i]];
                }
                else
                    if (t&(1ll<<i)) t^=number[c[i]];
            }
            else
            {
                if ((limit&(1ll<<i))&&!(t&(1ll<<i))) ok=0;
                if (ok&&(t&(1ll<<i))&&!(limit&(1ll<<i))) break;
            }
        if (t<=limit) ans++;
        return ans<<(n-m);
    }   
};
