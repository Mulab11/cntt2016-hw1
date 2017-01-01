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

int a[55];
bool dp[55][2510];

struct KingdomAndDice 
{
    double newFairness(vector <int> firstDie, vector <int> secondDie, int X)
    {
    	int n=firstDie.size(),m=0;
        //Discretization
    	for (int i=0;i<n;i++) if (firstDie[i]) a[m++]=firstDie[i];
    	for (int i=0;i<n;i++) a[m++]=secondDie[i];
    	sort(a,a+m);
    	int s1=0,s2=0;
    	for (int i=0;i<n;i++)
    		if (firstDie[i])
    		{
    			s1++;
    			for (int j=0;j<n;j++) if (firstDie[i]>secondDie[j]) s2++;
    		}
        //dp[i][j]:we've already known i elements of firstDie and the number of pairs (p,q) that firstDie[p]>secondDie[q] is j
    	for (int k=s1;k<=n;k++) dp[k][s2]=1;
    	for (int i=1;i<m;i++)
   		{
   			int t=0;
   			for (int j=0;j<n;j++) if (a[i]>secondDie[j]) t++;
   			for (int p=0;p<min(n,a[i]-a[i-1]-1);p++)
   				for (int j=n;j>s1;j--)
   					for (int k=n*n/2+n;k>=t;k--)
   						dp[j][k]|=dp[j-1][k-t];
   		}
    	for (int i=0;i<min(n,X-a[m-1]);i++)
    		for (int j=n;j>s1;j--)
    			for (int k=n*n/2+n;k>=n;k--)
    				dp[j][k]|=dp[j-1][k-n];
    	if (n&1)
    	{
    		int x=n*n/2;
    		for (int i=0;i<=x;i++)
    		{
    			if (dp[n][x-i]) return double(x-i)/n/n;
    			if (dp[n][x+i+1]) return double(x+i+1)/n/n;
    		}
    	}
    	else
    	{
    		int x=n*n/2;
    		for (int i=0;i<=x;i++)
    		{
    			if (dp[n][x-i]) return double(x-i)/n/n;
    			if (dp[n][x+i]) return double(x+i)/n/n;
    		}
    	}
    }
};
