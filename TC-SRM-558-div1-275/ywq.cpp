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

const int inf=1000000000;

int a[55],dp[55][55][3];

struct Stamp 
{
    int getMinimumCost(string desiredColor, int stampCost, int pushCost)
    {
        int n=desiredColor.size();
        for (int i=0;i<n;i++)
        {
            if (desiredColor[i]=='R') a[i]=0;
            if (desiredColor[i]=='G') a[i]=1;
            if (desiredColor[i]=='B') a[i]=2;
            if (desiredColor[i]=='*') a[i]=3;
        }
        int ans=inf;
        for (int i=1;i<=n;i++)
        {
            for (int j=0;j<=n;j++)
                for (int p=1;p<=n;p++)
                    for (int k=0;k<3;k++)
                        dp[j][p][k]=n+1;
            if (a[0]<3) dp[0][1][a[0]]=0; else for (int j=0;j<3;j++) dp[0][1][j]=0;
            for (int j=1;j<n;j++)
                for (int p=1;p<=n;p++)
                    for (int q=0;q<3;q++)
                        for (int l=0;l<3;l++)
                            if (a[j]==3||l==a[j])
                            {
                                if (l!=q)
                                {
                                    if (p<i) continue; //the length of the consecutive part can't be less than i
                                    dp[j][1][l]=min(dp[j][1][l],dp[j-1][p][q]+(p+i-1)/i);
                                }
                                else
                                    dp[j][p+1][q]=min(dp[j][p+1][q],dp[j-1][p][q]);
                            }
            for (int p=i;p<=n;p++)
                for (int q=0;q<3;q++)
                    if (dp[n-1][p][q]<=n) ans=min(ans,(dp[n-1][p][q]+(p+i-1)/i)*pushCost+i*stampCost);
        }
        return ans;
    }
};
