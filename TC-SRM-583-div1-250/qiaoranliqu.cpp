#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

#define N 55

int i,j,m,n,p,k,A[N][N];
class TravelOnMars{
	public:	
	int minTimes(vector<int> v,int str,int end)
	{
	        n=v.size();
	        memset(A,60,sizeof(A));
			for (i=0;i<n;++i)
			  for (j=0;j<n;++j)
			    if (min(abs(max(i,j)-min(i,j)),abs(min(i,j)+n-max(i,j)))<=v[i]) A[i][j]=1;
			for (k=0;k<n;++k)
			  for (i=0;i<n;++i)
			    for (j=0;j<n;++j)
				  A[i][j]=min(A[i][k]+A[k][j],A[i][j]);
		    return A[str][end];
	}
};
