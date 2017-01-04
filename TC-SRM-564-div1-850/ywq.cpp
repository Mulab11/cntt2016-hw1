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

const int mod=1000000007;

int dp[55][55],pow2[35];

struct DefectiveAddition 
{
    int count(vector <int> cards, int n)
    {
    	int m=cards.size(),ans=0;
    	for (int i=0;i<m;i++) cards[i]++;
    	pow2[0]=1;for (int i=1;i<=30;i++) pow2[i]=ll(pow2[i-1])*((mod+1)/2)%mod; //2^(-i)
    	for (int i=30;i>=0;i--)
    	{
    		memset(dp,0,sizeof(dp));dp[0][0]=1;int cnt=0;
    		for (int j=0;j<m;j++)
    		{
    			if (cards[j]&(1<<i)) cnt++;
    			for (int k=0;k<=m;k++)
    				if (cards[j]&(1<<i))
    				{
    					dp[j+1][k]=(ll(dp[j][k])*(1<<i)+dp[j+1][k])%mod;
      					dp[j+1][k+1]=(ll(dp[j][k])*(cards[j]%(1<<i))+dp[j+1][k+1])%mod;
    				}
    				else
    					dp[j+1][k]=(ll(dp[j][k])*(cards[j]%(1<<i))+dp[j+1][k])%mod;
    		}
    		int x=0;
    		if (n&(1<<i)) x=1;
    		for (int j=x;j<cnt;j+=2) ans=(ll(dp[m][j])*pow2[i]+ans)%mod; //one card's value is fixed
    		if (((cnt&1)&&(!(n&(1<<i))))||((!(cnt&1))&&(n&(1<<i)))) break;
    	}
    	return ans;
    }
};
