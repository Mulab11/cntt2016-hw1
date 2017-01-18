#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std; 

#define N 1005

int i,j,m,n,p,k,vis[N];
class LittleElephantAndIntervalsDiv1{
	 public:
	 	long long getNumber(int n,vector<int> L,vector<int> R)
	 	{
	 		  m=R.size(); long long ans=1;
	 		  for (i=m-1;i>=0;--i)
	 		  {
	 		  	    int cnt=0;
	 		  	    for (j=L[i];j<=R[i];++j)
	 		  	      if (!vis[j]) vis[j]=1,cnt=1;
	 		  	    if (cnt) ans*=2;
	 		  }
	 		  return ans;
	 	}
}; 
	 		  	
