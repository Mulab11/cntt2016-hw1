#include<bits/stdc++.h>
using namespace std;
int i,j,k,s,n,f[51][8];
vector<int> c[3];
class BallsSeparating
{
	public:
		int minOperations(vector<int> r,vector<int> g,vector<int> b)
		{
			if(c[0]=r,c[1]=g,c[2]=b,memset(f,-1,sizeof(f)),n=r.size(),n<3)return -1;
			for(f[0][0]=0;i<n;i++)for(s+=r[i]+g[i]+b[i],j=0;j<8;j++)if(~f[i][j])for(k=0;k<3;k++)f[i+1][j|(1<<k)]=max(f[i+1][j|(1<<k)],f[i][j]+c[k][i]);
			return s-f[n][7];
		}
};
