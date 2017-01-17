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

int dfs(int n,int w,int x,int d)
{
	if (n<=w&&(x==1||x==n)) return d+1;
	if (x==w&&n<2*w) return d+1;
	if (n==x&&x%w==1) return d+1;
	if (w==1&&(x==1||x==n)) return d+1;
	if (d==2) return 4;
	int r=(x-1)/w+1,c=(x-1)%w+1;
	int ans=4,R=(n-1)/w+1,C=(n-1)%w+1;
	for (int i=1;i<r;i++)
		for (int j=1;j<=w;j++)
			ans=min(ans,dfs(n-i*j,w,x-i*j,d+1));
	for (int i=1;i<=r;i++)
		for (int j=1;j<c;j++)
		{
			int t=(R-i)*j;
			if (j<=C) t+=j; else t+=C;
			ans=min(ans,dfs(n-t,w,x-(r-i+1)*j,d+1));
		}
	ans=min(ans,dfs(r*w,w,x,d+1));
	for (int i=1;i<=r;i++)
		for (int j=c+1;j<=w;j++)
		{
			int t=(R-i)*(j-c);
			if (c<=C) t-=c; else t-=C;
			if (j<=C) t+=j; else t+=C;
			ans=min(ans,dfs(n-t,w,x-(r-i)*(j-c),d+1));
		}
	return ans;
}

struct FoxAndAvatar 
{
    int minimalSteps(int n, int width, int x)
    {
    	if (n==1) return 0; else return dfs(n,width,x,0);
    }
};
