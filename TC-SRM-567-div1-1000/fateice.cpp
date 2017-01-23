#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<map>
#define L long long
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
using namespace std;
class Mountains
{
	int n,m,f[60],l[60],r[60],q=1000000009;
	vector<int> x;
	map<string,int> p;
	inline int dfs(int i)  //记忆化搜索 
	{
		if(i<0)
		  return 1;
		int j,k,g[60],ans=0;
	    string s;
		s.clear();
		s.push_back(i);
		for(j=0;j<m;j++)
		  s.push_back(f[j]);
		if(p[s])
		  return p[s];
		if(l[i]==m)
		  {
		   for(j=0,k=0;j<m;j++)   //枚举放在哪个位置 
		     if(x[i]<=f[j])
		       k++;
		   ans=(L)k*dfs(i-1)%q;
		  }
		else
		  for(j=l[i];j<=r[i];j++)   //枚举放在哪个位置 
		    if(x[i]-(j-l[i])>f[l[i]] && x[i]-(r[i]-j)>f[r[i]] && (l[i]==0 || x[i]-(j-l[i])-1<=f[l[i]-1]) && (r[i]==m-1 || x[i]-(r[i]-j)-1<=f[r[i]+1]))
		      {
			   for(k=l[i];k<=r[i];k++)
			     {
			      g[k]=f[k];
			      f[k]=x[i]-abs(j-k);
				 }
			   ans=(ans+dfs(i-1))%q;
			   for(k=l[i];k<=r[i];k++)
			     f[k]=g[k];
			  }
		p[s]=ans;
		return ans;
	}
public:
	int countPlacements(vector<int> xx,vector<string> s)
	{
		int i,j;
		x=xx;
		n=x.size();
		m=s[0].size();
		for(i=0;i<n;i++)
		  {
		   for(j=0;j<m && s[i][j]=='-';j++);
		   l[i]=j;
		   for(j=m-1;j>=0 && s[i][j]=='-';j--);
		   r[i]=j;
		   for(j=l[i];j<=r[i];j++)
		     if(s[i][j]=='-')
		       return 0;
		  }
		return dfs(n-1);
    }
};
