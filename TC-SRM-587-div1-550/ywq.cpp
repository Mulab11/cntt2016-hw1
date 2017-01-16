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

double calc(int k,int W)
{
	k=W-k;
	return double(k)/(k+W);
}

struct TriangleXor 
{
    int theArea(int W)
    {
    	double ans=0;
    	for (int i=0;i<W;i+=2)
    	{
    		double dy=double(i+1)/(i+1+W)-double(i)/(i+W);
    		ans+=dy;
    	}
    	ans=ans*W;
    	if (W%2==0) ans+=double(W)/4;
    	for (int i=W-1;i>0;i-=2)
    		ans=ans+(calc(i-1,W)-calc(i+1,W))*(0.5-calc(i,W))*W;
    	return int(ans+0.001);
    }
};
