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

int sqr(int x) {return x*x;}

int b[50010][3],c[50010][3];

struct FindPolygons 
{
    double minimumPolygon(int L)
    {
    	if (L%2==1||L<=2) return -1;
    	int m1=0,m2=0;
    	for (int i=0;i<=L/2;i++)
    		for (int j=0;j<=L/2;j++)
    		{
    			if (i==0&&j==0) continue;
    			int x=i*i+j*j;int p=sqrt(x+0.5);
    			if (p*p==x&&p<=L/2)
    			{
    				if (i==0||j==0) {b[++m1][0]=i;b[m1][1]=j;b[m1][2]=p;} else {c[++m2][0]=i;c[m2][1]=j;c[m2][2]=p;}
    			}
    		}
    	int ans=L;
    	for (int i=1;i<=m1;i++)
    		for (int j=1;j<=m2;j++)
    		{
    			int x=sqr(b[i][0]-c[j][0])+sqr(b[i][1]-c[j][1]);
    			int p=sqrt(x+0.5);
    			if (p*p==x&&b[i][2]+c[j][2]+p==L) ans=min(ans,max(max(b[i][2],c[j][2]),p)-min(min(b[i][2],c[j][2]),p));
    		}
    	for (int i=1;i<=m2;i++)
    		for (int j=i+1;j<=m2;j++)
    		{
    			int x=sqr(c[i][0]-c[j][0])+sqr(c[i][1]-c[j][1]);
    			int p=sqrt(x+0.5);
    			if (p*p==x&&c[i][2]+c[j][2]+p==L&&c[i][0]*c[j][1]!=c[i][1]*c[j][0]) ans=min(ans,max(max(c[i][2],c[j][2]),p)-min(min(c[i][2],c[j][2]),p));
    		}
    	if (ans<L) return ans; else return L/2%2;
    }
};
