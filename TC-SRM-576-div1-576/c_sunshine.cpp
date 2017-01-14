#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class TheExperiment
{
	public:
	string s;
	int n,m,M;
	int f[305][305][3];
	
	inline void up(int &x,const int &y)
	{x=(x+y)%M;}
	
	int countPlacements(vector<string> intensity, int M, int L, int A, int B)
	{
		for(int i=0;i<intensity.size();i++)
			s+=intensity[i];
		n=s.size();m=M;this->M=M=1000000009;
		f[0][0][0]=1;
		//f[i][j][k]: now is at position i, j sponges has been placed.
		//k=0 : position is not covered.
		//k=1 : position is covered and there isn't an intact sponge in the last continuous sponges group.
		//k=2 : position is covered and there is an intact sponge.
		for(int i=0;i<n;i++)
			for(int j=0;j<=m;j++)
			{
				int sum=0;
				//do not place a sponge here
				up(f[i+1][j][0],f[i][j][0]);
				up(f[i+1][j][0],f[i][j][2]);
				for(int k=i;k<n&&k<i+L;k++)//place a sponge [i,k]
				{
					sum+=s[k]-'0';
					if(sum>=A&&sum<=B)
					{
						up(f[k+1][j+1][1+(k==i+L-1)],f[i][j][0]);
						up(f[k+1][j+1][1+(k==i+L-1)],f[i][j][1]);
						up(f[k+1][j+1][2],f[i][j][2]);
					}
				}
			}
		int ans=0;
		up(ans,f[n][m][0]);
		up(ans,f[n][m][2]);
		return ans;
	}
};

