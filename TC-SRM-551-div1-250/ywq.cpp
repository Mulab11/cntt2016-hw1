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

int dp1[55],dp2[55];

struct ColorfulChocolates 
{
    int maximumSpread(string chocolates, int maxSwaps)
    {
    	int n=chocolates.size(),ans=0;
    	for (int i=0;i<n;i++)//enumerate which chocolate doesn't move
    	{
    		dp1[i]=0;dp2[i]=0;int s=0;
    		for (int j=i-1;j>=0;j--)
    		{
    			dp1[j]=dp1[j+1];dp2[j]=dp2[j+1];
    			if (chocolates[j]==chocolates[i]) {dp2[j]++;dp1[j]+=s;} else s++;
    		}
    		s=0;
    		for (int j=i+1;j<n;j++)
    		{
    			dp1[j]=dp1[j-1];dp2[j]=dp2[j-1];
    			if (chocolates[j]==chocolates[i]) {dp2[j]++;dp1[j]+=s;} else s++;
    		}
    		int k=n-1;
    		for (int j=i;j>=0;j--)
    		{
    			while (k>=i&&dp1[j]+dp1[k]>maxSwaps) k--;//two pointers
    			if (k<i) break;
    			ans=max(ans,dp2[j]+dp2[k]+1);
    		}
    	}
    	return ans;
    }
};
