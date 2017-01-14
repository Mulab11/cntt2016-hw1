#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class GUMIAndSongsDiv1
{
	public:
	int f[55][55];
	int maxSongs(vector<int> duration,vector<int> tone,int T)
	{
		vector<pair<int,int> > song;
		int n=tone.size();
		for(int i=0;i<n;i++)
			song.push_back(make_pair(tone[i],duration[i]));
		//It is clear that we can sing songs in an increasing order to get a minimum cost
		sort(song.begin(),song.end());
		//f[i][j]: We have song j songs and the last song we've song is i
		memset(f,63,sizeof(f));
		for(int i=0;i<n;i++)
			f[i][1]=song[i].second;
		int ans=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<=n;j++)
				if(f[i][j]<=T)
				{
					ans=max(ans,j);
					for(int k=i+1;k<n;k++)//enumerate next song we will sing
						f[k][j+1]=min(f[k][j+1],f[i][j]+song[k].first-song[i].first+song[k].second);
				}
		return ans;
	}
};

