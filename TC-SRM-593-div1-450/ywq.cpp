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

bool ok[1000010],ok2[1000010];

struct MayTheBestPetWin 
{
    int calc(vector <int> a, vector <int> b)
    {
        int n=a.size();
        memset(ok,0,sizeof(ok));ok[500000]=1;
        for (int i=0;i<n;i++)
        {
            memset(ok2,0,sizeof(ok2));
            for (int j=0;j<=1000000;j++)
                if (ok[j])
                {
                    ok2[j-a[i]]=ok2[j+b[i]]=1;
                }
            for (int j=0;j<=1000000;j++) ok[j]=ok2[j];
        }
        int tmp=0;
        for (int i=0;i<n;i++) tmp+=b[i]-a[i];
        int ans=500000;
        for (int i=0;i<=1000000;i++)
            if (ok[i])
            {
                int t=i-500000;
                ans=min(ans,max(t,tmp-t));
            }
        return ans;
    }
};
