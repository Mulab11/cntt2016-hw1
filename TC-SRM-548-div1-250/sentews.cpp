#include<cstdio>
#include<algorithm>
using namespace std;
int f[111111]={};int n;
int g[111111]={};
int zuo=0,you=833333333;
bool check(int s)
{
	g[0]=f[0]-s;
	if(g[0]<1)g[0]=1;
	for(int i=1;i<n;i++)
	{
		if(f[i]+s<=g[i-1])return false;
		g[i]=max(g[i-1]+1,f[i]-s);
	}
	return true;
}
class KingdomAndTrees
{
	public:
	int minLevel(vector <int> heights)
	{
		n=heights.size();
		for(int i=0;i<n;i++)
			f[i]=heights[i];
		if(check(0))
			return 0;
		while(zuo+1<you)
		{
			int zhong=(zuo+you)/2;
			if(check(zhong))
				you=zhong;
			else
				zuo=zhong;
		}
		return you;
	}
};
