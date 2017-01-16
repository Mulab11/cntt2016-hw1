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

int q[55],d[55];

struct TravelOnMars 
{
    int minTimes(vector <int> range, int startCity, int endCity)
    {
    	int n=range.size();
    	for (int i=0;i<n;i++) d[i]=n;d[startCity]=0;
    	int f=1,r=1;q[1]=startCity;
    	while (f<=r)
    	{
    		int x=q[f++];
    		for (int i=0;i<=range[x];i++)
    		{
    			int y=(x-i+n)%n;
    			if (d[y]==n) {d[y]=d[x]+1;q[++r]=y;}
    			y=(x+i)%n;
    			if (d[y]==n) {d[y]=d[x]+1;q[++r]=y;}
    		}
    	}
    	return d[endCity];
    }
};
