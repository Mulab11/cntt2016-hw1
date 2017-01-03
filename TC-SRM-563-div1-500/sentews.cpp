#include<algorithm>
#include<vector>
using namespace std;
int f[155]={};
int ans=0;
struct ff{int x,y;}g[155]={};
class SpellCards
{
public:
	int maxDamage(vector<int> level, vector<int> damage)
	{
		int n=level.size();
		for(int i=0;i<n;i++)
			g[i].x=level[i],g[i].y=damage[i];
		for(int i=0;i<n;i++)
			for(int j=n;j>=g[i].x;j--)
				f[j]=max(f[j-g[i].x]+g[i].y,f[j]);
		return f[n];
	}
};
