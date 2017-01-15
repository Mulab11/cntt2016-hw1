#include<string>
#include<algorithm>
#include<vector>
using namespace std;
int f[111]={},g[111]={};int n,t;
class GUMIAndSongsDiv1
{
public:
	int maxSongs(vector <int> duration, vector <int> tone, int T)
	{
		t=T;
		n=tone.size();
		for(int i=0;i<n;i++)
			f[i]=duration[i],g[i]=tone[i];
		int codeforces=0;
		for(int i=0;i<n;i++)
			for(int j=i;j<n;j++)
			{
				int maxx=max(g[i],g[j]);
				int minn=min(g[i],g[j]);
				int r=t-maxx+minn-f[i];
				if(i!=j)r-=f[j];
				if(r<0)continue;
				int tt[111]={},tot=0;
				int temp=1;
				if(i!=j)temp++;
				for(int k=0;k<n;k++)
					if(i!=k&&j!=k&&g[k]>=minn&&g[k]<=maxx)
						tt[tot++]=f[k];
				sort(tt,tt+tot);
				for(int k=0;k<tot;k++)if(r>=tt[k])
					temp++,r-=tt[k];
				codeforces=max(codeforces,temp);
			}
		return codeforces;
	}
};
