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

string s;
pii a[510];

struct EllysRoomAssignmentsDiv1 
{
    double getAverage(vector <string> ratings)
    {
    	s="";
    	for (int i=0;i<ratings.size();i++) s+=ratings[i];
    	int l=s.size(),m=0,d=0;
    	for (int i=0;i<=l;i++)
    		if (i==l||s[i]==' ')
    		{
    			a[m]=mp(d,m);m++;d=0;
    		}
    		else
    			d=d*10+s[i]-'0';
    	sort(a,a+m);
    	for (int i=0;i<(m/2);i++) swap(a[i],a[m-1-i]);
    	int R=(m-1)/20+1;
		double ans=0,x0;int y0=0,t=0,p;	
    	for (int i=0;i<=(m-1)/R;i++)
    	{
    		int s=0,x=0,y=0;
    		for (int j=i*R;j<(i+1)*R&&j<m;j++)
    		{
    			s+=a[j].x;if (!a[j].y) x=a[j].x;y++;
    		}
    		if (!x)
    		{
    			if (y==R) {ans+=double(s)/y;t++;} else {x0=double(s)/y;y0=y;}
    		}
    		else
    			p=x;
    	}
    	double ans0=0;
    	ans0=(ans+p)*(R-y0)/R/(t+1);
    	ans0+=(ans+x0+p)/(t+2)*y0/R;
    	return ans0;
    }
};
