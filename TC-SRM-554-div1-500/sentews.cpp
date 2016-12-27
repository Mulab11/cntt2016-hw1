#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int f[155]={},n;
int g[155]={},tot=-1;
bool cmpp(int a,int b)
{
	if(f[a]!=f[b])
		return f[a]<f[b];
	else 
		return a<b;
}
class TheBrickTowerMediumDivOne
{
    public:
        vector <int> find(vector <int> heights)
        {
			n=heights.size();
			for(int i=0;i<n;i++)f[i]=heights[i];
            tot=0;
			for(int i=1;i<n;i++)
				if(f[i]<=f[g[tot]])
					g[++tot]=i;
				else g[n+tot-i]=i;
			sort(g+tot+1,g+n,cmpp);
			vector <int>aa;
			for(int i=0;i<n;i++)
				aa.push_back(g[i]);
			return aa;
        }
};
/*
int main()
{
	freopen("1","r",stdin);
    int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)
		scanf("%d",&f[i]);
	tot=0;
	for(int i=1;i<n;i++)
		if(f[i]<=f[g[tot]])
			g[++tot]=i;
		else g[n+tot-i]=i;
	sort(g+tot+1,g+n,cmpp);
	
}*/
