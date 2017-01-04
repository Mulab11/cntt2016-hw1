#include <map>
#include <cmath>
#include <bitset>
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

string s;

struct point
{
	int x,y;
	point(int x0=0,int y0=0) {x=x0;y=y0;}
	point operator -(point a)const {return point(x-a.x,y-a.y);}
}a[230],b[230];

ll cross(point a,point b) {return ll(a.x)*b.y-ll(a.y)*b.x;}

bitset<230> f[230][230],g[230][230],h;

struct CheckerFreeness 
{
    string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY)
    {

        //turn strings into arrays

    	int n1=0;s="";
    	for (int i=0;i<whiteX.size();i++) s+=whiteX[i];
    	int l=s.size(),d=0;
    	for (int i=0;i<=l;i++)
    		if (i==l||s[i]==' ')
    		{
    			a[++n1].x=d;d=0;
    		}
    		else
    			d=d*10+s[i]-'0';
    	n1=0;s="";
    	for (int i=0;i<whiteY.size();i++) s+=whiteY[i];
    	l=s.size();d=0;
    	for (int i=0;i<=l;i++)
    		if (i==l||s[i]==' ')
    		{
    			a[++n1].y=d;d=0;
    		}
    		else
    			d=d*10+s[i]-'0';
    	int n2=0;s="";
    	for (int i=0;i<blackX.size();i++) s+=blackX[i];
    	l=s.size();d=0;
    	for (int i=0;i<=l;i++)
    		if (i==l||s[i]==' ')
    		{
    			b[++n2].x=d;d=0;
    		}
    		else
    			d=d*10+s[i]-'0';
    	n2=0;s="";
    	for (int i=0;i<blackY.size();i++) s+=blackY[i];
    	l=s.size();d=0;
    	for (int i=0;i<=l;i++)
    		if (i==l||s[i]==' ')
    		{
    			b[++n2].y=d;d=0;
    		}
    		else
    			d=d*10+s[i]-'0';


    	for (int i=1;i<=n1;i++)
    		for (int j=1;j<=n2;j++)
    			for (int k=1;k<=n1;k++)
    				if (i!=k)
    				{
    					if (cross(a[k]-a[i],b[j]-a[i])>0) f[i][j][k]=1; else g[i][j][k]=1;
    				}
    	for (int i=1;i<=n2;i++)
    		for (int j=i+1;j<=n2;j++)
    		{
    			for (int k=1;k<=n1;k++)
    				if (cross(a[k]-b[i],b[j]-b[i])<0) h[k]=1; else h[k]=0;
    			for (int k=1;k<=n1;k++)
    				if (!h[k])
    					if ((h&f[k][i]&g[k][j]).any()) return "NO"; //there is a checker
    		}
    	return "YES";
    }
};
