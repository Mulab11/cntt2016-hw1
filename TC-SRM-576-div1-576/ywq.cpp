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

const int mod=1000000009;

int dp[310][310][2];
string a;
int s[310];

struct TheExperiment
{
    int countPlacements(vector <string> intensity, int M, int L, int A, int B)
    {
        a="";int n0=intensity.size();
        for (int i=0;i<n0;i++) a+=intensity[i];
        int n=a.size();
        s[0]=0;for (int i=0;i<n;i++) s[i+1]=s[i]+a[i]-48;
        for (int i=0;i<n;i++)
            for (int j=0;j<M;j++)
            {
                for (int p=0;p<i;p++) dp[i][j][0]=(dp[i][j][0]+dp[p][j][1])%mod;
                if (j==0) dp[i][j][0]=(dp[i][j][0]+1)%mod;
                for (int k=0;k<2;k++)
                    if (dp[i][j][k])
                        for (int p=i+1;p<=i+L;p++)
                            if (s[p]-s[i]>=A&&s[p]-s[i]<=B)
                                dp[p][j+1][k|(p-i==L)]=(dp[p][j+1][k|(p-i==L)]+dp[i][j][k])%mod;
            }
        int ans=0;
        for (int i=0;i<=n;i++) ans=(ans+dp[i][M][1])%mod;
        return ans;
    }
};
