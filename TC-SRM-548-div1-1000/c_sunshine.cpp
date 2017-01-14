#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;
typedef long long LL;
const int M=1000000007;
class KingdomAndCities
{
	public:
	
	int co[1300][55],f[55][55];
	
	int calc(int n,int k)//Count the connected bidirectional graphs with n vertices and k edges.
	{
		if(n<0||k<0)return 0;
		int &res=f[n][k];
		if(res!=-1)return res;
		res=0;
		if(k>=n-1&&k<=co[n][2])
		{
			res=co[co[n][2]][k];
			//We use inclusion-exclusion principle, that means subtract the unconnected graph.
			//We can simply pick the size of set of vertices connected to 1,
			//and use conbinatorial number to calculate the number of ways.
			for(int na=1,nb=n-1;na<n;na++,nb--)
				for(int ka=0,kb=k;ka<=k;ka++,kb--)
					res=(res+M-(LL)co[n-1][na-1]*calc(na,ka)%M*co[co[nb][2]][kb]%M)%M;
		}
		return res;
	}
	
	int howMany(int n,int m,int k)
	{
		memset(co,0,sizeof(co));
		//conbinatorial numbers 
		for(int i=0;i<=1225;i++)
		{
			co[i][0]=1;
			for(int j=1;j<=i&&j<=50;j++)
				co[i][j]=(co[i-1][j]+co[i-1][j-1])%M;
		}
		memset(f,-1,sizeof(f));
		int ans=0;
		if(m==0)ans=calc(n,k);
		if(m==1)
		{
			//The graph will still be connected after moving the special vertex.
			ans=(LL)calc(n-1,k-2)*co[n-1][2]%M;
			//The graph will be split into two blocks after moving the special vertex.
			for(int na=1,nb=n-2;na<n-1;na++,nb--)
				for(int ka=0,kb=k-2;ka<=k-2;ka++,kb--)
					ans=(ans+(LL)calc(na,ka)*calc(nb,kb)%M
											*co[n-2][na-1]%M*(na*nb)%M)%M;
		}
		if(m==2)
		{
			//The graph will still be connected after moving two special vertices,
			//and there is an edge between two special vertices.
			ans=(LL)calc(n-2,k-3)*(n-2)*(n-2)%M;
			//The graph will be split into two blocks after moving the special vertices,
			//and there is an edge between two special vertices.
			//Like G1-a-b-G2.
			for(int na=1,nb=n-3;na<n-2;na++,nb--)
				for(int ka=0,kb=k-3;ka<=k-3;ka++,kb--)
					ans=(ans+(LL)calc(na,ka)*calc(nb,kb)%M
											*co[n-3][na-1]%M*na*nb*2%M)%M;
			//The graph will still be connected after moving two special vertices,
			//and there isn't an edge between two special vertices.
			ans=(ans+(LL)calc(n-2,k-4)*co[n-2][2]%M*co[n-2][2])%M;
			//The graph will be split into two blocks after moving one of two special vertices.
			for(int na=1,nb=n-3;na<n-2;na++,nb--)
				for(int ka=0,kb=k-4;ka<=k-4;ka++,kb--)
					ans=(ans+(LL)calc(na,ka)*calc(nb,kb)%M*co[n-3][na-1]%M
											*na*nb*(na*nb+na*(na-1)+nb*(nb-1))%M)%M;
			//The graph will be split into three blocks after moving the special vertices.
			//Like G1-a-G2-b-G3.
			for(int na=1;na<n-3;na++)
				for(int ka=0;ka<=k-4;ka++)
					for(int nb=1;nb<n-2-na;nb++)
						for(int kb=0;kb<=k-4-ka;kb++)
						{
							int nc=n-2-na-nb,kc=k-4-ka-kb;
							ans=(ans+(LL)calc(na,ka)*calc(nb,kb)%M*calc(nc,kc)%M
													*co[n-3][na-1]%M*co[n-2-na-1][nb-1]%M
													*2*na*nb*nc*(na+nb+nc)%M)%M;
						}
		}
		return ans;
	}
};

