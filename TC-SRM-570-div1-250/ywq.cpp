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

const int di[4][2]={{0,1},{1,0},{0,-1},{-1,0}};

struct RobotHerb 
{
    long long getdist(int T, vector <int> a)
    {
    	int x=0,y=0,z=0;
    	for (int i=0;i<a.size();i++)
    	{
    		x+=a[i]*di[z][0];y+=a[i]*di[z][1];
    		z=(z+a[i])%4;
    	}
    	int tx=0,ty=0,tz=0;
    	for (int i=0;i<4;i++)
    	{
    		if (tz==0) {tx+=x;ty+=y;}
    		if (tz==1) {tx+=y;ty-=x;}
    		if (tz==2) {tx-=x;ty-=y;}
    		if (tz==3) {tx-=y;ty+=x;}
    		tz=(tz+z)%4;
    	}
    	ll p=ll(T/4)*tx,q=ll(T/4)*ty;
    	tz=0;
    	for (int i=0;i<T%4;i++)
    	{
    		if (tz==0) {p+=x;q+=y;}
    		if (tz==1) {p+=y;q-=x;}
    		if (tz==2) {p-=x;q-=y;}
    		if (tz==3) {p-=y;q+=x;}
    		tz=(tz+z)%4;
    	}
    	return abs(p)+abs(q);
    }
};
