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

double f[55][55][55][4],g[55][55][55][4];

struct RockPaperScissors 
{
    double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb)
    {
    	int n=rockProb.size();
    	for (int i=1;i<4;i++) f[0][0][0][i]=0;f[0][0][0][0]=1;
    	for (int i=0;i<n;i++)
    	{
    		for (int p=0;p<=i+1;p++)
    			for (int q=0;p+q<=i+1;q++)
    				for (int r=0;p+q+r<=i+1;r++)
    					for (int k=0;k<4;k++)
    					{
    						g[p][q][r][k]=f[p][q][r][k];
    						f[p][q][r][k]=0;
    					}
    		for (int p=0;p<=i;p++)
    			for (int q=0;p+q<=i;q++)
    				for (int r=0;p+q+r<=i;r++)
    				{
    					double t;
    					t=double(rockProb[i])/300/(n-p-q-r)*(p+q+r+1);
    					for (int k=0;k<4;k++) f[p+1][q][r][k]+=g[p][q][r][k]*t;
    					t=double(paperProb[i])/300/(n-p-q-r)*(p+q+r+1);
    					for (int k=0;k<4;k++) f[p][q+1][r][k]+=g[p][q][r][k]*t;
    					t=double(scissorsProb[i])/300/(n-p-q-r)*(p+q+r+1);
    					for (int k=0;k<4;k++) f[p][q][r+1][k]+=g[p][q][r][k]*t;
    					f[p][q][r][0]+=g[p][q][r][0];
    					f[p][q][r][1]+=g[p][q][r][0]*rockProb[i]/300+g[p][q][r][1];
    					f[p][q][r][2]+=g[p][q][r][0]*paperProb[i]/300+g[p][q][r][2];
    					f[p][q][r][3]+=g[p][q][r][0]*scissorsProb[i]/300+g[p][q][r][3];
    				}
    	}
    	double ans=0;
    	for (int p=0;p<n;p++)
    		for (int q=0;p+q<n;q++)
    			for (int r=0;p+q+r<n;r++)
    			{
    				double t=0;
    				for (int j=0;j<3;j++) t=max(t,f[p][q][r][j+1]*3+f[p][q][r][(j+1)%3+1]);
    				ans+=t/(n-p-q-r);
    			}
    	return ans;
    }
};
