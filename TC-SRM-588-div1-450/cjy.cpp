#include<bits/stdc++.h>
#define vi vector<int>
using namespace std;
int f[4096][131],ans;
class KeyDungeonDiv1
{
	public:
		int maxKeys(vi dr,vi dg,vi rr,vi rg,vi rw,vi ks)
		{
			int n=dr.size(),i,j,k,l,s,t;
			memset(f,-1,sizeof(f));
			f[0][ks[0]]=ks[2];
			for(i=0;i<(1<<n);i++)//f[i][j]表示开门状态i，剩j把红时最多有多少白			
			{
				for(j=s=0;j<n;j++)if(i>>j&1)s+=rr[j]+rg[j]+rw[j]-dr[j]-dg[j];
				for(j=0;j<131;j++)if(~f[i][j])
				{
					k=s+ks[0]+ks[1]+ks[2]-j-f[i][j];
					ans=max(ans,f[i][j]+j+k);
					for(l=0;l<n;l++)if(!(i>>l&1)&&k+j+f[i][j]>=dr[l]+dg[l]&&k+f[i][j]>=dg[l]&&j+f[i][j]>=dr[l])
					t=max(0,j-dr[l])+rr[l],f[i|(1<<l)][t]=max(f[i|(1<<l)][t],f[i][j]-max(0,dr[l]-j)-max(0,dg[l]-k)+rw[l]);
				}
			}
			return ans;
		}
};
