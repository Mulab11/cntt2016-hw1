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

const int mod=555555555;

int c[3210][3210];

struct XorBoard 
{
    int count(int H, int W, int Rcount, int Ccount, int S)
    {
    	for (int i=0;i<=3200;i++)
    	{
    		c[i][0]=c[i][i]=1;
    		for (int j=1;j<i;j++) c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod;
    	}
    	int ans=0;
    	for (int i=0;i<=H;i++)
    		if (i%2==Rcount%2&&i<=Rcount)
    		{
    			int res=(Rcount-i)/2;
    			int t=ll(c[H][i])*c[res+H-1][H-1]%mod;
    			if (i*2==H)
    			{
    				if (H*W/2==S) //every column can be changed any times
    				{
    					t=ll(t)*c[Ccount+W-1][W-1]%mod;
    					ans=(ans+t)%mod;
    				}
    			}
    			else
    			{
    				if ((i*W-S)%(2*i-H)==0)
    				{
    					int j=(i*W-S)/(2*i-H); //the number of reversed columns
    					if (j<0||j>W) continue;
    					if (j<=Ccount&&j%2==Ccount%2)
    					{
    						int res=(Ccount-j)/2;
    						t=ll(t)*c[W][j]%mod*c[res+W-1][W-1]%mod;
    						ans=(ans+t)%mod;
    					}
    				}
    			}
    		}
    	return ans;
    }
};
