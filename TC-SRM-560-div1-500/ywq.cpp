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

int a[310][310],b[310][310];
bool ok[310][310];

struct DrawingPointsDivOne 
{
    int maxSteps(vector <int> x, vector <int> y)
    {
    	int n=x.size();
    	for (int i=0;i<n;i++) {x[i]+=71;y[i]+=71;}

        //binary search

    	int l=0,r=150;
    	while (l<=r)
    	{
    		int mid=(l+r)>>1;
    		memset(a,0,sizeof(a));
    		for (int i=0;i<n;i++)
    		{
    			a[x[i]][y[i]]++;a[x[i]+mid][y[i]]--;
    			a[x[i]][y[i]+mid]--;a[x[i]+mid][y[i]+mid]++;
    		}
    		memset(b,0,sizeof(b));
    		for (int i=1;i<=300;i++)
    		{
    			int s=0,s2=0;
    			for (int j=1;j<=300;j++)
    			{
    				s2+=a[i][j];a[i][j]=a[i-1][j]+s2;
    				if (a[i][j]) s++; //there is a point in grid(i,j)
    				b[i][j]=b[i-1][j]+s;
    			}
    		}
    		memset(ok,0,sizeof(ok));
    		for (int i=0;i<n;i++) ok[x[i]][y[i]]=1;
    		bool t=1;
    		for (int i=0;i<=150;i++)
    			for (int j=0;j<=150;j++)
    				if ((!ok[i+1][j+1])&&b[i+mid][j+mid]-b[i][j+mid]-b[i+mid][j]+b[i][j]==mid*mid) t=0;
    		if (t) l=mid+1; else r=mid-1;
    	}
    	if (r==150) return -1; else return r-1;
    }
};
