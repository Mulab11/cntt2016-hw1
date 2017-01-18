#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

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
int i,j,m,n,p,k,v[N][N],tot,cao,w[N];
double f[N][2][1500];
class RandomPaintingOnABoard{
	public:
		double expectedSteps(vector<string> s)
		{
			   n=s.size(); m=s[0].length();
			   if (n<m)
			   {
			      for (i=0;i<n;++i)
			        for (j=0;j<m;++j)
			           v[i][j]=s[i][j]-'0',tot+=v[i][j];
			   }
			   else 
			   {
			   	     swap(n,m);
			   	     for (i=0;i<n;++i)
					   for (j=0;j<m;++j) 
					     v[i][j]=s[j][i]-'0',tot+=v[i][j];
			   }
			   double ans=0;
			   for (cao=0;cao<(1<<n);++cao)
			   {
			   	    memset(f,0,sizeof(f));
			   	    memset(w,0,sizeof(w));
			   	    int ww=0,r=0;
			   	    for (i=0;i<n;++i)
			   	      if (cao&(1<<i)) 
			   	        for (j=0,r++;j<m;++j) ww+=v[i][j];
			   	        else for (j=0;j<m;++j) w[j]+=v[i][j];
			   	   f[0][r%2][ww]=1;
			   	   for (i=0;i<m;++i)
			   	     for (j=0;j<2;++j)
			   	       for (k=0;k<1400;++k)
			   	         if (f[i][j][k])
							{
							    f[i+1][j][k]+=f[i][j][k];
								f[i+1][j^1][k+w[i]]+=f[i][j][k];
						    }
				   for (k=1;k<1400;++k)
				      ans+=1.*(f[m][1][k]-f[m][0][k])*(tot-k)/k;
			   }
			   return ans+1.;
		}
};
			    
