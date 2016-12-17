#include<bits/stdc++.h>
#define vi vector<int>
using namespace std;
long long f[55][55],ans,C[55][55];
int a[55],i,j,n,m,no,K;
vi c[55],_;
void dp(int p)
{
	int i,j,k;
	memset(f,0,sizeof(f));
	f[0][c[0].size()-1-p]=1;
	for(i=0;i<m;i++)for(j=0;j<=n;j++)for(k=0;k<c[_[i]].size();k++)if(no||c[_[i]][k]<c[0][p])f[i+1][j+c[_[i]].size()-1-k]+=f[i][j];
	for(j=0;j<=n;j++)ans+=f[m][j]*C[j][K-m-!no];
}
class Excavations
{
	public:
		long long count(vi b,vi d,vi A,int k)
		{
			n=b.size();m=A.size();_=A;K=k;
			if(K<m)return 0;
			for(i=0;i<=n;i++)for(j=C[i][0]=1;j<=i;j++)C[i][j]=C[i-1][j]+C[i-1][j-1];
			for(auto x : A)
			{
				for(a[x]=1,i=0;i<n;i++)if(b[i]==x)c[x].push_back(d[i]);
				sort(c[x].begin(),c[x].end());
			}
			for(i=0;i<n;i++)if(!a[b[i]])c[0].push_back(d[i]);
			sort(c[0].begin(),c[0].end());
			for(i=0;i<c[0].size();i++)dp(i);
			no=1;dp(c[0].size()-1);
			return ans;
		}
};
