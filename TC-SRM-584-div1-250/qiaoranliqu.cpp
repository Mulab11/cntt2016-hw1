#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>

#define pb push_back

using namespace std;
int A[55][55],n,i,j,k;
class Egalitarianism{
	public:
		int maxDifference(vector<string> s,int d)
		{
			   int ans=0;
			   memset(A,60,sizeof(A));
			   n=s.size();
			   for (i=0;i<n;++i)
			     for (j=0;j<n;++j)
			       if (s[i][j]=='Y') A[i][j]=1;
			    for (k=0;k<n;++k)
			      for (i=0;i<n;++i)
			         if (k!=i) 
			        for (j=0;j<n;++j) 
			           if (k!=j&&i!=j)
			             A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
			    for (i=0;i<n;++i)
			      for (j=0;j<n;++j)
			        if(i!=j) ans=max(ans,A[i][j]);
			    if (ans>(int)1e9) return -1;
			    return ans*d;
		}
}E;
int main()
{
	 vector<string> v;
	 v.pb("NYN"),
     v.pb("YNY"),
     v.pb("NYN");
	 E.maxDifference(v,10);
}
