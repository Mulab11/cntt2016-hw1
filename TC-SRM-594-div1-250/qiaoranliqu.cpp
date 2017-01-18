#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans,f[N][N],l;
long long C[N],D[N];
class AstronomicalRecords{
	public:
		int minimalPlanets(vector <int> A, vector <int> B)
		{
				n=A.size(); m=B.size();
				for (i=0;i<n;++i)
					for (j=0;j<m;++j) 
					{
						for (k=1;k<=n;++k) C[k]=1ll*A[k-1]*B[j];
						for (k=1;k<=m;++k) D[k]=1ll*B[k-1]*A[i];
						memset(f,0,sizeof(f));
						for (k=1;k<=n;++k)
							for (l=1;l<=m;++l)
							{
								f[k][l]=max(f[k][l-1],f[k-1][l]);
								if (C[k]==D[l])
								f[k][l]=max(f[k][l],f[k-1][l-1]+1);
							}
						ans=max(ans,f[n][m]);
					}
					return n+m-ans;
		}
};

