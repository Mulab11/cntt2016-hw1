#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;
typedef long long LL;
template<class T> inline bool ten(T &x,const T &y){return y<x?x=y,1:0;}
template<class T> inline bool rel(T &x,const T &y){return x<y?x=y,1:0;}
class MonstersValley
{
	public:
	LL f[55][105];
	int minimumPrice(vector<LL> dread,vector<int> price)
	{
		int n=dread.size();
		memset(f,-1,sizeof(f));
		f[0][0]=0;
		//f[i][j]: The greatest total scariness of his party when he has gone past the first i monsters and paid j coins.
		for(int i=0;i<n;i++)
			for(int j=0;j<=i+i;j++)
				if(f[i][j]!=-1)
				{
					if(dread[i]<=f[i][j])//We can simply go past it.
						rel(f[i+1][j],f[i][j]);
					//Any time we can bribe it.
					rel(f[i+1][j+price[i]],f[i][j]+dread[i]);
				}
		for(int j=0;j<=n+n;j++)//Find the minimum cost since -1 means impossible.
			if(f[n][j]!=-1)return j;
		return -1;
	}
};

