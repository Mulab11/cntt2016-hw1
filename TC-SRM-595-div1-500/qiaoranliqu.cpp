#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

using namespace std; 

#define N 2505

int vis[N],i,j,m,n,p,k,len,E[N],A[N][N];
char c[N];
long long ans;

class LittleElephantAndRGB{
	 public:
	 	long long getNumber (vector<string> s,int k)
	 	{
	 		for (i=0;i<(int)s.size();++i)
	 		  for (j=0;j<(int)s[i].length();++j)
	 		    c[++len]=s[i][j];
	 		for (i=1;i<=len;++i)
	 		{
	 			   int Max=0,now=0;
	 			   for (j=i;j<=len;++j)
	 			   {
	 			   	  if (c[j]=='G') ++now; else now=0;
	 			   	  Max=max(Max,now); 
	 			   if (Max>=k) ans+=(len-j)*(len-j+1)/2,E[j]++;
	 		       }
	 		}
	 		int pr=0;
	        for (i=1;i<=len;++i)
	 		{   
	 		     int Max=0,now=0; pr+=E[i-1];
	 		     for (j=i;j<=len;++j) 
	 		     {
	 		     	    if (c[j]=='G') ++now; else now=0;
	 		     	    Max=max(Max,now);
	 		     if (Max>=k) ans+=(i-1)*i/2,ans-=pr;
	 		     }
	 		}
	 		for (i=1;i<=len;++i)
	 		{
	 			 int Max=0,now=0;
	 			 for (j=i;j<=len;++j)
	 			 {
	 			 	  if (c[j]=='G') ++now; else now=0;
	 			 	  Max=max(Max,now);
	 			 	  if (Max>=k) break;
	 			 	  A[j][now]++;
	 			 }
	 		 }
	 		 for (i=1;i<=len;++i) 
			    for (j=0;j<k;++j) A[i][j]+=A[i-1][j];
			 for (i=1;i<=len;++i)
			    for (j=k;j>=0;--j) A[i][j]+=A[i][j+1]; 
	 		 for (i=1;i<=len;++i)
	 		 {
	 		 	    int now=0,flag=0,S=0;
	 		 	    for (j=i;j<=len;++j)
					{
					    if (!flag&&c[j]=='G') ++now;
		                else flag=1;
		                if (c[j]=='G') ++S; else S=0;
					    if(S>=k) break; 
					    ans+=A[i-1][k-now];
					}
			 }
			 return ans;
	 	}
}FFT;
	
