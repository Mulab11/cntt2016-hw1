#include <map>
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
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

string s;

struct FlippingBitsDiv1
{
    int getmin(vector <string> S, int m)
    {
    	s="";
    	for (int i=0;i<S.size();i++) s+=S[i];
    	int n=s.size();
    	if (m<=17)
    	{
    		int dp[2],dp2[2],c[20],ans=n;
    		for (int p=0;p<(1<<m);p++)
    		{
    			dp[0]=0;dp[1]=1;
    			for (int i=0;i<m;i++) if (p&(1<<i)) c[i]=1; else c[i]=0;
    			for (int i=(n-1)/m;i>=0;i--)
    			{
    				for (int j=0;j<2;j++) dp2[j]=n;
    				for (int j=0;j<2;j++)
    					for (int k=0;k<2;k++)
    					{
    						int t=dp[j]+k;
    						for (int q=i*m;q<(i+1)*m&&q<n;q++)
    							if (s[q]-48!=(c[q%m]^j^k)) t++;
    						dp2[j^k]=min(dp2[j^k],t);
    					}
    				for (int j=0;j<2;j++) dp[j]=dp2[j];
    			}
                ans=min(ans,min(dp[0],dp[1]));
    		}
    		return ans;
    	}
    	int b[20];
    	int k=(n-1)/m+1,ans=n;
    	for (int i=0;i<(1<<k);i++)
    	{
    		int tmp=0;
    		for (int j=0;j<k;j++) if (i&(1<<j)) {b[j]=1;tmp++;} else b[j]=0;
    		for (int j=k-1;j;j--) b[j-1]^=b[j];
    		for (int j=0;j<m;j++)
    		{
    			int s0=0,s1=0;
    			for (int p=j;p<n;p+=m)
    			{
    				s0++;
    				if ((s[p]-48)^b[p/m]) s1++;
    			}
    			tmp+=min(s1,s0-s1);
    		}
    		ans=min(ans,tmp);
    	}
    	return ans;
    }	
};
