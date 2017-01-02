#include<bits/stdc++.h>
#define UP(x,y) (x+=1ll*f[j][k][l]*(y)%P)%=P
using namespace std;
int v[30],i,s,f[55][2][2],j,k,l,P=1e9+7,n;
class DefectiveAddition//分情况讨论，DP
{
	public:
		int count(vector<int> a,int m)
		{
			for(i=v[0]=1;i<30;i++)v[i]=1ll*v[i-1]*(P+1>>1)%P;
			for(auto x:a)k^=x,n++;
			for(s=k==m,i=29;~i;i--)
			{
				for(memset(f,0,sizeof(f)),f[j=0][0][0]=1;j<n;j++)for(k=0;k<2;k++)for(l=0;l<2;l++)if(a[j]>>i&1)UP(f[j+1][k][1],1<<i),UP(f[j+1][k^1][l],(a[j]&(1<<i)-1)+1);else UP(f[j+1][k][l],(a[j]&(1<<i)-1)+1);
				if((s+=1ll*f[n][m>>i&1][1]*v[i]%P)%=P,!f[n][m>>i&1][0])break;
			}
			return s;
		}
};
