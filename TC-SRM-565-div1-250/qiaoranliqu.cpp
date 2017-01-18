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

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k;
long long f[N][N];
class MonstersValley{
	public:
		int minimumPrice(vector<long long> dread, vector <int> price)
	    {
	    	 n=dread.size();
	    	 for (i=0;i<=n;++i)
	    	 	for (j=0;j<=100;++j) f[i][j]=-1;
	    	 f[0][0]=0;
	    	 for (i=0;i<n;++i) //令f_{i,j}为代价为j的最高收益 
	    	 	for (j=0;j<=100;++j)
	    	 		if (f[i][j]!=-1)
	    	 	{
	    	 		 f[i+1][j+price[i]]=max(f[i+1][j+price[i]],f[i][j]+dread[i]);
	    	 		 if (f[i][j]>=dread[i]) f[i+1][j]=max(f[i+1][j],f[i][j]); 
				}
			for (i=0;i<=100;++i)  if (f[n][i]!=-1) return i; 
	    }
}; 
