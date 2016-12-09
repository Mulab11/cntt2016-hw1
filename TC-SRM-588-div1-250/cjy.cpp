#include<bits/stdc++.h>
using namespace std;
pair<int,int>c[55];
int f[55][55],ans,i,j,k;
class GUMIAndSongsDiv1
{
	public:
		int maxSongs(vector<int> a,vector<int> b,int T)
		{
			for(i=0;i<a.size();i++)c[i]=make_pair(b[i],a[i]);
			sort(c,c+a.size());
			for(i=0;i<a.size();i++)//f[i][j]表示唱了以i结尾的j首歌最小时间		
			{
				f[i][0]=c[i].second;
				if(f[i][0]<=T)ans=max(ans,1);
				for(j=1;j<=i;j++)
				{
					for(f[i][j]=1<<30,k=j-1;k<i;k++)f[i][j]=min(f[i][j],f[k][j-1]+c[i].second+c[i].first-c[k].first);
					if(f[i][j]<=T)ans=max(ans,j+1);
				}
			}
			return ans;
		}
};
