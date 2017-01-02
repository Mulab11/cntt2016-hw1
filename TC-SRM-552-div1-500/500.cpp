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

int a[35][35],b[35][35];
int f1[35][910],f2[35][910],f3[35][910],f4[35][910];

struct FoxAndFlowerShopDivOne 
{
    int theMaxFlowers(vector <string> flowers, int maxDiff)
    {
    	int n=flowers.size(),m=flowers[0].size();
    	for (int i=1;i<=n;i++)
    	{
    		int s1=0,s2=0;
    		for (int j=1;j<=m;j++)
    		{
    			if (flowers[i-1][j-1]=='L') s1++; else if (flowers[i-1][j-1]=='P') s2++;
    			a[i][j]=a[i-1][j]+s1;b[i][j]=b[i-1][j]+s2;
    		}
    	}
    	for (int i=0;i<=n*m;i++)
    	{
    		for (int j=1;j<=n;j++) f1[j][i]=f2[j][i]=-1000;
    		for (int j=1;j<=m;j++) f3[j][i]=f4[j][i]=-1000;
    	}
        //enumerate all the rectangles and update the prefix maximum and the suffix maximum
    	for (int i=1;i<=n;i++)
    		for (int j=1;j<=m;j++)
    			for (int p=i;p<=n;p++)
    				for (int q=j;q<=m;q++)
    				{
    					int s1=a[p][q]-a[i-1][q]-a[p][j-1]+a[i-1][j-1];
    					int s2=b[p][q]-b[i-1][q]-b[p][j-1]+b[i-1][j-1];
    					int s3=s1+s2,s4=s1-s2+b[n][m];
    					for (int k=p;k<=n;k++) f1[k][s4]=max(f1[k][s4],s3);
    					for (int k=i;k>=1;k--) f2[k][s4]=max(f2[k][s4],s3);
    					for (int k=q;k<=m;k++) f3[k][s4]=max(f3[k][s4],s3);
    					for (int k=j;k>=1;k--) f4[k][s4]=max(f4[k][s4],s3);
    				}
    	int ans=-1;
        //split two rectangles by the row
    	for (int i=1;i<n;i++)
    		for (int j=0;j<=n*m;j++)
    			for (int k=0;k<=n*m;k++)
    				if (abs(j-b[n][m]+k-b[n][m])<=maxDiff) ans=max(ans,f1[i][j]+f2[i+1][k]);
    	//split two rectangles by the column
        for (int i=1;i<m;i++)
    		for (int j=0;j<=n*m;j++)
    			for (int k=0;k<=n*m;k++)
    				if (abs(j-b[n][m]+k-b[n][m])<=maxDiff) ans=max(ans,f3[i][j]+f4[i+1][k]);
    	return ans;
    }
};
