#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class KeyDungeonDiv1
{
	public:
	int f[4096][135];
	int maxKeys(vector<int> doorR,vector<int> doorG,vector<int> roomR,vector<int> roomG,vector<int> roomW,vector<int> keys)
	{
		int n=doorR.size(),ans=0;
		//f[s][r]:The maximum number of white keys we can have,
		//while the set of the doors we have opened is s and we have excatly r red keys.
		//We can calculate the number of keys we have if we know the set of opened doors, so we needn't keep it
		memset(f,-1,sizeof(f));
		f[0][keys[0]]=keys[2];
		for(int s=0;s<1<<n;s++)
		{
			int num=keys[0]+keys[1]+keys[2];//the number of keys we have
			for(int i=0;i<n;i++)
				if(s>>i&1)
				{
					num-=doorR[i]+doorG[i];
					num+=roomR[i]+roomG[i]+roomW[i];
				}
			for(int r=0,g,w,r_,g_,w_;r<=num;r++)
				if(f[s][r]!=-1)
				{
					ans=max(ans,num);//this state can be reached, so we need to update the answer with num
					for(int i=0;i<n;i++)//enumerate the next door to open
						if((s>>i&1)==0)
						{
							w=f[s][r];
							g=num-r-w;
							//We should use white keys as few as possible,
							//because anytime, a white key is not worse than a red or green key
							r_=max(0,r-doorR[i]);
							g_=max(0,g-doorG[i]);
							w_=w-max(doorR[i]-r,0)-max(doorG[i]-g,0);
							if(w_>=0)
							{
								r_+=roomR[i];
								g_+=roomG[i];
								w_+=roomW[i];
								//calculate the new numbers of red, green and white keys.
								f[s|1<<i][r_]=max(f[s|1<<i][r_],w_);
							}
						}
				}
		}
		return ans;
	}
};

